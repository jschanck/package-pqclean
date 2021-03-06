--- upstream/Reference_Implementation/hqc-rmrs-192/src/fft.c
+++ upstream-patched/Reference_Implementation/hqc-rmrs-192/src/fft.c
@@ -15,9 +15,10 @@
 #include <stdint.h>
 #include <string.h>
 
-static void compute_fft_betas(uint16_t* betas);
-static void compute_subset_sums(uint16_t* subset_sums, uint16_t* set, size_t set_size);
-static void radix(uint16_t* f0, uint16_t* f1, const uint16_t* f, uint32_t m_f);
+static void compute_fft_betas(uint16_t *betas);
+static void compute_subset_sums(uint16_t *subset_sums, const uint16_t *set, uint16_t set_size);
+static void radix(uint16_t *f0, uint16_t *f1, const uint16_t *f, uint32_t m_f);
+static void radix_big(uint16_t *f0, uint16_t *f1, const uint16_t *f, uint32_t m_f);
 static void fft_rec(uint16_t *w, uint16_t *f, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas);
 
 
@@ -26,8 +27,9 @@
  *
  * @param[out] betas Array of size PARAM_M-1
  */
-static void compute_fft_betas(uint16_t* betas) {
-	for(size_t i = 0 ; i < PARAM_M - 1 ; ++i) {
+static void compute_fft_betas(uint16_t *betas) {
+	size_t i;
+	for (i = 0 ; i < PARAM_M - 1 ; ++i) {
 		betas[i] = 1 << (PARAM_M - 1 - i);
 	}
 }
@@ -44,11 +46,12 @@
  * @param[in] set Array of set_size elements
  * @param[in] set_size Size of the array set
  */
-static void compute_subset_sums(uint16_t* subset_sums, uint16_t* set, size_t set_size) {
+static void compute_subset_sums(uint16_t *subset_sums, const uint16_t *set, uint16_t set_size) {
+	uint16_t i, j;
 	subset_sums[0] = 0;
 
-	for(size_t i = 0 ; i < set_size ; ++i) {
-		for(size_t j = 0 ; j < (1U << i) ; ++j) {
+	for (i = 0 ; i < set_size ; ++i) {
+		for (j = 0 ; j < (1<<i) ; ++j) {
 			subset_sums[(1 << i) + j] = set[i] ^ subset_sums[j];
 		}
 	}
@@ -88,7 +91,7 @@
 			f1[2] = f[3] ^ f1[1] ^ f0[3];
 			f0[1] = f[2] ^ f0[2] ^ f1[1];
 			f1[0] = f[1] ^ f0[1];
-			return;
+			break;
 
 		case 3:
 			f0[0] = f[0];
@@ -99,49 +102,55 @@
 			f1[3] = f[7];
 			f0[1] = f[2] ^ f0[2] ^ f1[1];
 			f1[0] = f[1] ^ f0[1];
-			return;
+			break;
 
 		case 2:
 			f0[0] = f[0];
 			f0[1] = f[2] ^ f[3];
 			f1[0] = f[1] ^ f0[1];
 			f1[1] = f[3];
-			return;
+			break;
 
 		case 1:
 			f0[0] = f[0];
 			f1[0] = f[1];
-			return;
+			break;
 
 		default:
-			;
-			size_t n = 1 << (m_f - 2);
-
-			uint16_t Q[2 * (1 << (PARAM_FFT - 2))];
-			uint16_t R[2 * (1 << (PARAM_FFT - 2))];
+			radix_big(f0, f1, f, m_f);
+			break;
+	}
+}
 
-			uint16_t Q0[1 << (PARAM_FFT - 2)];
-			uint16_t Q1[1 << (PARAM_FFT - 2)];
-			uint16_t R0[1 << (PARAM_FFT - 2)];
-			uint16_t R1[1 << (PARAM_FFT - 2)];
-
-			memcpy(Q, f + 3 * n, 2 * n);
-			memcpy(Q + n, f + 3 * n, 2 * n);
-			memcpy(R, f, 4 * n);
-
-			for (size_t i = 0 ; i < n ; ++i) {
-				Q[i] ^= f[2 * n + i];
-				R[n + i] ^= Q[i];
-			}
+static void radix_big(uint16_t *f0, uint16_t *f1, const uint16_t *f, uint32_t m_f) {
+	uint16_t Q[2 * (1 << (PARAM_FFT - 2))] = {0};
+	uint16_t R[2 * (1 << (PARAM_FFT - 2))] = {0};
+
+	uint16_t Q0[1 << (PARAM_FFT - 2)] = {0};
+	uint16_t Q1[1 << (PARAM_FFT - 2)] = {0};
+	uint16_t R0[1 << (PARAM_FFT - 2)] = {0};
+	uint16_t R1[1 << (PARAM_FFT - 2)] = {0};
+
+	size_t i, n;
+
+	n = 1;
+	n <<= (m_f - 2);
+	memcpy(Q, f + 3 * n, 2 * n);
+	memcpy(Q + n, f + 3 * n, 2 * n);
+	memcpy(R, f, 4 * n);
+
+	for (i = 0 ; i < n ; ++i) {
+		Q[i] ^= f[2 * n + i];
+		R[n + i] ^= Q[i];
+	}
 
-			radix(Q0, Q1, Q, m_f - 1);
-			radix(R0, R1, R, m_f - 1);
+	radix(Q0, Q1, Q, m_f - 1);
+	radix(R0, R1, R, m_f - 1);
 
-			memcpy(f0, R0, 2 * n);
-			memcpy(f0 + n, Q0, 2 * n);
-			memcpy(f1, R1, 2 * n);
-			memcpy(f1 + n, Q1, 2 * n);
-	}
+	memcpy(f0, R0, 2 * n);
+	memcpy(f0 + n, Q0, 2 * n);
+	memcpy(f1, R1, 2 * n);
+	memcpy(f1 + n, Q1, 2 * n);
 }
 
 
@@ -159,27 +168,32 @@
  * @param[in] betas FFT constants
  */
 static void fft_rec(uint16_t *w, uint16_t *f, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas) {
-	uint16_t f0[1 << (PARAM_FFT - 2)];
-	uint16_t f1[1 << (PARAM_FFT - 2)];
-	uint16_t gammas[PARAM_M - 2];
-	uint16_t deltas[PARAM_M - 2];
-	size_t k = 1 << (m - 1);
-	uint16_t gammas_sums[1 << (PARAM_M - 2)];
+	uint16_t f0[1 << (PARAM_FFT - 2)] = {0};
+	uint16_t f1[1 << (PARAM_FFT - 2)] = {0};
+	uint16_t gammas[PARAM_M - 2] = {0};
+	uint16_t deltas[PARAM_M - 2] = {0};
+	uint16_t gammas_sums[1 << (PARAM_M - 2)] = {0};
 	uint16_t u[1 << (PARAM_M - 2)] = {0};
 	uint16_t v[1 << (PARAM_M - 2)] = {0};
+	uint16_t tmp[PARAM_M - (PARAM_FFT - 1)] = {0};
+
+	uint16_t beta_m_pow;
+	size_t i, j, k;
+	size_t x;
 
 	// Step 1
 	if (m_f == 1) {
-		uint16_t tmp[PARAM_M - (PARAM_FFT - 1)];
-		for (size_t i = 0 ; i < m ; ++i) {
+		for (i = 0 ; i < m ; ++i) {
 			tmp[i] = gf_mul(betas[i], f[1]);
 		}
 
 		w[0] = f[0];
-		for (size_t j = 0 ; j < m ; ++j) {
-			for (size_t k = 0 ; k < (1U << j) ; ++k) {
-				w[(1 << j) + k] = w[k] ^ tmp[j];
+		x = 1;
+		for (j = 0 ; j < m ; ++j) {
+			for (k = 0 ; k < x ; ++k) {
+				w[x + k] = w[k] ^ tmp[j];
 			}
+			x <<= 1;
 		}
 
 		return;
@@ -187,8 +201,10 @@
 
 	// Step 2: compute g
 	if (betas[m - 1] != 1) {
-		uint16_t beta_m_pow = 1;
-		for (size_t i = 1 ; i < (1U << m_f) ; ++i) {
+		beta_m_pow = 1;
+		x = 1;
+		x <<= m_f;
+		for (i = 1 ; i < x ; ++i) {
 			beta_m_pow = gf_mul(beta_m_pow, betas[m - 1]);
 			f[i] = gf_mul(beta_m_pow, f[i]);
 		}
@@ -198,7 +214,7 @@
 	radix(f0, f1, f, m_f);
 
 	// Step 4: compute gammas and deltas
-	for (uint8_t i = 0 ; i < m - 1 ; ++i) {
+	for (i = 0 ; i + 1 < m ; ++i) {
 		gammas[i] = gf_mul(betas[i], gf_inverse(betas[m - 1]));
 		deltas[i] = gf_square(gammas[i]) ^ gammas[i];
 	}
@@ -209,10 +225,12 @@
 	// Step 5
 	fft_rec(u, f0, (f_coeffs + 1) / 2, m - 1, m_f - 1, deltas);
 
+	k = 1;
+	k <<= ((m - 1)&0xf); // &0xf is to let the compiler know that m-1 is small.
 	if (f_coeffs <= 3) { // 3-coefficient polynomial f case: f1 is constant
 		w[0] = u[0];
 		w[k] = u[0] ^ f1[0];
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			w[i] = u[i] ^ gf_mul(gammas_sums[i], f1[0]);
 			w[k + i] = w[i] ^ f1[0];
 		}
@@ -223,7 +241,7 @@
 		memcpy(w + k, v, 2 * k);
 		w[0] = u[0];
 		w[k] ^= u[0];
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			w[i] = u[i] ^ gf_mul(gammas_sums[i], v[i]);
 			w[k + i] ^= w[i];
 		}
@@ -252,14 +270,15 @@
  * @param[in] f_coeffs Number coefficients of f (i.e. deg(f)+1)
  */
 void fft(uint16_t *w, const uint16_t *f, size_t f_coeffs) {
-	uint16_t betas[PARAM_M - 1];
-	uint16_t betas_sums[1 << (PARAM_M - 1)];
-	uint16_t f0[1 << (PARAM_FFT - 1)];
-	uint16_t f1[1 << (PARAM_FFT - 1)];
-	uint16_t deltas[PARAM_M - 1];
-	size_t k = 1 << (PARAM_M - 1);
-	uint16_t u[1 << (PARAM_M - 1)];
-	uint16_t v[1 << (PARAM_M - 1)];
+	uint16_t betas[PARAM_M - 1] = {0};
+	uint16_t betas_sums[1 << (PARAM_M - 1)] = {0};
+	uint16_t f0[1 << (PARAM_FFT - 1)] = {0};
+	uint16_t f1[1 << (PARAM_FFT - 1)] = {0};
+	uint16_t deltas[PARAM_M - 1] = {0};
+	uint16_t u[1 << (PARAM_M - 1)] = {0};
+	uint16_t v[1 << (PARAM_M - 1)] = {0};
+
+	size_t i, k;
 
 	// Follows Gao and Mateer algorithm
 	compute_fft_betas(betas);
@@ -275,7 +294,7 @@
 	radix(f0, f1, f, PARAM_FFT);
 
 	// Step 4: Compute deltas
-	for (size_t i = 0 ; i < PARAM_M - 1 ; ++i) {
+	for (i = 0 ; i < PARAM_M - 1 ; ++i) {
 		deltas[i] = gf_square(betas[i]) ^ betas[i];
 	}
 
@@ -283,6 +302,7 @@
 	fft_rec(u, f0, (f_coeffs + 1) / 2, PARAM_M - 1, PARAM_FFT - 1, deltas);
 	fft_rec(v, f1, f_coeffs / 2, PARAM_M - 1, PARAM_FFT - 1, deltas);
 
+	k = 1 << (PARAM_M - 1);
 	// Step 6, 7 and error polynomial computation
 	memcpy(w + k, v, 2 * k);
 
@@ -293,7 +313,7 @@
 	w[k] ^= u[0];
 
 	// Find other roots
-	for (size_t i = 1 ; i < k ; ++i) {
+	for (i = 1 ; i < k ; ++i) {
 		w[i] = u[i] ^ gf_mul(betas_sums[i], v[i]);
 		w[k + i] ^= w[i];
 	}
@@ -309,23 +329,23 @@
  * @param[in] w Array of size 2^PARAM_M
  */
 void fft_retrieve_error_poly(uint8_t* error, const uint16_t* w) {
-	uint16_t gammas[PARAM_M-1] = {0};
-	uint16_t gammas_sums[1 << (PARAM_M-1)] = {0};
-	size_t k = 1 << (PARAM_M-1);
-	
-	compute_fft_betas(gammas);
-	compute_subset_sums(gammas_sums, gammas, PARAM_M-1);
+	uint16_t gammas[PARAM_M - 1] = {0};
+	uint16_t gammas_sums[1 << (PARAM_M - 1)] = {0};
+	uint16_t k;
+	size_t i, index;
 
-	error[0] ^= 1 ^ ((uint16_t)-w[0] >> 15);
-	error[0] ^= 1 ^ ((uint16_t)-w[k] >> 15);
-
-	size_t index = PARAM_GF_MUL_ORDER;
+	compute_fft_betas(gammas);
+	compute_subset_sums(gammas_sums, gammas, PARAM_M - 1);
 
-	for (size_t i = 1 ; i < k ; ++i) {
-		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i]);
-		error[index] ^= 1 ^ ((uint16_t)-w[i] >> 15);
+	k = 1 << (PARAM_M-1);
+	error[0] ^= 1 ^ ((uint16_t) -w[0] >> 15);
+	error[0] ^= 1 ^ ((uint16_t) -w[k] >> 15);
+
+	for (i = 1 ; i < k ; ++i) {
+		index = PARAM_GF_MUL_ORDER - gf_log[gammas_sums[i]];
+		error[index] ^= 1 ^ ((uint16_t) -w[i] >> 15);
 
-		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i] ^ 1);
-		error[index] ^= 1 ^ ((uint16_t)-w[k + i] >> 15);
+		index = PARAM_GF_MUL_ORDER - gf_log[gammas_sums[i] ^ 1];
+		error[index] ^= 1 ^ ((uint16_t) -w[k + i] >> 15);
 	}
 }

