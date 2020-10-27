--- upstream/ref/symmetric-aes.h
+++ upstream-patched/ref/symmetric-aes.h
@@ -0,0 +1,24 @@
+#ifndef AES256CTR_H
+#define AES256CTR_H
+
+#include "aes.h"
+
+#include <stddef.h>
+#include <stdint.h>
+
+typedef struct {
+    aes256ctx sk_exp;
+    uint8_t iv[12];
+    uint32_t ctr;
+} aes256xof_ctx;
+
+#define aes256_prf KYBER_NAMESPACE(_aes256_prf)
+void aes256_prf(uint8_t *output, size_t outlen, const uint8_t *key, uint8_t nonce);
+#define aes256xof_absorb KYBER_NAMESPACE(_aes256xof_absorb)
+void aes256xof_absorb(aes256xof_ctx *s, const uint8_t *key, uint8_t x, uint8_t y);
+#define aes256xof_squeezeblocks KYBER_NAMESPACE(_aes256xof_squeezeblocks)
+void aes256xof_squeezeblocks(uint8_t *out, size_t nblocks, aes256xof_ctx *s);
+#define aes256xof_ctx_release KYBER_NAMESPACE(_aes256xof_ctx_release)
+void aes256xof_ctx_release(aes256xof_ctx *s);
+
+#endif

