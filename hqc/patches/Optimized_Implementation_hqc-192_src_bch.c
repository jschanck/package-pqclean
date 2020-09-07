--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/bch.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/bch.c
@@ -17,8 +17,8 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(const uint16_t i, const uint16_t modulus);
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound);
+static uint16_t mod(uint16_t i, uint16_t modulus);
+static void compute_cyclotomic_cosets(uint16_t *cosets, uint16_t upper_bound);
 static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
 static void message_from_codeword(uint64_t *message, const uint64_t *codeword);
 static void compute_syndromes(__m256i* syndromes, const uint64_t * rcv);
@@ -33,7 +33,7 @@
  * @param[in] i The integer whose modulo is taken
  * @param[in] modulus The modulus
  */
-static uint16_t mod(const uint16_t i, const uint16_t modulus) {
+static uint16_t mod(uint16_t i, uint16_t modulus) {
 	uint16_t tmp = i - modulus;
 
 	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
@@ -51,7 +51,7 @@
  * @param[out] cosets Array receiving the coset representatives
  * @param[in] upper_bound The upper bound
  */
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound) {
+static void compute_cyclotomic_cosets(uint16_t *cosets, uint16_t upper_bound) {
 	// Compute the odd cyclotomic classes
 	for (uint16_t i = 1 ; i < upper_bound ; i += 2) {
 		if (cosets[i] == 0) { // If i does not already belong to a class
@@ -267,10 +267,10 @@
  * @param[in] rcv Array of size VEC_N1_SIZE_BYTES storing the received word
  */
 void compute_syndromes(__m256i *syndromes, const uint64_t *rcv) {
-	static const __m256i zero_256 = {0UL,0UL,0UL,0UL};
-	static const __m256i mask_one = {0x0UL, 0x0101010101010101UL, 0x0202020202020202UL, 0x0303030303030303UL};
-	static const __m256i mask_two  = {0x8040201008040201UL, 0x8040201008040201UL,0x8040201008040201UL,0x8040201008040201UL};
-	static const __m256i un_256 = {1UL, 1UL, 1UL, 1UL};
+	const __m256i zero_256 = _mm256_set1_epi64x(0);
+	const __m256i mask_one = _mm256_set_epi64x(0x0303030303030303,0x0202020202020202,0x0101010101010101,0x0);
+	const __m256i mask_two  = _mm256_set1_epi64x(-0x7FBFDFEFF7FBFDFF);
+	const __m256i un_256 = _mm256_set1_epi64x(1);
 
 	__m256i y;
 	__m256i S;
@@ -298,11 +298,11 @@
 	}
 
 	// Evaluation of the polynomial corresponding to the vector v in alpha^i for i in {1, ..., 2 * PARAM_DELTA}
-	for (uint16_t j = 0 ; j < SYND_SIZE_256 ; ++j) {
+	for (size_t j = 0 ; j < SYND_SIZE_256 ; ++j) {
 		S = zero_256;
 		alpha_tmp = table_alpha_ij + (j << 4);
 
-		for (uint16_t i = 0 ; i < PARAM_N1 ; ++i) {
+		for (size_t i = 0 ; i < PARAM_N1 ; ++i) {
 			tmp_repeat = _mm256_set1_epi64x((long long)(tmp_array[i]!=0));
 			L = _mm256_cmpeq_epi64(tmp_repeat,un_256);
 			tmp_repeat = _mm256_lddqu_si256((__m256i *)(alpha_tmp + i * (PARAM_DELTA << 1)));

