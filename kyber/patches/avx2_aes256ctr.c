--- upstream/avx2/aes256ctr.c
+++ upstream-patched/avx2/aes256ctr.c
@@ -126,14 +126,14 @@
 
 void aes256ctr_prf(uint8_t *out,
                    size_t outlen,
-                   const uint8_t seed[32],
+                   const uint8_t key[32],
                    uint64_t nonce)
 {
   unsigned int i;
   uint8_t buf[64];
   aes256ctr_ctx state;
 
-  aes256ctr_init(&state, seed, nonce);
+  aes256ctr_init(&state, key, nonce);
 
   while(outlen >= 64) {
     aesni_encrypt4(out, &state.n, state.rkeys);

