--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/fft.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/fft.c
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

