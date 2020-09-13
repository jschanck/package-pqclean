--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-128/src/kem.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-128/src/kem.c
@@ -55,28 +55,28 @@
 	#endif
 
 	uint8_t theta[SHA512_BYTES] = {0};
-	uint64_t m[VEC_K_SIZE_64] = {0};
+	uint8_t m[VEC_K_SIZE_BYTES] = {0};
 	uint64_t u[VEC_N_256_SIZE_64] = {0};
 	uint64_t v[VEC_N1N2_256_SIZE_64] = {0};
 	unsigned char d[SHA512_BYTES] = {0};
 	unsigned char mc[VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES] = {0};
 
 	// Computing m
-	vect_set_random_from_randombytes(m);
+	randombytes(m, VEC_K_SIZE_BYTES);
 
 	// Computing theta
-	sha3_512(theta, (uint8_t*) m, VEC_K_SIZE_BYTES);
+	sha3_512(theta, m, VEC_K_SIZE_BYTES);
 
 	// Encrypting m
 	hqc_pke_encrypt(u, v, m, theta, pk);
 
 	// Computing d
-	sha512(d, (unsigned char *) m, VEC_K_SIZE_BYTES);
+	sha512(d, m, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
 	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Computing ciphertext
@@ -114,7 +114,7 @@
 	uint64_t v[VEC_N1N2_256_SIZE_64] = {0};
 	unsigned char d[SHA512_BYTES] = {0};
 	unsigned char pk[PUBLIC_KEY_BYTES] = {0};
-	uint64_t m[VEC_K_SIZE_64] = {0};
+	uint8_t m[VEC_K_SIZE_BYTES] = {0};
 	uint8_t theta[SHA512_BYTES] = {0};
 	uint64_t u2[VEC_N_256_SIZE_64] = {0};
 	uint64_t v2[VEC_N1N2_256_SIZE_64] = {0};
@@ -131,18 +131,18 @@
 	hqc_pke_decrypt(m, u, v, sk);
 
 	// Computing theta
-	sha3_512(theta, (uint8_t*) m, VEC_K_SIZE_BYTES);
+	sha3_512(theta, m, VEC_K_SIZE_BYTES);
 
 	// Encrypting m'
 	hqc_pke_encrypt(u2, v2, m, theta, pk);
 
 	// Computing d'
-	sha512(d2, (unsigned char *) m, VEC_K_SIZE_BYTES);
+	sha512(d2, m, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
 	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_256_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Abort if c != c' or d != d'

