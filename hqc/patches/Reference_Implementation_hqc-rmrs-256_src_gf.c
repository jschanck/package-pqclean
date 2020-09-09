--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-256/src/gf.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-256/src/gf.c
@@ -8,47 +8,6 @@
 #include <stdint.h>
 
 
-/**
- * Generates exp and log lookup tables of GF(2^m).
- * The logarithm of 0 is defined as 2^PARAM_M by convention. <br>
- * The last two elements of the exp table are needed by the gf_mul function.
- * (for example if both elements to multiply are zero).
- * @param[out] exp Array of size 2^PARAM_M + 2 receiving the powers of the primitive element
- * @param[out] log Array of size 2^PARAM_M receiving the logarithms of the elements of GF(2^m)
- * @param[in] m Parameter of Galois field GF(2^m)
- */
-void gf_generate(uint16_t *exp, uint16_t *log, const int16_t m) {
-	uint16_t elt = 1;
-	uint16_t alpha = 2; // primitive element of GF(2^PARAM_M)
-	uint16_t gf_poly = PARAM_GF_POLY;
-
-	for (size_t i = 0 ; i < (1U << m) - 1 ; ++i) {
-		exp[i] = elt;
-		log[elt] = i;
-
-		elt *= alpha;
-		if (elt >= 1 << m) {
-			elt ^= gf_poly;
-		}
-	}
-
-	exp[(1 << m) - 1] = 1;
-	exp[1 << m] = 2;
-	exp[(1 << m) + 1] = 4;
-	log[0] = 1 << m; // by convention
-}
-
-
-
-/**
- * Returns the requested power of the primitive element of GF(2^PARAM_M).
- * @returns a^i
- */
-uint16_t gf_exp(uint16_t i) {
-	return exp[i];
-}
-
-
 
 /**
  * Returns the integer i such that elt = a^i
@@ -68,9 +27,9 @@
  * @param[in] b Second element of GF(2^PARAM_M) to multiply (cannot be zero)
  */
 uint16_t gf_mul(uint16_t a, uint16_t b) {
-	// mask = 0xffff if neither a nor b is zero. Otherwise mask is 0.
-	// mask = 0xffff si ni a ni b n'est nul. sinon mask = 0
-	int16_t mask = ((log[a]|log[b]) >> PARAM_M) - 1;
+  uint16_t mask;
+  mask = (uint16_t) (-((int32_t) a) >> 31); // a != 0
+  mask &= (uint16_t) (-((int32_t) b) >> 31); // b != 0
 	return mask & exp[gf_mod(log[a] + log[b])];
 }
 
@@ -82,7 +41,7 @@
  * @param[in] a Element of GF(2^PARAM_M)
  */
 uint16_t gf_square(uint16_t a) {
-	int16_t mask = (log[a] >> PARAM_M) - 1;
+	int16_t mask = (uint16_t) (-((int32_t) a) >> 31); // a != 0
 	return mask & exp[gf_mod(2 * log[a])];
 }
 
@@ -94,7 +53,8 @@
  * @param[in] a Element of GF(2^PARAM_M)
  */
 uint16_t gf_inverse(uint16_t a) {
-	return exp[PARAM_GF_MUL_ORDER - log[a]];
+	int16_t mask = (uint16_t) (-((int32_t) a) >> 31); // a != 0
+	return mask & exp[PARAM_GF_MUL_ORDER - log[a]];
 }
 
 
@@ -107,10 +67,10 @@
  * @param[in] i The integer whose modulo is taken
  */
 uint16_t gf_mod(uint16_t i) {
-	uint16_t tmp = i - PARAM_GF_MUL_ORDER;
+	uint16_t tmp = (uint16_t) (i - PARAM_GF_MUL_ORDER);
 
 	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
+	uint16_t mask = -(tmp >> 15);
 
 	return tmp + (mask & PARAM_GF_MUL_ORDER);
 }

