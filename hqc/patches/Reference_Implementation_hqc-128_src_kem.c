--- hqc-2020-05-29/Reference_Implementation/hqc-128/src/kem.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-128/src/kem.c
@@ -55,6 +55,7 @@
     	#endif
     
 	uint8_t theta[SHA512_BYTES] = {0};
+	uint8_t m_bytes[VEC_K_SIZE_BYTES] = {0};
 	uint64_t m[VEC_K_SIZE_64] = {0};
 	uint64_t u[VEC_N_SIZE_64] = {0};
 	uint64_t v[VEC_N1N2_SIZE_64] = {0};
@@ -62,21 +63,22 @@
 	unsigned char mc[VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES] = {0};
 
 	// Computing m
-	vect_set_random_from_randombytes(m);
+	randombytes(m_bytes, VEC_K_SIZE_BYTES);
+	load8_arr(m, VEC_K_SIZE_64, m_bytes, VEC_K_SIZE_BYTES);
 
 	// Computing theta
-	sha3_512(theta, (uint8_t*) m, VEC_K_SIZE_BYTES);
+	sha3_512(theta, m_bytes, VEC_K_SIZE_BYTES);
 
 	// Encrypting m
 	hqc_pke_encrypt(u, v, m, theta, pk);
 
 	// Computing d
-	sha512(d, (unsigned char *) m, VEC_K_SIZE_BYTES);
+	sha512(d, m_bytes, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
-	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	memcpy(mc, m_bytes, VEC_K_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Computing ciphertext
@@ -114,6 +116,7 @@
 	uint64_t v[VEC_N1N2_SIZE_64] = {0};
 	unsigned char d[SHA512_BYTES] = {0};
 	unsigned char pk[PUBLIC_KEY_BYTES] = {0};
+	uint8_t m_bytes[VEC_K_SIZE_BYTES] = {0};
 	uint64_t m[VEC_K_SIZE_64] = {0};
 	uint8_t theta[SHA512_BYTES] = {0};
 	uint64_t u2[VEC_N_SIZE_64] = {0};
@@ -129,20 +132,21 @@
 
 	// Decryting
 	hqc_pke_decrypt(m, u, v, sk);
+	store8_arr(m_bytes, VEC_K_SIZE_BYTES, m, VEC_K_SIZE_64);
 
 	// Computing theta
-	sha3_512(theta, (uint8_t*) m, VEC_K_SIZE_BYTES);
+	sha3_512(theta, m_bytes, VEC_K_SIZE_BYTES);
 
 	// Encrypting m'
 	hqc_pke_encrypt(u2, v2, m, theta, pk);
 
 	// Computing d'
-	sha512(d2, (unsigned char *) m, VEC_K_SIZE_BYTES);
+	sha512(d2, m_bytes, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
-	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	memcpy(mc, m_bytes, VEC_K_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Abort if c != c' or d != d'

