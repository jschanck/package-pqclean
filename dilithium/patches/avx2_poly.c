--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -422,6 +422,7 @@
   stream128_state state;
   stream128_init(&state, seed, nonce);
   poly_uniform_preinit(a, &state);
+  stream128_release(&state);
 }
 
 #ifndef DILITHIUM_USE_AES
@@ -535,7 +536,7 @@
 *              - const uint8_t seed[]: byte array with seed of length CRHBYTES
 *              - uint16_t nonce: 2-byte nonce
 **************************************************/
-void poly_uniform_eta_preinit(poly *a, stream128_state *state)
+void poly_uniform_eta_preinit(poly *a, stream256_state *state)
 {
   unsigned int ctr;
   ALIGNED_UINT8(REJ_UNIFORM_ETA_BUFLEN) buf;
@@ -554,6 +555,7 @@
   stream256_state state;
   stream256_init(&state, seed, nonce);
   poly_uniform_eta_preinit(a, &state);
+  stream256_release(&state);
 }
 
 #ifndef DILITHIUM_USE_AES
@@ -637,6 +639,7 @@
   stream256_state state;
   stream256_init(&state, seed, nonce);
   poly_uniform_gamma1_preinit(a, &state);
+  stream256_release(&state);
 }
 
 #ifndef DILITHIUM_USE_AES
@@ -698,12 +701,12 @@
   unsigned int i, b, pos;
   uint64_t signs;
   ALIGNED_UINT8(SHAKE256_RATE) buf;
-  keccak_state state;
+  shake256incctx state;
 
-  shake256_init(&state);
-  shake256_absorb(&state, seed, SEEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeezeblocks(buf.coeffs, 1, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, seed, SEEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(buf.coeffs, SHAKE256_RATE, &state);
 
   memcpy(&signs, buf.coeffs, 8);
   pos = 8;
@@ -712,7 +715,7 @@
   for(i = N-TAU; i < N; ++i) {
     do {
       if(pos >= SHAKE256_RATE) {
-        shake256_squeezeblocks(buf.coeffs, 1, &state);
+        shake256_inc_squeeze(buf.coeffs, SHAKE256_RATE, &state);
         pos = 0;
       }
 
@@ -723,6 +726,7 @@
     c->coeffs[b] = 1 - 2*(signs & 1);
     signs >>= 1;
   }
+  shake256_inc_ctx_release(&state);
 }
 
 /*************************************************

