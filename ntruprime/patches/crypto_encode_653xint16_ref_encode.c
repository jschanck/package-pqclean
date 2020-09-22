--- upstream/crypto_encode/653xint16/ref/encode.c
+++ upstream-patched/crypto_encode/653xint16/ref/encode.c
@@ -8,7 +8,7 @@
 
   for (i = 0;i < 653;++i) {
     crypto_uint16 u = *x++;
-    *s++ = u;
-    *s++ = u >> 8;
+    *s++ = (unsigned char) u;
+    *s++ = (unsigned char) (u >> 8);
   }
 }

