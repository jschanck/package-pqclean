--- upstream/AVX_Implementation_KEM/polymul/scm_avx.c
+++ upstream-patched/AVX_Implementation_KEM/polymul/scm_avx.c
@@ -2,13 +2,14 @@
 
 //#pragma STDC FP_CONTRACT ON
 
+#include <immintrin.h>
 
 inline __m256i mul_add(__m256i a, __m256i b, __m256i c) { 
     return _mm256_add_epi16(_mm256_mullo_epi16(a, b), c);
 }
 
 
-void schoolbook_avx_new3_acc(__m256i* a, __m256i* b, __m256i* c_avx) ////8 coefficients of a and b has been prefetched
+static void schoolbook_avx_new3_acc(__m256i* a, __m256i* b, __m256i* c_avx) ////8 coefficients of a and b has been prefetched
 									      //the c_avx are added cummulatively
 {
 
@@ -410,7 +411,7 @@
 
 
 
-void schoolbook_avx_new2(__m256i* a, __m256i* b, __m256i* c_avx) ////8 coefficients of a and b has been prefetched
+static void schoolbook_avx_new2(__m256i* a, __m256i* b, __m256i* c_avx) ////8 coefficients of a and b has been prefetched
 									      //the c_avx are not added cummulatively
 {
 

