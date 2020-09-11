--- hqc-2020-05-29/Reference_Implementation/hqc-128/src/fft.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-128/src/fft.c
@@ -19,8 +19,10 @@
 static void compute_fft_betas(uint16_t *betas);
 static void compute_subset_sums(uint16_t *subset_sums, const uint16_t *set, size_t set_size);
 static void radix_t(uint16_t *f, const uint16_t *f0, const uint16_t *f1, uint32_t m_f);
+static void radix_t_big(uint16_t *f, const uint16_t *f0, const uint16_t *f1, uint32_t m_f);
 static void fft_t_rec(uint16_t *f, const uint16_t *w, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas);
 static void radix(uint16_t *f0, uint16_t *f1, const uint16_t *f, uint32_t m_f);
+static void radix_big(uint16_t *f0, uint16_t *f1, const uint16_t *f, uint32_t m_f);
 static void fft_rec(uint16_t *w, uint16_t *f, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas);
 
 
@@ -30,7 +32,8 @@
  * @param[out] betas Array of size PARAM_M-1
  */
 static void compute_fft_betas(uint16_t *betas) {
-	for (size_t i = 0 ; i < PARAM_M - 1 ; ++i) {
+	size_t i;
+	for (i = 0 ; i < PARAM_M - 1 ; ++i) {
 		betas[i] = 1 << (PARAM_M - 1 - i);
 	}
 }
@@ -48,10 +51,11 @@
  * @param[in] set_size Size of the array set
  */
 static void compute_subset_sums(uint16_t *subset_sums, const uint16_t *set, size_t set_size) {
+  uint16_t i, j;
 	subset_sums[0] = 0;
 
-	for (size_t i = 0 ; i < set_size ; ++i) {
-		for (size_t j = 0 ; j < (1U << i) ; ++j) {
+	for (i = 0 ; i < set_size ; ++i) {
+		for (j = 0 ; j < (1U << i) ; ++j) {
 			subset_sums[(1 << i) + j] = set[i] ^ subset_sums[j];
 		}
 	}
@@ -90,7 +94,7 @@
 			f[13] = f[7] ^ f[9] ^ f[11] ^ f1[6];
 			f[14] = f[6] ^ f0[6] ^ f0[7] ^ f1[6];
 			f[15] = f[7] ^ f0[7] ^ f1[7];
-			return;
+			break;
 
 		case 3:
 			f[0] = f0[0];
@@ -101,49 +105,54 @@
 			f[5] = f[3] ^ f1[2];
 			f[6] = f[4] ^ f0[3] ^ f1[2];
 			f[7] = f[3] ^ f0[3] ^ f1[3];
-			return;
+			break;
 
 		case 2:
 			f[0] = f0[0];
 			f[1] = f1[0];
 			f[2] = f0[1] ^ f1[0];
 			f[3] = f[2] ^ f1[1];
-			return;
+			break;
 
 		case 1:
 			f[0] = f0[0];
 			f[1] = f1[0];
-			return;
+			break;
 
 		default:
-			;
-
-			size_t n = 1 << (m_f - 2);
-
-			uint16_t Q0[1 << (PARAM_FFT_T - 2)];
-			uint16_t Q1[1 << (PARAM_FFT_T - 2)];
-			uint16_t R0[1 << (PARAM_FFT_T - 2)];
-			uint16_t R1[1 << (PARAM_FFT_T - 2)];
-
-			uint16_t Q[1 << 2 * (PARAM_FFT_T - 2)];
-			uint16_t R[1 << 2 * (PARAM_FFT_T - 2)];
+			radix_t_big(f, f0, f1, m_f);
+			break;
+	}
+}
 
-			memcpy(Q0, f0 + n, 2 * n);
-			memcpy(Q1, f1 + n, 2 * n);
-			memcpy(R0, f0, 2 * n);
-			memcpy(R1, f1, 2 * n);
+static void radix_t_big(uint16_t *f, const uint16_t *f0, const uint16_t *f1, uint32_t m_f) {
+	uint16_t Q0[1 << (PARAM_FFT_T - 2)] = {0};
+	uint16_t Q1[1 << (PARAM_FFT_T - 2)] = {0};
+	uint16_t R0[1 << (PARAM_FFT_T - 2)] = {0};
+	uint16_t R1[1 << (PARAM_FFT_T - 2)] = {0};
 
-			radix_t (Q, Q0, Q1, m_f - 1);
-			radix_t (R, R0, R1, m_f - 1);
+	uint16_t Q[1 << 2 * (PARAM_FFT_T - 2)] = {0};
+	uint16_t R[1 << 2 * (PARAM_FFT_T - 2)] = {0};
 
-			memcpy(f, R, 4 * n);
-			memcpy(f + 2 * n, R + n, 2 * n);
-			memcpy(f + 3 * n, Q + n, 2 * n);
+	uint16_t n;
+	size_t i;
 
-			for (size_t i = 0 ; i < n ; ++i) {
-				f[2 * n + i] ^= Q[i];
-				f[3 * n + i] ^= f[2 * n + i];
-			}
+	n = 1 << (m_f - 2);
+	memcpy(Q0, f0 + n, 2 * n);
+	memcpy(Q1, f1 + n, 2 * n);
+	memcpy(R0, f0, 2 * n);
+	memcpy(R1, f1, 2 * n);
+
+	radix_t (Q, Q0, Q1, m_f - 1);
+	radix_t (R, R0, R1, m_f - 1);
+
+	memcpy(f, R, 4 * n);
+	memcpy(f + 2 * n, R + n, 2 * n);
+	memcpy(f + 3 * n, Q + n, 2 * n);
+
+	for (i = 0 ; i < n ; ++i) {
+		f[2 * n + i] ^= Q[i];
+		f[3 * n + i] ^= f[2 * n + i];
 	}
 }
 
@@ -162,29 +171,31 @@
  * @param[in] betas FFT constants
  */
 static void fft_t_rec(uint16_t *f, const uint16_t *w, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas) {
-	size_t k = 1 << (m - 1);
-	uint16_t gammas[PARAM_M - 2];
-	uint16_t deltas[PARAM_M - 2];
-	uint16_t gammas_sums[1 << (PARAM_M - 1)];
+	uint16_t gammas[PARAM_M - 2] = {0};
+	uint16_t deltas[PARAM_M - 2] = {0};
+	uint16_t gammas_sums[1 << (PARAM_M - 1)] = {0};
 	uint16_t u[1 << (PARAM_M - 2)] = {0};
 	uint16_t f0[1 << (PARAM_FFT_T - 2)] = {0};
 	uint16_t f1[1 << (PARAM_FFT_T - 2)] = {0};
+	uint16_t betas_sums[1 << (PARAM_M - 1)] = {0};
+	uint16_t v[1 << (PARAM_M - 2)] = {0};
+  uint16_t beta_m_pow;
+
+	size_t i, j, k;
 
 	// Step 1
 	if (m_f == 1) {
 		f[0] = 0;
-		for (size_t i = 0 ; i < (1U << m) ; ++i) {
+		for (i = 0 ; i < (1U << m) ; ++i) {
 			f[0] ^= w[i];
 		}
 		f[1] = 0;
 
-		uint16_t betas_sums[1 << (PARAM_M - 1)];
 		betas_sums[0] = 0;
-		for (size_t j = 0 ; j < m ; ++j) {
-			for (size_t k = 0 ; k < (1U << j) ; ++k) {
-				size_t index = (1 << j) + k;
-				betas_sums[index] = betas_sums[k] ^ betas[j];
-				f[1] ^= gf_mul(betas_sums[index], w[index]);
+		for (j = 0 ; j < m ; ++j) {
+			for (k = 0 ; k < (1U << j) ; ++k) {
+				betas_sums[(1<<j)+k] = betas_sums[k] ^ betas[j];
+				f[1] ^= gf_mul(betas_sums[(1<<j)+k], w[(1<<j)+k]);
 			}
 		}
 
@@ -192,7 +203,7 @@
 	}
 
 	// Compute gammas and deltas
-	for (uint8_t i = 0 ; i < m - 1 ; ++i) {
+	for (i = 0 ; i + 1 < m ; ++i) {
 		gammas[i] = gf_mul(betas[i], gf_inverse(betas[m - 1]));
 		deltas[i] = gf_square(gammas[i]) ^ gammas[i];
 	}
@@ -206,23 +217,22 @@
 	 * Transpose:
 	 * u[i] = w[i] + w[k+i]
 	 * v[i] = G[i].w[i] + (G[i]+1).w[k+i] = G[i].u[i] + w[k+i] */
+	k = 1 << ((m - 1)&0xf); // &0xf is to let the compiler know that m-1 is small.
 	if (f_coeffs <= 3) { // 3-coefficient polynomial f case
 		// Step 5: Compute f0 from u and f1 from v
 		f1[1] = 0;
 		u[0] = w[0] ^ w[k];
 		f1[0] = w[k];
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			u[i] = w[i] ^ w[k + i];
 			f1[0] ^= gf_mul(gammas_sums[i], u[i]) ^ w[k + i];
 		}
 		fft_t_rec(f0, u, (f_coeffs + 1) / 2, m - 1, m_f - 1, deltas);
 	} else {
-		uint16_t v[1 << (PARAM_M - 2)] = {0};
-
 		u[0] = w[0] ^ w[k];
 		v[0] = w[k];
 
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			u[i] = w[i] ^ w[k + i];
 			v[i] = gf_mul(gammas_sums[i], u[i]) ^ w[k + i];
 		}
@@ -237,8 +247,8 @@
 
 	// Step 2: compute f from g
 	if (betas[m - 1] != 1) {
-		uint16_t beta_m_pow = 1;
-		for (size_t i = 1 ; i < (1U << m_f) ; ++i) {
+		beta_m_pow = 1;
+		for (i = 1 ; i < (1U << m_f) ; ++i) {
 			beta_m_pow = gf_mul(beta_m_pow, betas[m - 1]);
 			f[i] = gf_mul(beta_m_pow, f[i]);
 		}
@@ -261,14 +271,15 @@
  */
 void fft_t(uint16_t *f, const uint16_t *w, size_t f_coeffs) {
 	// Transposed from Gao and Mateer algorithm
-	uint16_t betas[PARAM_M - 1];
-	uint16_t betas_sums[1 << (PARAM_M - 1)];
-	size_t k = 1 << (PARAM_M - 1);
+	uint16_t betas[PARAM_M - 1] = {0};
+	uint16_t betas_sums[1 << (PARAM_M - 1)] = {0};
 	uint16_t u[1 << (PARAM_M - 1)] = {0};
 	uint16_t v[1 << (PARAM_M - 1)] = {0};
-	uint16_t deltas[PARAM_M - 1];
-	uint16_t f0[1 << (PARAM_FFT_T - 1)];
-	uint16_t f1[1 << (PARAM_FFT_T - 1)];
+	uint16_t deltas[PARAM_M - 1] = {0};
+	uint16_t f0[1 << (PARAM_FFT_T - 1)] = {0};
+	uint16_t f1[1 << (PARAM_FFT_T - 1)] = {0};
+
+	size_t i, k;
 
 	compute_fft_betas(betas);
 	compute_subset_sums(betas_sums, betas, PARAM_M - 1);
@@ -281,15 +292,16 @@
 	 * Transpose:
 	 * u[i] = w[i] + w[k+i]
 	 * v[i] = G[i].w[i] + (G[i]+1).w[k+i] = G[i].u[i] + w[k+i] */
+	k = 1 << (PARAM_M - 1);
 	u[0] = w[0] ^ w[k];
 	v[0] = w[k];
-	for (size_t i = 1 ; i < k ; ++i) {
+	for (i = 1 ; i < k ; ++i) {
 		u[i] = w[i] ^ w[k + i];
 		v[i] = gf_mul(betas_sums[i], u[i]) ^ w[k + i];
 	}
 
 	// Compute deltas
-	for (size_t i = 0 ; i < PARAM_M - 1 ; ++i) {
+	for (i = 0 ; i < PARAM_M - 1 ; ++i) {
 		deltas[i] = gf_square(betas[i]) ^ betas[i];
 	}
 
@@ -337,7 +349,7 @@
 			f1[2] = f[3] ^ f1[1] ^ f0[3];
 			f0[1] = f[2] ^ f0[2] ^ f1[1];
 			f1[0] = f[1] ^ f0[1];
-			return;
+			break;
 
 		case 3:
 			f0[0] = f[0];
@@ -348,51 +360,56 @@
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
-
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
-
-			radix(Q0, Q1, Q, m_f - 1);
-			radix(R0, R1, R, m_f - 1);
-
-			memcpy(f0, R0, 2 * n);
-			memcpy(f0 + n, Q0, 2 * n);
-			memcpy(f1, R1, 2 * n);
-			memcpy(f1 + n, Q1, 2 * n);
+			radix_big(f0, f1, f, m_f);
+			break;
 	}
 }
 
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
+	n = 1 << (m_f - 2);
+	memcpy(Q, f + 3 * n, 2 * n);
+	memcpy(Q + n, f + 3 * n, 2 * n);
+	memcpy(R, f, 4 * n);
+
+	for (i = 0 ; i < n ; ++i) {
+		Q[i] ^= f[2 * n + i];
+		R[n + i] ^= Q[i];
+	}
+
+	radix(Q0, Q1, Q, m_f - 1);
+	radix(R0, R1, R, m_f - 1);
+
+	memcpy(f0, R0, 2 * n);
+	memcpy(f0 + n, Q0, 2 * n);
+	memcpy(f1, R1, 2 * n);
+	memcpy(f1 + n, Q1, 2 * n);
+}
+
 
 
 /**
@@ -408,25 +425,27 @@
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
+		for (j = 0 ; j < m ; ++j) {
+			for (k = 0 ; k < (1U << j) ; ++k) {
 				w[(1 << j) + k] = w[k] ^ tmp[j];
 			}
 		}
@@ -436,8 +455,8 @@
 
 	// Step 2: compute g
 	if (betas[m - 1] != 1) {
-		uint16_t beta_m_pow = 1;
-		for (size_t i = 1 ; i < (1U << m_f) ; ++i) {
+		beta_m_pow = 1;
+		for (i = 1 ; i < (1U << m_f) ; ++i) {
 			beta_m_pow = gf_mul(beta_m_pow, betas[m - 1]);
 			f[i] = gf_mul(beta_m_pow, f[i]);
 		}
@@ -447,7 +466,7 @@
 	radix(f0, f1, f, m_f);
 
 	// Step 4: compute gammas and deltas
-	for (uint8_t i = 0 ; i < m - 1 ; ++i) {
+	for (i = 0 ; i + 1 < m ; ++i) {
 		gammas[i] = gf_mul(betas[i], gf_inverse(betas[m - 1]));
 		deltas[i] = gf_square(gammas[i]) ^ gammas[i];
 	}
@@ -458,10 +477,11 @@
 	// Step 5
 	fft_rec(u, f0, (f_coeffs + 1) / 2, m - 1, m_f - 1, deltas);
 
+	k = 1 << ((m - 1)&0xf); // &0xf is to let the compiler know that m-1 is small.
 	if (f_coeffs <= 3) { // 3-coefficient polynomial f case: f1 is constant
 		w[0] = u[0];
 		w[k] = u[0] ^ f1[0];
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			w[i] = u[i] ^ gf_mul(gammas_sums[i], f1[0]);
 			w[k + i] = w[i] ^ f1[0];
 		}
@@ -472,7 +492,7 @@
 		memcpy(w + k, v, 2 * k);
 		w[0] = u[0];
 		w[k] ^= u[0];
-		for (size_t i = 1 ; i < k ; ++i) {
+		for (i = 1 ; i < k ; ++i) {
 			w[i] = u[i] ^ gf_mul(gammas_sums[i], v[i]);
 			w[k + i] ^= w[i];
 		}
@@ -501,14 +521,15 @@
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
@@ -524,7 +545,7 @@
 	radix(f0, f1, f, PARAM_FFT);
 
 	// Step 4: Compute deltas
-	for (size_t i = 0 ; i < PARAM_M - 1 ; ++i) {
+	for (i = 0 ; i < PARAM_M - 1 ; ++i) {
 		deltas[i] = gf_square(betas[i]) ^ betas[i];
 	}
 
@@ -532,6 +553,7 @@
 	fft_rec(u, f0, (f_coeffs + 1) / 2, PARAM_M - 1, PARAM_FFT - 1, deltas);
 	fft_rec(v, f1, f_coeffs / 2, PARAM_M - 1, PARAM_FFT - 1, deltas);
 
+	k = 1 << (PARAM_M - 1);
 	// Step 6, 7 and error polynomial computation
 	memcpy(w + k, v, 2 * k);
 
@@ -542,7 +564,7 @@
 	w[k] ^= u[0];
 
 	// Find other roots
-	for (size_t i = 1 ; i < k ; ++i) {
+	for (i = 1 ; i < k ; ++i) {
 		w[i] = u[i] ^ gf_mul(betas_sums[i], v[i]);
 		w[k + i] ^= w[i];
 	}
@@ -561,21 +583,20 @@
  * @param[in] vector Array of size VEC_N1_SIZE_BYTES
  */
 void fft_t_preprocess_bch_codeword(uint16_t *w, const uint64_t *vector) {
-	uint16_t r[1 << PARAM_M];
-	uint16_t gammas[PARAM_M - 1];
-	uint16_t gammas_sums[1 << (PARAM_M - 1)];
-	size_t k = 1 << (PARAM_M - 1);
+	uint16_t r[1 << PARAM_M] = {0};
+	uint16_t gammas[PARAM_M - 1] = {0};
+	uint16_t gammas_sums[1 << (PARAM_M - 1)] = {0};
+	size_t i, j, k;
 
 	// Unpack the received word vector into array r
-	size_t i;
 	for (i = 0 ; i < VEC_N1_SIZE_64 - (PARAM_N1 % 64 != 0) ; ++i) {
-		for (size_t j = 0 ; j < 64 ; ++j) {
+		for (j = 0 ; j < 64 ; ++j) {
 			r[64 * i + j] = (uint8_t) ((vector[i] >> j) & 1);
 		}
 	}
 
 	// Last byte
-	for (size_t j = 0 ; j < PARAM_N1 % 64 ; ++j) {
+	for (j = 0 ; j < PARAM_N1 % 64 ; ++j) {
 		r[64 * i + j] = (uint8_t) ((vector[i] >> j) & 1);
 	}
 
@@ -586,11 +607,12 @@
 	compute_subset_sums(gammas_sums, gammas, PARAM_M - 1);
 
 	// Twist and permute r adequately to obtain w
+	k = 1 << (PARAM_M - 1);
 	w[0] = 0;
 	w[k] = -r[0] & 1;
-	for (size_t i = 1 ; i < k ; ++i) {
-		w[i] = -r[gf_log(gammas_sums[i])] & gammas_sums[i];
-		w[k + i] = -r[gf_log(gammas_sums[i] ^ 1)] & (gammas_sums[i] ^ 1);
+	for (i = 1 ; i < k ; ++i) {
+		w[i] = -r[gf_log[gammas_sums[i]]] & gammas_sums[i];
+		w[k + i] = -r[gf_log[gammas_sums[i] ^ 1]] & (gammas_sums[i] ^ 1);
 	}
 }
 
@@ -603,25 +625,29 @@
  * @param[in] w Array of size 2^PARAM_M
  */
 void fft_retrieve_bch_error_poly(uint64_t *error, const uint16_t *w) {
-	uint16_t gammas[PARAM_M - 1];
-	uint16_t gammas_sums[1 << (PARAM_M - 1)];
-	size_t k = 1 << (PARAM_M - 1);
-	size_t index = PARAM_GF_MUL_ORDER;
+	uint16_t gammas[PARAM_M - 1] = {0};
+	uint16_t gammas_sums[1 << (PARAM_M - 1)] = {0};
+	uint64_t bit;
+	uint16_t k;
+	size_t i, index;
 
 	compute_fft_betas(gammas);
 	compute_subset_sums(gammas_sums, gammas, PARAM_M - 1);
 
-	error[0] ^= ((uint64_t) 1) ^ ((uint16_t) - w[0] >> 15);
-	uint64_t bit = ((uint64_t) 1) ^ ((uint16_t) - w[k] >> 15);
+	error[0] ^= 1 ^ ((uint16_t) - w[0] >> 15);
+
+	k = 1 << (PARAM_M - 1);
+	index = PARAM_GF_MUL_ORDER;
+	bit = 1 ^ ((uint16_t) - w[k] >> 15);
 	error[index / 8] ^= bit << (index % 64);
 
-	for (size_t i = 1 ; i < k ; ++i) {
-		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i]);
-		bit = ((uint64_t) 1) ^ ((uint16_t) - w[i] >> 15);
+	for (i = 1 ; i < k ; ++i) {
+		index = PARAM_GF_MUL_ORDER - gf_log[gammas_sums[i]];
+		bit = 1 ^ ((uint16_t) - w[i] >> 15);
 		error[index / 64] ^= bit << (index % 64);
 
-		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i] ^ 1);
-		bit = ((uint64_t) 1) ^ ((uint16_t) - w[k + i] >> 15);
+		index = PARAM_GF_MUL_ORDER - gf_log[gammas_sums[i] ^ 1];
+		bit = 1 ^ ((uint16_t) - w[k + i] >> 15);
 		error[index / 64] ^= bit << (index % 64);
 	}
 }

