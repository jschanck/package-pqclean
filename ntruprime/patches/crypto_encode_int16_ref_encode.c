--- upstream/crypto_encode/int16/ref/encode.c
+++ upstream-patched/crypto_encode/int16/ref/encode.c
@@ -1,9 +1,10 @@
 #include "crypto_encode.h"
 #include "crypto_uint16.h"
+#define uint16 crypto_uint16
 
 void crypto_encode(unsigned char *s,const void *x)
 {
-  crypto_uint16 u = *(const crypto_uint16 *) x;
-  s[0] = u;
-  s[1] = u >> 8;
+  uint16 u = *(const uint16 *) x;
+  s[0] = (unsigned char) u;
+  s[1] = (unsigned char) (u >> 8);
 }

