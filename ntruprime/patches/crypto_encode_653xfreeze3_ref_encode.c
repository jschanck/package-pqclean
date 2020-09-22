--- upstream/crypto_encode/653xfreeze3/ref/encode.c
+++ upstream-patched/crypto_encode/653xfreeze3/ref/encode.c
@@ -11,9 +11,9 @@
 /* all inputs: 3 divides x-F3_freeze(x) */
 /* and F3_freeze(x) is in {-2,-1,0,1,2} */
 
-static inline char F3_freeze(int16 x)
+static inline unsigned char F3_freeze(int16 x)
 {
-  return x-3*((10923*x+16384)>>15);
+  return (unsigned char) (x-3*((10923*x+16384)>>15));
 }
 
 void crypto_encode(unsigned char *s,const void *v)

