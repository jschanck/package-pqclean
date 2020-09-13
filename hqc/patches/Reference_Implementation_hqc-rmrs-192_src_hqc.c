--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-192/src/hqc.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-192/src/hqc.c
@@ -84,7 +84,7 @@
  * @param[in] theta Seed used to derive randomness required for encryption
  * @param[in] pk String containing the public key
  */
-void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint64_t *m, unsigned char *theta, const unsigned char *pk) {
+void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint8_t *m, unsigned char *theta, const unsigned char *pk) {
 	AES_XOF_struct seedexpander;
 	uint64_t h[VEC_N_SIZE_64] = {0};
 	uint64_t s[VEC_N_SIZE_64] = {0};
@@ -110,7 +110,8 @@
 	vect_add(u, r1, u, VEC_N_SIZE_64);
 
 	// Compute v = m.G by encoding the message
-	code_encode(v, m);
+	code_encode((uint8_t*)v, m);
+	load8_arr(v, VEC_N1N2_SIZE_64, (uint8_t*)v, VEC_N1N2_SIZE_BYTES);
 	vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
 
 	// Compute v = m.G + s.r2 + e
@@ -142,17 +143,16 @@
  * @param[in] v Vector v (second part of the ciphertext)
  * @param[in] sk String containing the secret key
  */
-void hqc_pke_decrypt(uint64_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
-	uint64_t x[VEC_N_SIZE_64] = {0};
-	uint32_t y[PARAM_OMEGA] = {0};
+void hqc_pke_decrypt(uint8_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
 	uint8_t pk[PUBLIC_KEY_BYTES] = {0};
 	uint64_t tmp1[VEC_N_SIZE_64] = {0};
 	uint64_t tmp2[VEC_N_SIZE_64] = {0};
+	uint32_t y[PARAM_OMEGA] = {0};
 	AES_XOF_struct perm_seedexpander;
 	uint8_t perm_seed[SEED_BYTES] = {0};
 
 	// Retrieve x, y, pk from secret key
-	hqc_secret_key_from_string(x, y, pk, sk);
+	hqc_secret_key_from_string(tmp1, y, pk, sk);
 
 	randombytes(perm_seed, SEED_BYTES);
 	seedexpander_init(&perm_seedexpander, perm_seed, perm_seed + 32, SEEDEXPANDER_MAX_LENGTH);
@@ -170,5 +170,6 @@
 	#endif
 
 	// Compute m by decoding v - u.y
-	code_decode(m, tmp2);
+	store8_arr((uint8_t *)tmp1, VEC_N_SIZE_BYTES, tmp2, VEC_N_SIZE_64);
+	code_decode(m, (uint8_t *)tmp1);
 }

