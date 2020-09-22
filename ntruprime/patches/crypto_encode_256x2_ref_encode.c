--- upstream/crypto_encode/256x2/ref/encode.c
+++ upstream-patched/crypto_encode/256x2/ref/encode.c
@@ -5,5 +5,5 @@
   const unsigned char *r = v;
   int i;
   for (i = 0;i < 32;++i) s[i] = 0;
-  for (i = 0;i < 256;++i) s[i>>3] |= (r[i]&1)<<(i&7);
+  for (i = 0;i < 256;++i) s[i>>3] |= (unsigned char) ((r[i]&1)<<(i&7));
 }

