--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-256/src/kem.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-256/src/kem.c
@@ -55,28 +55,28 @@
     	#endif
     
 	uint8_t theta[SHA512_BYTES] = {0};
-	uint64_t m[VEC_K_SIZE_64] = {0};
+	uint8_t m[VEC_K_SIZE_BYTES] = {0};
 	uint64_t u[VEC_N_SIZE_64] = {0};
 	uint64_t v[VEC_N1N2_SIZE_64] = {0};
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
@@ -109,12 +109,12 @@
         	printf("\n\n\n\n### DECAPS ###");
 	#endif
 
-	int8_t result = -1;
+	uint8_t result;
 	uint64_t u[VEC_N_SIZE_64] = {0};
 	uint64_t v[VEC_N1N2_SIZE_64] = {0};
 	unsigned char d[SHA512_BYTES] = {0};
 	unsigned char pk[PUBLIC_KEY_BYTES] = {0};
-	uint64_t m[VEC_K_SIZE_64] = {0};
+	uint8_t m[VEC_K_SIZE_BYTES] = {0};
 	uint8_t theta[SHA512_BYTES] = {0};
 	uint64_t u2[VEC_N_SIZE_64] = {0};
 	uint64_t v2[VEC_N1N2_SIZE_64] = {0};
@@ -131,26 +131,28 @@
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
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Abort if c != c' or d != d'
-	result = (vect_compare(u, u2, VEC_N_SIZE_BYTES) == 0 && vect_compare(v, v2, VEC_N1N2_SIZE_BYTES) == 0 && memcmp(d, d2, SHA512_BYTES) == 0);
+	result = vect_compare((uint8_t *)u, (uint8_t *)u2, VEC_N_SIZE_BYTES);
+	result |= vect_compare((uint8_t *)v, (uint8_t *)v2, VEC_N1N2_SIZE_BYTES);
+	result |= vect_compare(d, d2, SHA512_BYTES);
+	result = (uint8_t) (-((int16_t) result) >> 15);
 	for (size_t i = 0 ; i < SHARED_SECRET_BYTES ; i++) {
-		ss[i] = result * ss[i];
+		ss[i] &= ~result;
 	}
-	result--;
 
 	#ifdef VERBOSE
 		printf("\n\npk: "); for(int i = 0 ; i < PUBLIC_KEY_BYTES ; ++i) printf("%02x", pk[i]);
@@ -165,5 +167,5 @@
 		printf("\n\n# Checking Ciphertext - End #\n");
 	#endif
 
-	return result;
+	return -(result&1);
 }

