--- upstream/crypto_decode/653x3/ref/decode.c
+++ upstream-patched/crypto_decode/653x3/ref/decode.c
@@ -12,11 +12,11 @@
 
   for (i = 0;i < p/4;++i) {
     x = *s++;
-    *f++ = ((uint8)(x&3))-1; x >>= 2;
-    *f++ = ((uint8)(x&3))-1; x >>= 2;
-    *f++ = ((uint8)(x&3))-1; x >>= 2;
-    *f++ = ((uint8)(x&3))-1;
+    *f++ = (uint8) ((x&3)-1); x >>= 2;
+    *f++ = (uint8) ((x&3)-1); x >>= 2;
+    *f++ = (uint8) ((x&3)-1); x >>= 2;
+    *f++ = (uint8) ((x&3)-1);
   }
   x = *s++;
-  *f++ = ((uint8)(x&3))-1;
+  *f++ = (uint8) ((x&3)-1);
 }

