--- hqc-2020-05-29/Optimized_Implementation/hqc-256/src/kem.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-256/src/kem.c
@@ -74,9 +74,9 @@
 	sha512(d, (unsigned char *) m, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
-	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc, VEC_K_SIZE_BYTES, m, VEC_K_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Computing ciphertext
@@ -109,7 +109,7 @@
 		printf("\n\n\n\n### DECAPS ###");
 	#endif
         
-	int8_t result = -1;
+	uint8_t result;
 	uint64_t u[VEC_N_256_SIZE_64] = {0};
 	uint64_t v[VEC_N1N2_256_SIZE_64] = {0};
 	unsigned char d[SHA512_BYTES] = {0};
@@ -140,17 +140,19 @@
 	sha512(d2, (unsigned char *) m, VEC_K_SIZE_BYTES);
 
 	// Computing shared secret
-	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc, VEC_K_SIZE_BYTES, m, VEC_K_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Abort if c != c' or d != d'
-	result = (vect_compare(u, u2, VEC_N_SIZE_BYTES) == 0 && vect_compare(v, v2, VEC_N1N2_SIZE_BYTES) == 0 && vect_compare((uint64_t *)d, (uint64_t *)d2, SHA512_BYTES) == 0);
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

