--- upstream/Optimized_Implementation/hqc-rmrs-256/src/reed_solomon.c
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-256/src/reed_solomon.c
@@ -7,6 +7,7 @@
 #include "gf.h"
 #include "reed_solomon.h"
 #include "parameters.h"
+#include "parsing.h"
 #include <stdint.h>
 #include <string.h>
 #include <stdio.h>
@@ -15,11 +16,10 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(uint16_t i, uint16_t modulus);
 static void compute_syndromes(uint16_t* syndromes, uint8_t* cdw);
-static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
+static uint16_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
 static void compute_roots(uint8_t* error, uint16_t* sigma);
-static void compute_z_poly(uint16_t* z, const uint16_t* sigma, const uint8_t degree, const uint16_t* syndromes);
+static void compute_z_poly(uint16_t* z, const uint16_t* sigma, uint16_t degree, const uint16_t* syndromes);
 static void compute_error_values(uint16_t* error_values, const uint16_t* z, const uint8_t* error);
 static void correct_errors(uint8_t* cdw, const uint16_t* error_values);
 
@@ -389,60 +389,6 @@
 };
 
 
-
-/**
- * Returns i modulo the given modulus.
- * i must be less than 2*modulus.
- * Therefore, the return value is either i or i-modulus.
- * @returns i mod (modulus)
- * @param[in] i The integer whose modulo is taken
- * @param[in] modulus The modulus
- */
-static uint16_t mod(uint16_t i, uint16_t modulus) {
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
- * @brief Computes the generator polynomial of the primitive Reed-Solomon code with given parameters.
- *
- * Code length is 2^m-1. <br>
- * PARAM_DELTA is the targeted correction capacity of the code
- * and receives the real correction capacity (which is at least equal to the target). <br>
- * exp and log are arrays giving antilog and log of GF(2^m) elements.
- *
- * @param[out] poly Array of size (2*PARAM_DELTA + 1) receiving the coefficients of the generator polynomial
- */
-void compute_generator_poly(uint16_t* poly) {
-	poly[0] = 1;
-	int tmp_degree = 0;
-
-	for (uint16_t i = 1 ; i < (2 * PARAM_DELTA + 1) ; ++i) {
-
-		for(size_t j = tmp_degree ; j ; --j) {
-			poly[j] = exp[mod(log[poly[j]] + i, PARAM_GF_MUL_ORDER)] ^ poly[j - 1];
-		}
-
-		poly[0] = exp[mod(log[poly[0]] + i, PARAM_GF_MUL_ORDER)];
-		poly[++tmp_degree] = 1;
-
-	}
-
-	printf("\n");
-	for (int i = 0 ; i < (PARAM_G) ; ++i) {
-		printf("%d, ", poly[i]);
-	}
-	printf("\n");
-}
-
-
-
 /**
  * @brief Encodes a message message of PARAM_K bits to a Reed-Solomon codeword codeword of PARAM_N1 bytes
  *
@@ -453,37 +399,40 @@
  * @param[out] cdw Array of size VEC_N1_SIZE_64 receiving the encoded message
  * @param[in] msg Array of size VEC_K_SIZE_64 storing the message
  */
-void reed_solomon_encode(uint64_t *cdw, const uint64_t *msg) {
+void reed_solomon_encode(uint8_t* cdw, const uint8_t* msg) {
+	size_t i, k;
 	uint8_t gate_value = 0;
+	uint8_t prev, x;
 
-	uint16_t tmp[PARAM_G + 5] = {0};
-	uint16_t PARAM_RS_POLY [] = {RS_POLY_COEFS,0,0,0,0,0};  //+5 to fit 256 bit registers
-
-	uint8_t msg_bytes[PARAM_K] = {0};
-	uint8_t cdw_bytes[PARAM_N1] = {0};
-
-	__m256i *tmp256 = (__m256i *)tmp;
-	__m256i *param256 = (__m256i *)PARAM_RS_POLY;
-
-	memcpy(msg_bytes, msg, PARAM_K);
-
-	for (int32_t i = PARAM_K - 1 ; i >= 0 ; --i) {
-		gate_value = msg_bytes[i] ^ cdw_bytes[PARAM_N1 - PARAM_K - 1];
-		__m256i gate256 = _mm256_set1_epi16(gate_value);
-		tmp256[0] = gf_mul_vect(gate256, param256[0]);
-		tmp256[1] = gf_mul_vect(gate256, param256[1]);
-		tmp256[2] = gf_mul_vect(gate256, param256[2]);
-		tmp256[3] = gf_mul_vect(gate256, param256[3]);
-	
-		for (size_t k = PARAM_N1 - PARAM_K - 1 ; k ; --k) {
-			cdw_bytes[k] = cdw_bytes[k - 1] ^ tmp[k];
-		}
-
-		cdw_bytes[0] = tmp[0];
+	union {
+		uint16_t arr16[16 * CEIL_DIVIDE(PARAM_G,16)];
+		__m256i dummy;
+	} tmp = {0};
+
+	union {
+		uint16_t arr16[16 * CEIL_DIVIDE(PARAM_G,16)];
+		__m256i dummy;
+	} PARAM_RS_POLY = {{ RS_POLY_COEFS }};
+
+	__m256i *tmp256 = (__m256i *)tmp.arr16;
+	__m256i *param256 = (__m256i *)PARAM_RS_POLY.arr16;
+
+	for (i = 0 ; i < PARAM_K ; ++i) {
+		gate_value = (uint8_t) (msg[PARAM_K-1-i] ^ cdw[PARAM_N1 - PARAM_K - 1]);
+		_mm256_storeu_si256(&tmp256[0], gf_mul_vect(_mm256_set1_epi16(gate_value), param256[0]));
+		_mm256_storeu_si256(&tmp256[1], gf_mul_vect(_mm256_set1_epi16(gate_value), param256[1]));
+		_mm256_storeu_si256(&tmp256[2], gf_mul_vect(_mm256_set1_epi16(gate_value), param256[2]));
+		_mm256_storeu_si256(&tmp256[3], gf_mul_vect(_mm256_set1_epi16(gate_value), param256[3]));
+
+		prev = 0;
+		for(k = 0 ; k < PARAM_N1-PARAM_K; k++) {
+			x = cdw[k];
+			cdw[k] = (uint8_t) (prev ^ tmp.arr16[k]);
+			prev = x;
+ 		}
 	}
 
-	memcpy(cdw_bytes + PARAM_N1 - PARAM_K, msg_bytes, PARAM_K);
-	memcpy(cdw, cdw_bytes, PARAM_N1);
+	memcpy(cdw + PARAM_N1 - PARAM_K, msg, PARAM_K);
 }
 
 
@@ -496,9 +445,10 @@
  */
 void compute_syndromes(uint16_t *syndromes, uint8_t *cdw) {
 	__m256i *syndromes256 = (__m256i *) syndromes;
-	
+	__m256i last_syndromes256;
 	syndromes256[0] = _mm256_set1_epi16(cdw[0]);
- 	for (size_t i = 0 ; i < PARAM_N1 - 1 ; ++i) {
+
+	for (size_t i = 0 ; i < PARAM_N1 - 1 ; ++i) {
 		syndromes256[0] ^= gf_mul_vect(_mm256_set1_epi16(cdw[i + 1]), alpha_ij256_1[i]);
 	}
 
@@ -512,7 +462,7 @@
 		syndromes256[2] ^= gf_mul_vect(_mm256_set1_epi16(cdw[i + 1]), alpha_ij256_3[i]);
 	}
 
-	__m256i last_syndromes256 = _mm256_set1_epi16(cdw[0]);
+	last_syndromes256 = _mm256_set1_epi16(cdw[0]);
 	for (size_t i = 0 ; i < PARAM_N1 - 1 ; ++i) {
 		last_syndromes256 ^= gf_mul_vect(_mm256_set1_epi16(cdw[i + 1]), alpha_ij256_4[i]);
 	}
@@ -543,55 +493,62 @@
  * @param[out] sigma Array of size (at least) PARAM_DELTA receiving the ELP
  * @param[in] syndromes Array of size (at least) 2*PARAM_DELTA storing the syndromes
  */
-static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes) {
-	sigma[0] = 1;
-	size_t deg_sigma = 0;
-	size_t deg_sigma_p = 0;
+static uint16_t compute_elp(uint16_t *sigma, const uint16_t *syndromes) {
+	uint16_t deg_sigma = 0;
+	uint16_t deg_sigma_p = 0;
+	uint16_t deg_sigma_copy = 0;
 	uint16_t sigma_copy[PARAM_DELTA + 1] = {0};
-	size_t deg_sigma_copy = 0;
 	uint16_t X_sigma_p[PARAM_DELTA + 1] = {0,1};
-	int32_t pp = -1; // 2*rho
+	uint16_t pp = (uint16_t) -1; // 2*rho
 	uint16_t d_p = 1;
 	uint16_t d = syndromes[0];
 
-	for (size_t mu = 0 ; (mu < (2 * PARAM_DELTA)) ; ++mu) {
+	uint16_t mask1, mask2, mask12;
+	uint16_t deg_X, deg_X_sigma_p;
+	uint16_t dd;
+	uint16_t mu;
+
+	uint16_t i;
+
+	sigma[0] = 1;
+	for (mu = 0 ; (mu < (2 * PARAM_DELTA)) ; ++mu) {
 		// Save sigma in case we need it to update X_sigma_p
 		memcpy(sigma_copy, sigma, 2 * (PARAM_DELTA));
 		deg_sigma_copy = deg_sigma;
 
-		uint16_t dd = gf_mul(d, gf_inverse(d_p));
+		dd = gf_mul(d, gf_inverse(d_p));
 
-		for (size_t i = 1 ; (i <= mu + 1) && (i <= PARAM_DELTA) ; ++i) {
+		for (i = 1 ; (i <= mu + 1) && (i <= PARAM_DELTA) ; ++i) {
 			sigma[i] ^= gf_mul(dd, X_sigma_p[i]);
 		}
 
-		size_t deg_X = mu - pp;
-		size_t deg_X_sigma_p = deg_X + deg_sigma_p;
+		deg_X = mu - pp;
+		deg_X_sigma_p = deg_X + deg_sigma_p;
 
 		// mask1 = 0xffff if(d != 0) and 0 otherwise
-		int16_t mask1 = -((uint16_t) - d >> 15);
+		mask1 = -((uint16_t) - d >> 15);
 
 		// mask2 = 0xffff if(deg_X_sigma_p > deg_sigma) and 0 otherwise
-		int16_t mask2 = -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
+		mask2 = -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
 
 		// mask12 = 0xffff if the deg_sigma increased and 0 otherwise
-		int16_t mask12 = mask1 & mask2;
-		deg_sigma = (mask12 & deg_X_sigma_p) ^ (~mask12 & deg_sigma);
+		mask12 = mask1 & mask2;
+		deg_sigma ^= mask12 & (deg_X_sigma_p^deg_sigma);
 
 		if (mu == (2 * PARAM_DELTA - 1)) {
 			break;
 		}
 
-		pp = (mask12 & mu) ^ (~mask12 & pp);
-		d_p = (mask12 & d) ^ (~mask12 & d_p);
-		for (size_t i = PARAM_DELTA ; i ; --i) {
+		pp ^= mask12 & (mu^pp);
+		d_p ^= mask12 & (d^d_p);
+		for (i = PARAM_DELTA ; i ; --i) {
 			X_sigma_p[i] = (mask12 & sigma_copy[i - 1]) ^ (~mask12 & X_sigma_p[i - 1]);
 		}
 
-		deg_sigma_p = (mask12 & deg_sigma_copy) ^ (~mask12 & deg_sigma_p);
+		deg_sigma_p ^= mask12 & (deg_sigma_copy^deg_sigma_p);
 		d = syndromes[mu + 1];
 
-		for (size_t i = 1 ; (i <= mu+1) && (i <= PARAM_DELTA) ; ++i) {
+		for (i = 1 ; (i <= mu+1) && (i <= PARAM_DELTA) ; ++i) {
 			d ^= gf_mul(sigma[i], syndromes[mu + 1 - i]);
 		}
 	}
@@ -629,22 +586,25 @@
  * @param[in] degree Integer that is the degree of polynomial sigma
  * @param[in] syndromes Array of 2 * PARAM_DELTA storing the syndromes
  */
-static void compute_z_poly(uint16_t* z, const uint16_t* sigma, const uint8_t degree, const uint16_t* syndromes) {
+static void compute_z_poly(uint16_t* z, const uint16_t* sigma, uint16_t degree, const uint16_t* syndromes) {
+	size_t i, j;
+	uint16_t mask;
+
 	z[0] = 1;
 
-	for (size_t i = 1 ; i < PARAM_DELTA + 1 ; ++i) {
-		int16_t mask2 = -((uint16_t) (i - degree - 1) >> 15);
-		z[i] = ((uint16_t)mask2) & sigma[i];
+	for (i = 1 ; i < PARAM_DELTA + 1 ; ++i) {
+		mask = -((uint16_t) (i - degree - 1) >> 15);
+		z[i] = mask & sigma[i];
 	}
 
 	z[1] ^= syndromes[0];
 
-	for (size_t i = 2 ; i <= PARAM_DELTA ; ++i) {
-		int16_t mask2 = -((uint16_t) (i - degree - 1) >> 15);
-		z[i] ^= ((uint16_t)mask2 & syndromes[i-1]);
+	for (i = 2 ; i <= PARAM_DELTA ; ++i) {
+		mask = -((uint16_t) (i - degree - 1) >> 15);
+		z[i] ^= mask & syndromes[i-1];
 
-		for (size_t j = 1 ; j < i ; ++j) {
-			z[i] ^= ((uint16_t)mask2) & gf_mul(sigma[j], syndromes[i - j - 1]);
+		for (j = 1 ; j < i ; ++j) {
+			z[i] ^= mask & gf_mul(sigma[j], syndromes[i - j - 1]);
 		}
 	}
 }
@@ -665,17 +625,25 @@
 	uint16_t beta_j[PARAM_DELTA] = {0};
 	uint16_t e_j[PARAM_DELTA] = {0};
 
-	uint16_t delta_counter = 0;
+	uint16_t delta_counter;
 	uint16_t delta_real_value;
+	uint16_t found;
+	uint16_t mask1;
+	uint16_t mask2;
+	uint16_t tmp1;
+	uint16_t tmp2;
+	uint16_t inverse;
+	uint16_t inverse_power_j;
 
 	// Compute the beta_{j_i} page 31 of the documentation
+	delta_counter = 0;
 	for (size_t i = 0 ; i < PARAM_N1 ; i++) {
-		uint16_t found = 0;
-		int16_t valuemask = ((int16_t) -(error[i] != 0)) >> 15;
+		found = 0;
+		mask1 = (uint16_t) (-((int32_t)error[i])>>31); // error[i] != 0
 		for (size_t j = 0 ; j < PARAM_DELTA ; j++) {
-			int16_t indexmask = ((int16_t) -(j == delta_counter)) >> 15;
-			beta_j[j] += indexmask & valuemask & exp[i];
-			found += indexmask & valuemask & 1;
+			mask2 = ~((uint16_t) (-((int32_t) j^delta_counter) >> 31)); // j == delta_counter
+			beta_j[j] += mask1 & mask2 & gf_exp[i];
+			found += mask1 & mask2 & 1;
 		}
 		delta_counter += found;
 	}
@@ -683,10 +651,10 @@
 
 	// Compute the e_{j_i} page 31 of the documentation
 	for (size_t i = 0 ; i < PARAM_DELTA ; ++i) {
-		uint16_t tmp1 = 1;
-		uint16_t tmp2 = 1;
-		uint16_t inverse = gf_inverse(beta_j[i]);
-		uint16_t inverse_power_j = 1;
+		tmp1 = 1;
+		tmp2 = 1;
+		inverse = gf_inverse(beta_j[i]);
+		inverse_power_j = 1;
 
 		for (size_t j = 1 ; j <= PARAM_DELTA ; ++j) {
 			inverse_power_j = gf_mul(inverse_power_j, inverse);
@@ -695,19 +663,19 @@
 		for (size_t k = 1 ; k < PARAM_DELTA ; ++k) {
 			tmp2 = gf_mul(tmp2, (1 ^ gf_mul(inverse, beta_j[(i+k) % PARAM_DELTA])));
 		}
-		int16_t mask = ((int16_t) -(i<delta_real_value))>>15;
-		e_j[i] = mask & gf_mul(tmp1,gf_inverse(tmp2));
+		mask1 = (uint16_t) (((int16_t) i-delta_real_value)>>15); // i < delta_real_value
+		e_j[i] = mask1 & gf_mul(tmp1,gf_inverse(tmp2));
 	}
 
 	// Place the delta e_{j_i} values at the right coordinates of the output vector
 	delta_counter = 0;
 	for (size_t i = 0 ; i < PARAM_N1 ; ++i) {
-		uint16_t found = 0;
-		int16_t valuemask = ((int16_t) -(error[i] !=0)) >> 15;
+		found = 0;
+		mask1 = (uint16_t) (-((int32_t)error[i])>>31); // error[i] != 0
 		for (size_t j = 0 ; j < PARAM_DELTA ; j++) {
-			int16_t indexmask = ((int16_t) -(j == delta_counter)) >> 15;
-			error_values[i] += indexmask & valuemask & e_j[j];
-			found += indexmask & valuemask & 1;
+			mask2 = ~((uint16_t) (-((int32_t) j^delta_counter) >> 31)); // j == delta_counter
+			error_values[i] += mask1 & mask2 & e_j[j];
+			found += mask1 & mask2 & 1;
 		}
 		delta_counter += found;
 	}
@@ -747,23 +715,20 @@
  * @param[out] msg Array of size VEC_K_SIZE_64 receiving the decoded message
  * @param[in] cdw Array of size VEC_N1_SIZE_64 storing the received word
  */
-void reed_solomon_decode(uint64_t* msg, uint64_t* cdw) {
-	uint8_t cdw_bytes[PARAM_N1] = {0};
+void reed_solomon_decode(uint8_t* msg, uint8_t* cdw) {
 	uint16_t syndromes[2 * PARAM_DELTA] = {0};
 	uint16_t sigma[1 << PARAM_FFT] = {0};
 	uint8_t error[1 << PARAM_M] = {0};
 	uint16_t z[PARAM_N1] = {0};
 	uint16_t error_values[PARAM_N1] = {0};
-
-	// Copy the vector in an array of bytes
-	memcpy(cdw_bytes, cdw, PARAM_N1);
+	uint16_t deg;
 
 	// Calculate the 2*PARAM_DELTA syndromes
-	compute_syndromes(syndromes, cdw_bytes);
+	compute_syndromes(syndromes, cdw);
 
 	// Compute the error locator polynomial sigma
 	// Sigma's degree is at most PARAM_DELTA but the FFT requires the extra room
-	size_t deg = compute_elp(sigma, syndromes);
+	deg = compute_elp(sigma, syndromes);
 
 	// Compute the error polynomial error
 	compute_roots(error, sigma);
@@ -775,10 +740,10 @@
 	compute_error_values(error_values, z, error);
 
 	// Correct the errors
-	correct_errors(cdw_bytes, error_values);
+	correct_errors(cdw, error_values);
 
 	// Retrieve the message from the decoded codeword
-	memcpy(msg, cdw_bytes + (PARAM_G - 1) , PARAM_K);
+	memcpy(msg, cdw + (PARAM_G - 1) , PARAM_K);
 
 #ifdef VERBOSE
 	printf("\n\nThe syndromes: ");

