--- upstream/crypto_encode/857x1723round/ref/encode.c
+++ upstream-patched/crypto_encode/857x1723round/ref/encode.c
@@ -12,6 +12,6 @@
   int16 x[p];
   int i;
 
-  for (i = 0;i < p;++i) x[i] = 3*((10923*a[i]+16384)>>15);
+  for (i = 0;i < p;++i) x[i] = (int16) (3*((10923*a[i]+16384)>>15));
   crypto_encode_857x1723(out,x);
 }

