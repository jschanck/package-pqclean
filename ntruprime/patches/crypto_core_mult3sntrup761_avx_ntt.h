--- upstream/crypto_core/mult3sntrup761/avx/ntt.h
+++ upstream-patched/crypto_core/mult3sntrup761/avx/ntt.h
@@ -6,7 +6,7 @@
 #define ntt512_7681 CRYPTO_NAMESPACE(ntt512_7681)
 #define invntt512_7681 CRYPTO_NAMESPACE(invntt512_7681)
 
-extern void ntt512_7681(int16_t *,int);
-extern void invntt512_7681(int16_t *,int);
+extern void ntt512_7681(int16_t *f,int reps);
+extern void invntt512_7681(int16_t *f,int reps);
 
 #endif

