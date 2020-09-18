--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/sign.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/sign.c
@@ -1,7 +1,6 @@
 #include "api.h"
-#if SUPERCOP
-    #include "crypto_sign.h"
-#endif
+#include <stddef.h>
+#include <stdint.h>
 #include <string.h>
 
 #include "sign_keypairHFE.h"
@@ -15,11 +14,7 @@
  * @param[out]   sk  The secret-key.
  * @return  Zero if the function runs correctly, non-zero else.
  */
-#if SUPERCOP
-int crypto_sign_keypair(unsigned char *pk, unsigned char *sk)
-#else
-int PREFIX_NAME(crypto_sign_keypair)(unsigned char *pk, unsigned char *sk)
-#endif
+int crypto_sign_keypair(uint8_t *pk, uint8_t *sk)
 {
     return sign_keypairHFE(pk,(UINT*)sk);
 }
@@ -34,18 +29,14 @@
  * @param[in]   sk  The secret-key.
  * @return  Zero if the function runs correctly, non-zero else.
  */
-#if SUPERCOP
 int crypto_sign(
-#else
-int PREFIX_NAME(crypto_sign)(
-#endif
-  unsigned char *sm, unsigned long long *smlen,
-  const unsigned char *m, unsigned long long mlen,
-  const unsigned char *sk)
+  uint8_t *sm, size_t *smlen,
+  const uint8_t *m, size_t mlen,
+  const uint8_t *sk)
 {
     *smlen=mlen+CRYPTO_BYTES;
-    memcpy(sm+CRYPTO_BYTES,m,(size_t)mlen);
-    return signHFE(sm,m,(size_t)mlen,(UINT*)sk);
+    memcpy(sm+CRYPTO_BYTES,m,mlen);
+    return signHFE(sm,m,mlen,(UINT*)sk);
 }
 
 
@@ -58,14 +49,10 @@
  * @param[in]   pk  The public-key.
  * @return  Zero if the function runs correctly, non-zero else.
  */
-#if SUPERCOP
 int crypto_sign_open(
-#else
-int PREFIX_NAME(crypto_sign_open)(
-#endif
-  unsigned char *m, unsigned long long *mlen,
-  const unsigned char *sm, unsigned long long smlen,
-  const unsigned char *pk)
+  uint8_t *m, size_t *mlen,
+  const uint8_t *sm, size_t smlen,
+  const uint8_t *pk)
 {
     int result;
     *mlen=smlen-CRYPTO_BYTES;
@@ -76,3 +63,21 @@
 }
 
 
+int crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m, size_t mlen, const uint8_t *sk)
+{
+    int result;
+    *siglen = CRYPTO_BYTES;
+    result = signHFE(sig,m,mlen,(UINT*)sk);
+    return result;
+}
+
+int crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m, size_t mlen, const uint8_t *pk)
+{
+    int result;
+    if (siglen == CRYPTO_BYTES) {
+      result = sign_openHFE(m,mlen,sig,pk);
+    } else {
+      result = -1;
+    }
+    return result;
+}

