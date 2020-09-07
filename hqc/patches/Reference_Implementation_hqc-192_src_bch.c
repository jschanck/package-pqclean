--- hqc-2020-05-29/Reference_Implementation/hqc-192/src/bch.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-192/src/bch.c
@@ -15,8 +15,8 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(const uint16_t i, const uint16_t modulus);
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound);
+static uint16_t mod(uint16_t i, uint16_t modulus);
+static void compute_cyclotomic_cosets(uint16_t *cosets, uint16_t upper_bound);
 static void unpack_message(uint8_t *message_unpacked, const uint64_t *message);
 static void lfsr_encode(uint8_t *codeword, const uint8_t *message);
 static void pack_codeword(uint64_t *codeword, const uint8_t *codeword_unpacked);
@@ -34,7 +34,7 @@
  * @param[in] i The integer whose modulo is taken
  * @param[in] modulus The modulus
  */
-static uint16_t mod(const uint16_t i, const uint16_t modulus) {
+static uint16_t mod(uint16_t i, uint16_t modulus) {
 	uint16_t tmp = i - modulus;
 
 	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
@@ -52,7 +52,7 @@
  * @param[out] cosets Array receiving the coset representatives
  * @param[in] upper_bound The upper bound
  */
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound) {
+static void compute_cyclotomic_cosets(uint16_t *cosets, uint16_t upper_bound) {
 	// Compute the odd cyclotomic classes
 	for (uint16_t i = 1 ; i < upper_bound ; i += 2) {
 		if (cosets[i] == 0) { // If i does not already belong to a class

