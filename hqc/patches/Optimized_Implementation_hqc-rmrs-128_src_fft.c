--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-128/src/fft.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-128/src/fft.c
@@ -16,7 +16,7 @@
 #include <string.h>
 
 static void compute_fft_betas(uint16_t* betas);
-static void compute_subset_sums(uint16_t* subset_sums, uint16_t* set, size_t set_size);
+static void compute_subset_sums(uint16_t* subset_sums, const uint16_t* set, size_t set_size);
 static void radix(uint16_t* f0, uint16_t* f1, const uint16_t* f, uint32_t m_f);
 static void fft_rec(uint16_t *w, uint16_t *f, size_t f_coeffs, uint8_t m, uint32_t m_f, const uint16_t *betas);
 
@@ -44,7 +44,7 @@
  * @param[in] set Array of set_size elements
  * @param[in] set_size Size of the array set
  */
-static void compute_subset_sums(uint16_t* subset_sums, uint16_t* set, size_t set_size) {
+static void compute_subset_sums(uint16_t* subset_sums, const uint16_t* set, size_t set_size) {
 	subset_sums[0] = 0;
 
 	for(size_t i = 0 ; i < set_size ; ++i) {
@@ -316,16 +316,16 @@
 	compute_fft_betas(gammas);
 	compute_subset_sums(gammas_sums, gammas, PARAM_M-1);
 
-	error[0] ^= 1 ^ ((uint16_t)-w[0] >> 15);
-	error[0] ^= 1 ^ ((uint16_t)-w[k] >> 15);
+	error[0] ^= (uint8_t) (1 ^ ((uint16_t)-w[0] >> 15));
+	error[0] ^= (uint8_t) (1 ^ ((uint16_t)-w[k] >> 15));
 
 	size_t index = PARAM_GF_MUL_ORDER;
 
 	for (size_t i = 1 ; i < k ; ++i) {
 		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i]);
-		error[index] ^= 1 ^ ((uint16_t)-w[i] >> 15);
+		error[index] ^= (uint8_t) (1 ^ ((uint16_t)-w[i] >> 15));
 
 		index = PARAM_GF_MUL_ORDER - gf_log(gammas_sums[i] ^ 1);
-		error[index] ^= 1 ^ ((uint16_t)-w[k + i] >> 15);
+		error[index] ^= (uint8_t) (1 ^ ((uint16_t)-w[k + i] >> 15));
 	}
 }

