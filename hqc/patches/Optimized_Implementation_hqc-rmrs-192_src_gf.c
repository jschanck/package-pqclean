--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/gf.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/gf.c
@@ -9,60 +9,7 @@
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
-
-
-/**
- * Returns the integer i such that elt = a^i
- * where a is the primitive element of GF(2^GF_M).
- *@returns the logarithm of the given element
- */
-uint16_t gf_log(uint16_t elt) {
-	return log[elt];
-}
+static uint16_t gf_reduce(uint64_t x, size_t deg_x);
 
 
 
@@ -72,30 +19,29 @@
  * @param[in] x Polynomial of degree less than 64
  * @param[in] deg_x The degree of polynomial x
  */
-uint16_t gf_reduce(uint64_t x, size_t deg_x) {  
-	// Compute the distance between the primitive polynomial first two set bits
-	size_t lz1 = __builtin_clz(PARAM_GF_POLY);
-	size_t lz2 = __builtin_clz(PARAM_GF_POLY ^ 1<<PARAM_M);
-	size_t dist = lz2 - lz1;
+static uint16_t gf_reduce(uint64_t x, size_t deg_x) {  
+	uint16_t z1, z2, rmdr, dist;
+  uint64_t mod;
+  size_t steps, i, j;
 
 	// Deduce the number of steps of reduction
-	size_t steps = CEIL_DIVIDE(deg_x - (PARAM_M-1), dist);
+	steps = CEIL_DIVIDE(deg_x - (PARAM_M-1), PARAM_GF_POLY_M2);
 
 	// Reduce
-	for (size_t i = 0; i < steps; ++i) {
-		uint64_t mod = x >> PARAM_M;
+	for (i = 0; i < steps; ++i) {
+		mod = x >> PARAM_M;
 		x &= (1<<PARAM_M) - 1;
 		x ^= mod;
 
-		size_t tz1 = 0;
-		uint16_t rmdr = PARAM_GF_POLY ^ 1;
-		for (size_t j = __builtin_popcount(PARAM_GF_POLY)-2; j; --j) {      
-			size_t tz2 = __builtin_ctz(rmdr);
-			size_t shift = tz2 - tz1;
-			mod <<= shift;
+		z1 = 0;
+		rmdr = PARAM_GF_POLY ^ 1;
+		for (j = PARAM_GF_POLY_WT-2; j; --j) {      
+			z2 = __tzcnt_u16(rmdr);
+			dist = (uint16_t) (z2 - z1);
+			mod <<= dist;
 			x ^= mod;
-			rmdr ^= 1 << tz2;
-			tz1 = tz2;
+			rmdr ^= 1 << z2;
+			z1 = z2;
 		}
 	}
 
@@ -167,10 +113,10 @@
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

