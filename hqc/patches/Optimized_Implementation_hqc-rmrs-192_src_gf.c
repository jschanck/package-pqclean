--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/gf.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/gf.c
@@ -9,50 +9,7 @@
 #include <wmmintrin.h>
 #include <stdint.h>
 
-uint16_t gf_reduce(uint64_t x, size_t deg_x);
-uint16_t gf_quad(uint64_t a);
-
-
-/**
- * @brief Generates exp and log lookup tables of GF(2^m).
- *
- * The logarithm of 0 is defined as 2^PARAM_M by convention. <br>
- * The last two elements of the exp table are needed by the gf_mul function from gf_lutmul.c
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
-	for (size_t i = 0 ; i < (1U << m) - 1 ; ++i){
-		exp[i] = elt;
-		log[elt] = i;
-
-		elt *= alpha;
-		if(elt >= 1 << m)
-			elt ^= gf_poly;
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
- * Returns the requested power of the primitive element of GF(2^GF_M).
- * @returns a^i
- */
-uint16_t gf_exp(uint16_t i) {
-	return exp[i];
-}
-
+static uint16_t gf_reduce(uint64_t x, size_t deg_x);
 
 
 /**
@@ -72,7 +29,7 @@
  * @param[in] x Polynomial of degree less than 64
  * @param[in] deg_x The degree of polynomial x
  */
-uint16_t gf_reduce(uint64_t x, size_t deg_x) {  
+static uint16_t gf_reduce(uint64_t x, size_t deg_x) {  
 	// Compute the distance between the primitive polynomial first two set bits
 	size_t lz1 = __builtin_clz(PARAM_GF_POLY);
 	size_t lz2 = __builtin_clz(PARAM_GF_POLY ^ 1<<PARAM_M);
@@ -167,10 +124,10 @@
  * @param[in] i The integer whose modulo is taken
  */
 uint16_t gf_mod(uint16_t i) {
-	uint16_t tmp = i - PARAM_GF_MUL_ORDER;
+	uint16_t tmp = (uint16_t) (i - PARAM_GF_MUL_ORDER);
 
 	// mask = 0xffff if (i < GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
+	uint16_t mask = -(tmp >> 15);
 
 	return tmp + (mask & PARAM_GF_MUL_ORDER);
-}
\ No newline at end of file
+}

