--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/kem.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/kem.c
@@ -75,8 +75,8 @@
 
 	// Computing shared secret
 	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Computing ciphertext
@@ -141,8 +141,8 @@
 
 	// Computing shared secret
 	memcpy(mc, m, VEC_K_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES, u, VEC_N_SIZE_BYTES);
-	memcpy(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
+	store8_arr(mc + VEC_K_SIZE_BYTES, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64);
+	store8_arr(mc + VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64);
 	sha512(ss, mc, VEC_K_SIZE_BYTES + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES);
 
 	// Abort if c != c' or d != d'

