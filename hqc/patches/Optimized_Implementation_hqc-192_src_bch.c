--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/bch.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/bch.c
@@ -17,135 +17,12 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(const uint16_t i, const uint16_t modulus);
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound);
 static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
 static void message_from_codeword(uint64_t *message, const uint64_t *codeword);
 static void compute_syndromes(__m256i* syndromes, const uint64_t * rcv);
 static void compute_roots(uint64_t *error, const uint16_t *sigma);
 
 /**
- * @brief Returns i modulo the given modulus.
- *
- * i must be less than 2*modulus.
- * Therefore, the return value is either i or i-modulus.
- * @returns i mod (modulus)
- * @param[in] i The integer whose modulo is taken
- * @param[in] modulus The modulus
- */
-static uint16_t mod(const uint16_t i, const uint16_t modulus) {
-	uint16_t tmp = i - modulus;
-
-	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
-
-	return tmp + (mask & modulus);
-}
-
-
-
-/**
- * @brief Computes the odd binary cyclotomic cosets modulo 2^m-1 for integers less than upper_bound.
- *
- * The array cosets of size 2^m-1 is filled by placing at index i the coset representative of i.
- * @param[out] cosets Array receiving the coset representatives
- * @param[in] upper_bound The upper bound
- */
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound) {
-	// Compute the odd cyclotomic classes
-	for (uint16_t i = 1 ; i < upper_bound ; i += 2) {
-		if (cosets[i] == 0) { // If i does not already belong to a class
-			uint16_t tmp = i;
-			size_t j = PARAM_M;
-			cosets[i] = i;
-			while(--j) { // Complete i's class
-				tmp = mod(2*tmp, PARAM_GF_MUL_ORDER);
-				cosets[tmp] = i;
-			}
-		}
-	}
-}
-
-
-
-/**
- * @brief Computes the generator polynomial of the primitive BCH code with given parameters.
- *
- * Code length is 2^m-1. <br>
- * Parameter t is the targeted correction capacity of the code
- * and receives the real correction capacity (which is at least equal to the target). <br>
- * exp and log are arrays giving antilog and log of GF(2^m) elements.
- * @returns the degree of the generator polynomial
- * @param[out] bch_poly Array of size (m*t + 1) receiving the coefficients of the generator polynomial
- * @param[in,out] t Targeted correction capacity; receives the real correction capacity
- * @param[in] exp Antilog table of GF(2^m)
- * @param[in] log Log table of GF(2^m)
- */
-size_t compute_bch_poly(uint16_t *bch_poly, size_t *t, const uint16_t *exp, const uint16_t *log) {
-	uint16_t cosets[PARAM_GF_MUL_ORDER];
-	size_t deg_bch_poly = 0;
-
-	memset(cosets, 0, 2 * PARAM_GF_MUL_ORDER);
-	compute_cyclotomic_cosets(cosets, 2 * *t);
-
-	// Start with bch_poly(X) = 1
-	bch_poly[0] = 1;
-
-	for (uint16_t i = 1 ; i < PARAM_GF_MUL_ORDER ; ++i) {
-		if(cosets[i] == 0) {
-			continue;
-		}
-
-		// Multiply bch_poly(X) by X-a^i
-		for (size_t j = deg_bch_poly ; j ; --j) {
-			int16_t mask = -((uint16_t)-bch_poly[j] >> 15);
-			bch_poly[j] = (mask & exp[mod(log[bch_poly[j]] + i, PARAM_GF_MUL_ORDER)]) ^ bch_poly[j - 1];
-		}
-		bch_poly[0] = exp[mod(log[bch_poly[0]] + i, PARAM_GF_MUL_ORDER)];
-		bch_poly[++deg_bch_poly] = 1;
-	}
-
-	// Determine the real correction capacity
-	while (cosets[2 * *t + 1] != 0) {
-		++*t;
-	}
-
-	return deg_bch_poly;
-}
-
-
-
-/**
- * @brief Computes the values alpha^ij for decoding syndromes
- *
- * function to initialize a table which contains values alpha^ij for i in [0,N1[ and j in [1,2*PARAM_DELTA]
- * these values are used in order to compute the syndromes of the received word v(x)=v_0+v_1x+...+v_{n1-1}x^{n1-1}
- * value alpha^ij is stored in alpha_ij_table[2*PARAM_DELTA*i+j-1]
- * The syndromes are equal to v(alpha^k) for k in [1,2*PARAM_DELTA]
- * Size of the table is fixed to match 256 bit representation
- * Useless values are filled with 0.
- *
- * @param[in] exp Exp look-up-table of GF
- */
-void table_alphaij_generation(const uint16_t *exp) {
-	int32_t tmp_value;
-	int16_t* alpha_tmp;
-
-	// pre-computation of alpha^ij for i in [0, N1[ and j in [1, 2*PARAM_DELTA]
-	// see comment of alpha_ij_table_init() function.
-	for(uint16_t i = 0; i < PARAM_N1 ; ++i) {
-		tmp_value = 0;
-		alpha_tmp = table_alpha_ij + i * (PARAM_DELTA << 1);
-		for(uint16_t j = 0 ; j < (PARAM_DELTA << 1) ; j++) {
-			tmp_value = gf_mod(tmp_value + i);
-			alpha_tmp[j] = exp[tmp_value];
-		}
-	}
-}
-
-
-
-/**
  * @brief Computes the error locator polynomial (ELP) sigma
  *
  * This is a constant time implementation of Berlekamp's simplified algorithm (see @cite joiner1995decoding). <br>
@@ -162,52 +39,54 @@
  * @param[in] syndromes Array of size (at least) 2*PARAM_DELTA storing the syndromes
  */
 static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes) {
-	sigma[0] = 1;
-	size_t deg_sigma = 0;
-	size_t deg_sigma_p = 0;
 	uint16_t sigma_copy[PARAM_DELTA - 1] = {0};
-	size_t deg_sigma_copy = 0;
-	uint16_t X_sigma_p[PARAM_DELTA + 1] = {0, 1};
-	int32_t pp = -1; // 2*rho
-	uint16_t d_p = 1;
-	uint16_t d = syndromes[0];
+	uint16_t X_sigma_p[PARAM_DELTA + 1] = {0};
+	uint16_t d_p, d, dd;
+	uint16_t mask;
+	int32_t pp; // 2*rho
+	size_t deg_sigma, deg_sigma_p, deg_sigma_copy, deg_X_sigma_p;
 
+	d = syndromes[0];
+	sigma[0] = 1;
+	X_sigma_p[1] = 1;
+	deg_sigma = 0;
+	deg_sigma_p = 0;
+	d_p = 1;
+	pp = -1;
 	for (size_t mu = 0 ; mu < PARAM_DELTA ; ++mu) {
 		// Save sigma in case we need it to update X_sigma_p
 		memcpy(sigma_copy, sigma, 2 * (PARAM_DELTA - 1));
 		deg_sigma_copy = deg_sigma;
 
-		uint16_t dd = gf_mul(d, gf_inverse(d_p)); // 0 if(d == 0)
+		dd = gf_mul(d, gf_inverse(d_p)); // 0 if(d == 0)
 		for (size_t i = 1 ; (i <= 2 * mu + 1) && (i <= PARAM_DELTA) ; ++i) {
 			sigma[i] ^= gf_mul(dd, X_sigma_p[i]);
 		}
 
-		size_t deg_X = 2 * mu - pp; // 2*(mu-rho)
-		size_t deg_X_sigma_p = deg_X + deg_sigma_p;
+		deg_X_sigma_p = 2 * mu - pp + deg_sigma_p;
 
-		// mask1 = 0xffff if(d != 0) and 0 otherwise
-		int16_t mask1 = -((uint16_t) - d >> 15);
+		// mask = 0xffff if(d != 0) and 0 otherwise
+		mask = -((uint16_t) - d >> 15);
 
-		// mask2 = 0xffff if(deg_X_sigma_p > deg_sigma) and 0 otherwise
-		int16_t mask2 = -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
+		// mask &= 0xffff if(deg_X_sigma_p > deg_sigma) and 0 otherwise
+		mask &= -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
 
-		// mask12 = 0xffff if the deg_sigma increased and 0 otherwise
-		int16_t mask12 = mask1 & mask2;
-		deg_sigma = (mask12 & deg_X_sigma_p) ^ (~mask12 & deg_sigma);
+		deg_sigma ^= mask & (deg_sigma ^ deg_X_sigma_p);
 
 		if (mu == PARAM_DELTA - 1) {
 			break;
 		}
 
 		// Update pp, d_p and X_sigma_p if needed
-		pp = (mask12 & (2 * mu)) ^ (~mask12 & pp);
-		d_p = (mask12 & d) ^ (~mask12 & d_p);
+		pp ^= mask & (pp ^ (2 * mu));
+		d_p ^= mask & (d_p ^ d);
 		for (size_t i = PARAM_DELTA - 1 ; i ; --i) {
-			X_sigma_p[i + 1] = (mask12 & sigma_copy[i - 1]) ^ (~mask12 & X_sigma_p[i - 1]);
+			X_sigma_p[i+1] = X_sigma_p[i-1];
+			X_sigma_p[i+1] ^= mask & (X_sigma_p[i+1] ^ sigma_copy[i-1]);
 		}
 		X_sigma_p[1] = 0;
 		X_sigma_p[0] = 0;
-		deg_sigma_p = (mask12 & deg_sigma_copy) ^ (~mask12 & deg_sigma_p);
+		deg_sigma_p ^= mask & (deg_sigma_p ^ deg_sigma_copy);
 
 		// Compute the next discrepancy
 		d = syndromes[2 * mu + 2];
@@ -230,31 +109,23 @@
  * @param[in] codeword Array of size VEC_N1_SIZE_BYTES storing the codeword
  */
 static void message_from_codeword(uint64_t *message, const uint64_t *codeword) {
-	int32_t val = PARAM_N1 - PARAM_K;
-
-	uint64_t mask1 = (uint64_t) (0xffffffffffffffff << val % 64);
-	uint64_t mask2 = (uint64_t) (0xffffffffffffffff >> (64 - val % 64));
-	size_t index = val / 64;
+	uint64_t mask1 = (uint64_t) (0xffffffffffffffff << ((PARAM_N1 - PARAM_K)%64));
+	uint64_t mask2 = (uint64_t) (0xffffffffffffffff >> (64 - (PARAM_N1 - PARAM_K)%64));
+	size_t index = (PARAM_N1 - PARAM_K) / 64;
 
 	for (size_t i = 0 ; i < VEC_K_SIZE_64 - 1 ; ++i) {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		uint64_t message2 = (codeword[++index] & mask2) << (64 - val % 64);
-		message[i] = message1 | message2;
+		message[i] = (codeword[index] & mask1) >> ((PARAM_N1 - PARAM_K) % 64);
+		message[i] |= (codeword[++index] & mask2) << (64 - (PARAM_N1 - PARAM_K)%64);
 	}
 
 	// Last byte (8-val % 8 is the number of bits given by message1)
-	if ((PARAM_K % 64 == 0) || (64 - val % 64 < PARAM_K % 64)) {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		uint64_t message2 = (codeword[++index] & mask2) << (64 - val % 64);
-		message[VEC_K_SIZE_64 - 1] = message1 | message2;
-	} else {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		message[VEC_K_SIZE_64 - 1] = message1;
-	}
+	message[VEC_K_SIZE_64 - 1] = (codeword[index] & mask1) >> ((PARAM_N1 - PARAM_K) % 64);
+	++index;
+	if (index < VEC_N1_SIZE_64)
+		message[VEC_K_SIZE_64 - 1] |= (codeword[index] & mask2) << (64 - (PARAM_N1 - PARAM_K)%64);
 }
 
 
-
 /**
  * @brief Computes the 2^PARAM_DELTA syndromes from the received vector vector
  *
@@ -267,10 +138,10 @@
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
@@ -278,7 +149,8 @@
 	__m256i tmp_repeat;
 	uint32_t *aux;
 	int16_t *alpha_tmp;
-	uint32_t i;
+	size_t i, j;
+	uint32_t nzflag;
 	// static variable so that it is stored in the DATA segment
 	// not in the STACK segment
 	static uint8_t tmp_array[PARAM_N1 + 4]; // +4 to control overflow due to management of 256 bits
@@ -298,12 +170,13 @@
 	}
 
 	// Evaluation of the polynomial corresponding to the vector v in alpha^i for i in {1, ..., 2 * PARAM_DELTA}
-	for (uint16_t j = 0 ; j < SYND_SIZE_256 ; ++j) {
+	for (j = 0 ; j < SYND_SIZE_256 ; ++j) {
 		S = zero_256;
 		alpha_tmp = table_alpha_ij + (j << 4);
 
-		for (uint16_t i = 0 ; i < PARAM_N1 ; ++i) {
-			tmp_repeat = _mm256_set1_epi64x((long long)(tmp_array[i]!=0));
+		for (i = 0 ; i < PARAM_N1 ; ++i) {
+			nzflag = ((-(int32_t) tmp_array[i]) >> 31) & 1;
+			tmp_repeat = _mm256_set1_epi64x(nzflag);
 			L = _mm256_cmpeq_epi64(tmp_repeat,un_256);
 			tmp_repeat = _mm256_lddqu_si256((__m256i *)(alpha_tmp + i * (PARAM_DELTA << 1)));
 			L = _mm256_and_si256(L,tmp_repeat);

