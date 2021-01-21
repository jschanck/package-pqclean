--- upstream/avx2/aes256ctr.h
+++ upstream-patched/avx2/aes256ctr.h
@@ -27,7 +27,7 @@
 #define aes256ctr_prf AES256CTR_NAMESPACE(prf)
 void aes256ctr_prf(uint8_t *out,
                    size_t outlen,
-                   const uint8_t key[32],
+                   const uint8_t seed[32],
                    uint64_t nonce);
 
 #endif

