--- upstream/crypto_sign/falcon512dyn/avx2/fpr.h
+++ upstream-patched/crypto_sign/falcon512dyn/avx2/fpr.h
@@ -32,8 +32,12 @@
 
 /* ====================================================================== */
 
+#include <immintrin.h>
 #include <math.h>
 
+#define FMADD(a, b, c)   _mm256_add_pd(_mm256_mul_pd(a, b), c)
+#define FMSUB(a, b, c)   _mm256_sub_pd(_mm256_mul_pd(a, b), c)
+
 /*
  * We wrap the native 'double' type into a structure so that the C compiler
  * complains if we inadvertently use raw arithmetic operators on the 'fpr'
@@ -218,7 +222,6 @@
 	return FPR(x.v / y.v);
 }
 
-TARGET_AVX2
 static inline void
 fpr_sqrt_avx2(double *t)
 {
@@ -276,7 +279,6 @@
 	return x.v < y.v;
 }
 
-TARGET_AVX2
 static inline uint64_t
 fpr_expm_p63(fpr x, fpr ccs)
 {

