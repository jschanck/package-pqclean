--- upstream/crypto_core/multsntrup857/avx/ntt.h
+++ upstream-patched/crypto_core/multsntrup857/avx/ntt.h
@@ -8,9 +8,9 @@
 #define invntt512_7681 CRYPTO_NAMESPACE(invntt512_7681)
 #define invntt512_10753 CRYPTO_NAMESPACE(invntt512_10753)
 
-extern void ntt512_7681(int16_t *,int);
-extern void ntt512_10753(int16_t *,int);
-extern void invntt512_7681(int16_t *,int);
-extern void invntt512_10753(int16_t *,int);
+extern void ntt512_7681(int16_t *f,int reps);
+extern void ntt512_10753(int16_t *f,int reps);
+extern void invntt512_7681(int16_t *f,int reps);
+extern void invntt512_10753(int16_t *f,int reps);
 
 #endif

