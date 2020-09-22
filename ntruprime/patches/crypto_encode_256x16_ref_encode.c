--- upstream/crypto_encode/256x16/ref/encode.c
+++ upstream-patched/crypto_encode/256x16/ref/encode.c
@@ -5,5 +5,5 @@
   const unsigned char *T = v;
   int i;
   for (i = 0;i < 128;++i)
-    s[i] = T[2*i]+(T[2*i+1]<<4);
+    s[i] = (unsigned char) (T[2*i]+(T[2*i+1]<<4));
 }

