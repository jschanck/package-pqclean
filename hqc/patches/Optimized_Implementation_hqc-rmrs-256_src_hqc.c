--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-256/src/hqc.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-256/src/hqc.c
@@ -84,7 +84,7 @@
  * @param[in] theta Seed used to derive randomness required for encryption
  * @param[in] pk String containing the public key
  */
-void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint64_t *m, unsigned char *theta, const unsigned char *pk) {
+void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint8_t *m, unsigned char *theta, const unsigned char *pk) {
 	AES_XOF_struct seedexpander;
 	uint64_t h[VEC_N_256_SIZE_64] = {0};
 	uint64_t s[VEC_N_256_SIZE_64] = {0};
@@ -110,7 +110,8 @@
 	vect_add(u, r1, u, VEC_N_256_SIZE_64);
 
 	// Compute v = m.G by encoding the message
-	code_encode(v, m);
+	code_encode((uint8_t*)v, m);
+	load8_arr(v, VEC_N1N2_256_SIZE_64, (uint8_t*)v, VEC_N1N2_SIZE_BYTES);
 	vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
 
 	// Compute v = m.G + s.r2 + e
@@ -142,15 +143,14 @@
  * @param[in] v Vector v (second part of the ciphertext)
  * @param[in] sk String containing the secret key
  */
-void hqc_pke_decrypt(uint64_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
-	uint64_t x[VEC_N_256_SIZE_64] = {0};
-	uint64_t y[VEC_N_256_SIZE_64] = {0};
+void hqc_pke_decrypt(uint8_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
 	uint8_t pk[PUBLIC_KEY_BYTES] = {0};
 	uint64_t tmp1[VEC_N_256_SIZE_64] = {0};
 	uint64_t tmp2[VEC_N_256_SIZE_64] = {0};
+	uint64_t y[VEC_N_256_SIZE_64] = {0};
 
 	// Retrieve x, y, pk from secret key
-	hqc_secret_key_from_string(x, y, pk, sk);
+	hqc_secret_key_from_string(tmp1, y, pk, sk);
 
 	// Compute v - u.y
 	vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
@@ -165,5 +165,6 @@
 	#endif
 
 	// Compute m by decoding v - u.y
-	code_decode(m, tmp2);
+	store8_arr((uint8_t *)tmp1, VEC_N_SIZE_BYTES, tmp2, VEC_N_256_SIZE_64);
+	code_decode(m, (uint8_t *)tmp1);
 }

