--- upstream/AVX_Implementation_KEM/polymul/matrix.c
+++ upstream-patched/AVX_Implementation_KEM/polymul/matrix.c
@@ -1,17 +1,6 @@
-/*
-// Helper function to print avx vector
-void print_avx2(__m256i a)
-{
-	uint16_t a_array[16];
-	_mm256_maskstore_epi32(&a_array, mask, a);
-	int16_t i;
-	for(i=0; i<16; i++)
-	printf("%u, ", a_array[i]);
-	printf("\n");	
-}
-*/
+#include <immintrin.h>
 
-void transpose_n1(__m256i *M)
+static void transpose_n1(__m256i *M)
 {
 	//int i;
 	register __m256i r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11;

