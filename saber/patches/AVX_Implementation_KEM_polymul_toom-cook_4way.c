--- upstream/AVX_Implementation_KEM/polymul/toom-cook_4way.c
+++ upstream-patched/AVX_Implementation_KEM/polymul/toom-cook_4way.c
@@ -3,16 +3,10 @@
 */
 //#include "timing.c"
 #include "consts.h"
-#include "scm_avx.c"
 #include "matrix.c"
+#include "scm_avx.c"
 
-void TC_interpol(__m256i *c_bucket, __m256i* res_avx_output);
-void KARA_interpol(__m256i *c_bucket, __m256i* result_final0, __m256i* result_final1, __m256i* result_final2, __m256i* result_final3, __m256i* result_final4, __m256i* result_final5, __m256i* result_final6);
-void KARA_eval(__m256i* b, __m256i *b_bucket);
-void TC_eval(__m256i* b_avx, __m256i* b_bucket);
-
-
-void batch_64coefficient_multiplications_new(__m256i* a, __m256i* b_bucket, __m256i* c_bucket, int f)//all 7 Karatsuba evaluation and interpolation are done in AVX.
+static void batch_64coefficient_multiplications_new(__m256i* a, __m256i* b_bucket, __m256i* c_bucket, int f)//all 7 Karatsuba evaluation and interpolation are done in AVX.
 {
 	__m256i a_bucket[SCM_SIZE*4]; //SCM_SIZE = 16; Holds evaluation (a & b) for 7 Karatsuba at a time
 
@@ -218,7 +212,7 @@
 		
 }
 
-void KARA_eval(__m256i* b, __m256i *b_bucket){
+static void KARA_eval(__m256i* b, __m256i *b_bucket){
 
 	__m256i r0_avx, r1_avx, r2_avx, r3_avx;
 
@@ -340,7 +334,7 @@
 			transpose_n1(b_bucket+48);	
 }
 
-void KARA_interpol(__m256i *c_bucket, __m256i* result_final0, __m256i* result_final1, __m256i* result_final2, __m256i* result_final3, __m256i* result_final4, __m256i* result_final5, __m256i* result_final6){
+static void KARA_interpol(__m256i *c_bucket, __m256i* result_final0, __m256i* result_final1, __m256i* result_final2, __m256i* result_final3, __m256i* result_final4, __m256i* result_final5, __m256i* result_final6){
 
 		//int64_t i;
 		register __m256i res_avx0, res_avx1, res_avx2, res_avx3, res_avx4, res_avx5, res_avx6, res_avx7; // to hold each 64X64 poly mul results
@@ -823,7 +817,7 @@
 
 }
 
-void toom_cook_4way_avx_n1(__m256i* a_avx,__m256i* b_bucket, __m256i *c_bucket, int f){ 
+static void toom_cook_4way_avx_n1(__m256i* a_avx,__m256i* b_bucket, __m256i *c_bucket, int f){ 
 
 	int i;
 
@@ -873,7 +867,7 @@
 
 }
 
-void TC_eval(__m256i* b_avx, __m256i* b_bucket){
+static void TC_eval(__m256i* b_avx, __m256i* b_bucket){
 
 	int i;
 	__m256i bw_avx[7*small_len_avx];
@@ -912,7 +906,7 @@
 }
 
 
-void TC_interpol(__m256i *c_bucket, __m256i* res_avx){
+static void TC_interpol(__m256i *c_bucket, __m256i* res_avx){
 
 	int i;
 
@@ -964,22 +958,22 @@
 		r1_avx = _mm256_sub_epi16(r1_avx, r2_avx);
 		r2_avx = _mm256_sub_epi16(r2_avx, r6_avx);
 		r2_avx = _mm256_sub_epi16(r2_avx, r0_avx);
-		temp_avx = _mm256_mullo_epi16 (r2_avx,int45_avx);
+		temp_avx = _mm256_mullo_epi16 (r2_avx, _mm256_set1_epi16(45));
 		r1_avx = _mm256_add_epi16(r1_avx, temp_avx);
 		temp_avx = _mm256_slli_epi16(r2_avx, 3);
 		r4_avx = _mm256_sub_epi16(r4_avx, temp_avx);
-		r4_avx = _mm256_mullo_epi16 (r4_avx,inv3_avx);
+		r4_avx = _mm256_mullo_epi16 (r4_avx, _mm256_set1_epi16(-21845)); // -21845 = 1/3 (mod 2^16)
 		r4_avx = _mm256_srli_epi16(r4_avx, 3);
 		r5_avx = _mm256_add_epi16(r5_avx, r1_avx);
 		temp_avx = _mm256_slli_epi16(r3_avx, 4);
 		r1_avx= _mm256_add_epi16(r1_avx, temp_avx);
-		r1_avx = _mm256_mullo_epi16 (r1_avx, inv9_avx);
+		r1_avx = _mm256_mullo_epi16 (r1_avx, _mm256_set1_epi16(-29127)); // -29127 = 1/9 (mod 2^16)
 		r1_avx= _mm256_srli_epi16(r1_avx, 1); 	
 		r3_avx= _mm256_add_epi16(r1_avx, r3_avx);
-		r3_avx= _mm256_sub_epi16(int0_avx, r3_avx);
-		temp_avx= _mm256_mullo_epi16 (r1_avx,int30_avx);
+		r3_avx= _mm256_sub_epi16(_mm256_set1_epi16(0), r3_avx);
+		temp_avx= _mm256_mullo_epi16 (r1_avx, _mm256_set1_epi16(30));
 		temp_avx= _mm256_sub_epi16(temp_avx, r5_avx);
-		temp_avx= _mm256_mullo_epi16 (temp_avx ,inv15_avx);
+		temp_avx= _mm256_mullo_epi16 (temp_avx, _mm256_set1_epi16(-4369)); // -4369 = 1/15 (mod 2^16)
 		r5_avx= _mm256_srli_epi16(temp_avx, 2);
 		r2_avx = _mm256_sub_epi16(r2_avx, r4_avx);
 		r1_avx = _mm256_sub_epi16(r1_avx, r5_avx);
@@ -1009,6 +1003,8 @@
 
 	// Reduction by X^256 + 1
 	for(i=0; i<16; i++)
+  {
 		res_avx[i] = _mm256_sub_epi16(res_avx_output[i], res_avx_output[i+16]);
+  }
 
 }

