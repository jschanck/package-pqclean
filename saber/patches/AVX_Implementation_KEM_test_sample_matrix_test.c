--- upstream/AVX_Implementation_KEM/test/sample_matrix_test.c
+++ upstream-patched/AVX_Implementation_KEM/test/sample_matrix_test.c
@@ -17,7 +17,7 @@
 {
 
   unsigned char seed[SABER_SEEDBYTES];
-  polyvec a[SABER_K];
+  polyvec a[SABER_L];
 	
 	
   uint64_t i, repeat;

