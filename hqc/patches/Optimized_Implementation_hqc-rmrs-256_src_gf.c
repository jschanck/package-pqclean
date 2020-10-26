--- upstream/Optimized_Implementation/hqc-rmrs-256/src/gf.c
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-256/src/gf.c
@@ -7,60 +7,7 @@
 #include "parameters.h"
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
 
 
 
@@ -70,30 +17,29 @@
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
+	uint64_t mod;
+	size_t steps, i, j;
 
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
 
@@ -132,38 +78,38 @@
 	__m128i bl = _mm256_extractf128_si256(b, 0);
 	__m128i bh = _mm256_extractf128_si256(b, 1);
 	
-	__m128i abl0 = _mm_clmulepi64_si128(al & maskl, bl & maskl, 0x0);
-	abl0 &= middlemaskl;
-	abl0 ^= (_mm_clmulepi64_si128(al & maskh, bl & maskh, 0x0) & middlemaskh);
-	
-	__m128i abh0 = _mm_clmulepi64_si128(al & maskl, bl & maskl, 0x11);
-	abh0 &= middlemaskl;
-	abh0 ^= (_mm_clmulepi64_si128(al & maskh, bl & maskh, 0x11) & middlemaskh);
-
-	abl0 = _mm_shuffle_epi8(abl0, indexl);
-	abl0 ^= _mm_shuffle_epi8(abh0, indexh);
-	
-	__m128i abl1 = _mm_clmulepi64_si128(ah & maskl, bh & maskl, 0x0);
-	abl1 &= middlemaskl;
-	abl1 ^= (_mm_clmulepi64_si128(ah & maskh, bh & maskh, 0x0) & middlemaskh);
-	
-	__m128i abh1 = _mm_clmulepi64_si128(ah & maskl, bh & maskl, 0x11);
-	abh1 &= middlemaskl;
-	abh1 ^= (_mm_clmulepi64_si128(ah & maskh, bh & maskh, 0x11) & middlemaskh);
+	__m128i abl0 = _mm_clmulepi64_si128(al & CONST128_MASKL, bl & CONST128_MASKL, 0x0);
+	abl0 &= CONST128_MIDDLEMASKL;
+	abl0 ^= (_mm_clmulepi64_si128(al & CONST128_MASKH, bl & CONST128_MASKH, 0x0) & CONST128_MIDDLEMASKH);
+	
+	__m128i abh0 = _mm_clmulepi64_si128(al & CONST128_MASKL, bl & CONST128_MASKL, 0x11);
+	abh0 &= CONST128_MIDDLEMASKL;
+	abh0 ^= (_mm_clmulepi64_si128(al & CONST128_MASKH, bl & CONST128_MASKH, 0x11) & CONST128_MIDDLEMASKH);
+
+	abl0 = _mm_shuffle_epi8(abl0, CONST128_INDEXL);
+	abl0 ^= _mm_shuffle_epi8(abh0, CONST128_INDEXH);
+	
+	__m128i abl1 = _mm_clmulepi64_si128(ah & CONST128_MASKL, bh & CONST128_MASKL, 0x0);
+	abl1 &= CONST128_MIDDLEMASKL;
+	abl1 ^= (_mm_clmulepi64_si128(ah & CONST128_MASKH, bh & CONST128_MASKH, 0x0) & CONST128_MIDDLEMASKH);
+	
+	__m128i abh1 = _mm_clmulepi64_si128(ah & CONST128_MASKL, bh & CONST128_MASKL, 0x11);
+	abh1 &= CONST128_MIDDLEMASKL;
+	abh1 ^= (_mm_clmulepi64_si128(ah & CONST128_MASKH, bh & CONST128_MASKH, 0x11) & CONST128_MIDDLEMASKH);
 
-	abl1 = _mm_shuffle_epi8(abl1, indexl);
-	abl1 ^= _mm_shuffle_epi8(abh1, indexh);
+	abl1 = _mm_shuffle_epi8(abl1, CONST128_INDEXL);
+	abl1 ^= _mm_shuffle_epi8(abh1, CONST128_INDEXH);
 	
 	__m256i ret = _mm256_set_m128i(abl1, abl0);
 	
-	__m256i aux = mr0;
+	__m256i aux = CONST256_MR0;
 	
 	for (int32_t i = 0 ; i < 7 ; i++) {
 		ret ^= red[i] & _mm256_cmpeq_epi16((ret & aux), aux);
 		aux = aux << 1;
 	}
 	
-	ret &= lastMask;
+	ret &= CONST256_LASTMASK;
 	return ret;
 }
 
@@ -221,10 +167,10 @@
  * @param[in] i The integer whose modulo is taken
  */
 uint16_t gf_mod(uint16_t i) {
-	uint16_t tmp = i - PARAM_GF_MUL_ORDER;
+	uint16_t tmp = (uint16_t) (i - PARAM_GF_MUL_ORDER);
 
 	// mask = 0xffff if (i < GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
+	uint16_t mask = -(tmp >> 15);
 
 	return tmp + (mask & PARAM_GF_MUL_ORDER);
 }

