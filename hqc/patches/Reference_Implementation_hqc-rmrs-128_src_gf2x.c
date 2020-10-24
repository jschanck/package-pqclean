--- upstream/Reference_Implementation/hqc-rmrs-128/src/gf2x.c
+++ upstream-patched/Reference_Implementation/hqc-rmrs-128/src/gf2x.c
@@ -6,15 +6,12 @@
 #include "gf2x.h"
 #include "rng.h"
 #include "parameters.h"
+#include "parsing.h"
 #include <stdint.h>
-#include <string.h>
-
-#define TABLE 16
-#define WORD 64
 
 static inline void swap(uint16_t * tab, uint16_t elt1, uint16_t elt2);
-static inline void reduce(uint64_t *o, uint64_t *a);
-static inline void fast_convolution_mult(uint64_t *o, const uint32_t *a1, const uint64_t *a2, const uint16_t weight, AES_XOF_struct *ctx);
+static void reduce(uint64_t *o, const uint64_t *a);
+static void fast_convolution_mult(uint8_t *o, const uint32_t *a1, const uint64_t *a2, uint16_t weight, AES_XOF_struct *ctx);
 
 /**
  * @brief swap two elements in a table
@@ -42,22 +39,18 @@
  * @param[in] a Pointer to the polynomial a(x)
  * @param[out] o Pointer to the result
  */
-static inline void reduce(uint64_t *o, uint64_t *a) {
+static void reduce(uint64_t *o, const uint64_t *a) {
+	size_t i;
 	uint64_t r;
-	uint64_t carry = 0;
-	static const int32_t dec64 = PARAM_N & 0x3f;
-	static const int32_t i64 = PARAM_N >> 6;
-	static const int32_t d0 = WORD - dec64;
-	int32_t i;
-
-	for (i = 0 ; i < i64 + 1 ; i++) {
-		r = a[i + i64] >> dec64;
-		carry = a[i + i64 + 1] << d0;
-		r ^= carry;
-		o[i] = a[i] ^ r;
+	uint64_t carry;
+
+	for (i = 0 ; i < VEC_N_SIZE_64 ; i++) {
+		r = a[i + VEC_N_SIZE_64 - 1] >> (PARAM_N & 63);
+		carry = (uint64_t) (a[i + VEC_N_SIZE_64] << (64 - (PARAM_N & 63)));
+		o[i] = a[i] ^ r ^ carry;
 	}
 
-	o[i - 1] &= RED_MASK;
+	o[VEC_N_SIZE_64 - 1] &= RED_MASK;
 }
 
 
@@ -73,75 +66,66 @@
  * @param[in] weight Hamming wifht of the sparse polynomial a2
  * @param[in] ctx Pointer to a seed expander used to randomize the multiplication process
  */
-static inline void fast_convolution_mult(uint64_t *o, const uint32_t *a1, const uint64_t *a2, const uint16_t weight, AES_XOF_struct *ctx) {
-//static inline int32_t fast_convolution_mult(const uint64_t *A, const uint32_t *vB, uint64_t *C, const uint16_t w, AES_XOF_struct *ctx)
+static void fast_convolution_mult(uint8_t *o, const uint32_t *a1, const uint64_t *a2, uint16_t weight, AES_XOF_struct *ctx) {
+//static uint32_t fast_convolution_mult(const uint64_t *A, const uint32_t *vB, uint64_t *C, const uint16_t w, AES_XOF_struct *ctx)
 	uint64_t carry;
-	int32_t dec, s;
-	uint64_t table[TABLE * (VEC_N_SIZE_64 + 1)];
-	uint16_t permuted_table[TABLE];
-	uint16_t permutation_table[TABLE];
+	uint32_t dec, s;
+	uint64_t table[16 * (VEC_N_SIZE_64 + 1)];
+	uint16_t permuted_table[16];
+	uint16_t permutation_table[16];
 	uint16_t permuted_sparse_vect[PARAM_OMEGA_E];
 	uint16_t permutation_sparse_vect[PARAM_OMEGA_E];
+	uint64_t tmp;
+	uint64_t *pt;
+	uint8_t *res;
+	size_t i, j;
 
-	for (int32_t i = 0 ; i < TABLE ; i++) {
-		permuted_table[i] = i;
+	for (i = 0 ; i < 16; i++) {
+		permuted_table[i] = (uint16_t) i;
 	}
 
-	seedexpander(ctx, (uint8_t *) permutation_table, TABLE << 1);
-
-	for (int32_t i = 0 ; i < TABLE - 1 ; i++) {
-		swap(permuted_table + i, 0, permutation_table[i] % (TABLE - i));
-	}
+	seedexpander(ctx, (uint8_t *) permutation_table, 16 * sizeof(uint16_t));
 
-	for (int32_t j = 0 ; j < VEC_N_SIZE_64 << 1 ; j++) {
-		o[j] = 0UL;
+	for (i = 0 ; i < 15 ; i++) {
+		swap(permuted_table + i, 0, permutation_table[i] % (16 - i));
 	}
 
-	uint64_t *pt = table + (permuted_table[0] * (VEC_N_SIZE_64 + 1));
-
-	for (int32_t j = 0 ; j < VEC_N_SIZE_64 ; j++) {
+	pt = table + (permuted_table[0] * (VEC_N_SIZE_64 + 1));
+	for (j = 0 ; j < VEC_N_SIZE_64 ; j++) {
 		pt[j] = a2[j];
 	}
+	pt[VEC_N_SIZE_64] = 0x0;
 
-	pt[VEC_N_SIZE_64] = 0x0UL;
-
-	for (uint32_t i = 1 ; i < TABLE ; i++) {
-		carry = 0x0UL;
-		int32_t idx = permuted_table[i] * (VEC_N_SIZE_64 + 1);
-		uint64_t *pt = table + idx;
-		for (int32_t j = 0 ; j < VEC_N_SIZE_64 ; j++) {
+	for (i = 1 ; i < 16 ; i++) {
+		carry = 0;
+		pt = table + (permuted_table[i] * (VEC_N_SIZE_64 + 1));
+		for (j = 0 ; j < VEC_N_SIZE_64 ; j++) {
 			pt[j] = (a2[j] << i) ^ carry;
-			carry = (a2[j] >> ((WORD - i)));
+			carry = (a2[j] >> ((64 - i)));
 		}
-
 		pt[VEC_N_SIZE_64] = carry;
 	}
 
-	for (int32_t i = 0 ; i < weight ; i++) {
-		permuted_sparse_vect[i] = i;
+	for (i = 0 ; i < weight ; i++) {
+		permuted_sparse_vect[i] = (uint16_t) i;
 	}
 
-	seedexpander(ctx, (uint8_t *) permutation_sparse_vect, weight << 1);
+	seedexpander(ctx, (uint8_t *) permutation_sparse_vect, weight * sizeof(uint16_t));
 
-	for (int32_t i = 0 ; i < weight - 1 ; i++) {
-		swap(permuted_sparse_vect + i, 0, permutation_sparse_vect[i] % (weight - i));
+	for (i = 0 ; i + 1 < weight ; i++) {
+		swap(permuted_sparse_vect + i, 0, (uint16_t) (permutation_sparse_vect[i] % (weight - i)));
 	}
 
-	for (int32_t i = 0 ; i < weight ; i++) {
-		carry = 0x0UL;
+	for (i = 0 ; i < weight ; i++) {
 		dec = a1[permuted_sparse_vect[i]] & 0xf;
 		s = a1[permuted_sparse_vect[i]] >> 4;
-		uint16_t *res_16 = (uint16_t *) o;
-		res_16 += s;
-		uint64_t *pt = table + (permuted_table[dec] * (VEC_N_SIZE_64 + 1));
-
-		for (int32_t j = 0 ; j < VEC_N_SIZE_64 + 1 ; j++) {
-			uint64_t tmp = (uint64_t) res_16[0] | ((uint64_t) (res_16[1])) << 16 |
-				(uint64_t) (res_16[2]) << 32 | ((uint64_t) (res_16[3])) << 48;
-			tmp ^= pt[j];
-			uint64_t *res_64 = (uint64_t *) res_16;
-			res_64[0] = tmp;
-			res_16 += 4;
+		res = o + 2*s;
+		pt = table + (permuted_table[dec] * (VEC_N_SIZE_64 + 1));
+
+		for (j = 0 ; j < VEC_N_SIZE_64 + 1 ; j++) {
+			tmp = load8(res);
+			store8(res, tmp ^ pt[j]);
+			res += 8;
 		}
 	}
 }
@@ -160,8 +144,10 @@
  * @param[in] weight Integer that is the weigt of the sparse polynomial
  * @param[in] ctx Pointer to the randomness context
  */
-void vect_mul(uint64_t *o, const uint32_t *a1, const uint64_t *a2, const uint16_t weight, AES_XOF_struct *ctx) {
-	uint64_t tmp[VEC_N_SIZE_64 << 1];
-	fast_convolution_mult(tmp, a1, a2, weight, ctx);
+void vect_mul(uint64_t *o, const uint32_t *a1, const uint64_t *a2, uint16_t weight, AES_XOF_struct *ctx) {
+	uint64_t tmp[2*VEC_N_SIZE_64+1] = {0};
+
+	fast_convolution_mult((uint8_t *) tmp, a1, a2, weight, ctx);
+	load8_arr(tmp, 2*VEC_N_SIZE_64+1, (uint8_t *) tmp, sizeof(tmp));
 	reduce(o, tmp);
 }

