--- upstream/Optimized_Implementation/hqc-rmrs-192/src/hqc.c
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-192/src/hqc.c
@@ -10,6 +10,7 @@
 #include "gf2x.h"
 #include "code.h"
 #include "vector.h"
+#include <immintrin.h>
 #include <stdint.h>
 #include <string.h>
 #ifdef VERBOSE
@@ -33,22 +34,11 @@
 	AES_XOF_struct pk_seedexpander;
 	uint8_t sk_seed[SEED_BYTES] = {0};
 	uint8_t pk_seed[SEED_BYTES] = {0};
-	static uint64_t x[VEC_N_256_SIZE_64] = {0};
-	static uint64_t y[VEC_N_256_SIZE_64] = {0};
-	static uint64_t h[VEC_N_256_SIZE_64] = {0};
-	static uint64_t s[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp[VEC_N_256_SIZE_64] = {0};
-
-	#ifdef __STDC_LIB_EXT1__
-		memset_s(x, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(y, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(h, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#else
-		memset(x, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(y, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(h, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#endif
-
+	aligned_vec_t vx = {0}; uint64_t *x = vx.arr64;
+	aligned_vec_t vy = {0}; uint64_t *y = vy.arr64;
+	aligned_vec_t vh = {0}; uint64_t *h = vh.arr64;
+	aligned_vec_t vs = {0}; uint64_t *s = vs.arr64;
+	aligned_vec_t vtmp = {0}; uint64_t *tmp = vtmp.arr64;
 
 	// Create seed_expanders for public key and secret key
 	randombytes(sk_seed, SEED_BYTES);
@@ -63,7 +53,7 @@
 
 	// Compute public key
 	vect_set_random(&pk_seedexpander, h);
-	vect_mul(tmp, y, h);
+	vect_mul(tmp, &vy, &vh);
 	vect_add(s, x, tmp, VEC_N_256_SIZE_64);
 
 	// Parse keys to string
@@ -97,31 +87,17 @@
  * @param[in] theta Seed used to derive randomness required for encryption
  * @param[in] pk String containing the public key
  */
-void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint64_t *m, unsigned char *theta, const unsigned char *pk) {
+void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint8_t *m, unsigned char *theta, const unsigned char *pk) {
 	AES_XOF_struct seedexpander;
-	static uint64_t h[VEC_N_256_SIZE_64] = {0};
-	static uint64_t s[VEC_N_256_SIZE_64] = {0};
-	static uint64_t r1[VEC_N_256_SIZE_64] = {0};
-	static uint64_t r2[VEC_N_256_SIZE_64] = {0};
-	static uint64_t e[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp1[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp2[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp3[VEC_N_256_SIZE_64] = {0};
-
-
-	#ifdef __STDC_LIB_EXT1__
-		memset_s(r2, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(h, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(s, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(e, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset_s(r1, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#else
-		memset(r2, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(h, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(s, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(e, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-		memset(r1, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#endif
+	aligned_vec_t vh = {0}; uint64_t *h = vh.arr64;
+	aligned_vec_t vs = {0}; uint64_t *s = vs.arr64;
+	aligned_vec_t vr1 = {0}; uint64_t *r1 = vr1.arr64;
+	aligned_vec_t vr2 = {0}; uint64_t *r2 = vr2.arr64;
+	aligned_vec_t ve = {0}; uint64_t *e = ve.arr64;
+	aligned_vec_t vtmp1 = {0}; uint64_t *tmp1 = vtmp1.arr64;
+	aligned_vec_t vtmp2 = {0}; uint64_t *tmp2 = vtmp2.arr64;
+	aligned_vec_t vtmp3 = {0}; uint64_t *tmp3 = vtmp3.arr64;
+
 	// Create seed_expander from theta
 	seedexpander_init(&seedexpander, theta, theta + 32, SEEDEXPANDER_MAX_LENGTH);
 
@@ -139,15 +115,16 @@
 	
 
 	// Compute u = r1 + r2.h
-	vect_mul(tmp1, r2, h);
+	vect_mul(tmp1, &vr2, &vh);
 	vect_add(u, r1, tmp1, VEC_N_256_SIZE_64);
 
 	// Compute v = m.G by encoding the message
-	code_encode(v, m);
+	code_encode((uint8_t*)v, m);
+	load8_arr(v, VEC_N1N2_256_SIZE_64, (uint8_t*)v, VEC_N1N2_SIZE_BYTES);
 	vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
 
 	// Compute v = m.G + s.r2 + e
-	vect_mul(tmp2, r2, s);
+	vect_mul(tmp2, &vr2, &vs);
 	vect_add(tmp3, e, tmp2, VEC_N_256_SIZE_64);
 	vect_add(tmp2, tmp1, tmp3, VEC_N_256_SIZE_64);
 	vect_resize(v, PARAM_N1N2, tmp2, PARAM_N);
@@ -177,25 +154,23 @@
  * @param[in] v Vector v (second part of the ciphertext)
  * @param[in] sk String containing the secret key
  */
-void hqc_pke_decrypt(uint64_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
-	uint64_t x[VEC_N_256_SIZE_64] = {0};
-	static uint64_t y[VEC_N_256_SIZE_64] = {0};
+void hqc_pke_decrypt(uint8_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk) {
 	uint8_t pk[PUBLIC_KEY_BYTES] = {0};
-	static uint64_t tmp1[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp2[VEC_N_256_SIZE_64] = {0};
-	static uint64_t tmp3[VEC_N_256_SIZE_64] = {0};
-	#ifdef __STDC_LIB_EXT1__
-		memset_s(y, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#else
-		memset(y, 0, (VEC_N_256_SIZE_64) * sizeof(uint64_t));
-	#endif
+	aligned_vec_t vx = {0}; uint64_t *x = vx.arr64;
+	aligned_vec_t vy = {0}; uint64_t *y = vy.arr64;
+	aligned_vec_t vtmp1 = {0}; uint64_t *tmp1 = vtmp1.arr64;
+	aligned_vec_t vtmp2 = {0}; uint64_t *tmp2 = vtmp2.arr64;
+	aligned_vec_t vtmp3 = {0}; uint64_t *tmp3 = vtmp3.arr64;
 
 	// Retrieve x, y, pk from secret key
 	hqc_secret_key_from_string(x, y, pk, sk);
 
 	// Compute v - u.y
 	vect_resize(tmp1, PARAM_N, v, PARAM_N1N2);
-	vect_mul(tmp3, y, u);
+	for(size_t i=0; i<VEC_N_256_SIZE_64; i++) {
+		tmp2[i] = u[i];
+	}
+	vect_mul(tmp3, &vy, &vtmp2);
 	vect_add(tmp2, tmp1, tmp3, VEC_N_256_SIZE_64);
 
 	#ifdef VERBOSE
@@ -206,5 +181,6 @@
 	#endif
 
 	// Compute m by decoding v - u.y
-	code_decode(m, tmp2);
+	store8_arr((uint8_t *)tmp1, VEC_N_SIZE_BYTES, tmp2, VEC_N_256_SIZE_64);
+	code_decode(m, (uint8_t *)tmp1);
 }

