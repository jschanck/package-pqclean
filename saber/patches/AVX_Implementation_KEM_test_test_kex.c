--- upstream/AVX_Implementation_KEM/test/test_kex.c
+++ upstream-patched/AVX_Implementation_KEM/test/test_kex.c
@@ -112,8 +112,8 @@
 	printf("Average time sample_matrix: \t %lu \n",clock_matrix/count_enc);
 	printf("Average times sample_secret: \t %lu \n",clock_secret/count_enc);
 	printf("Average times (matrix_vector + vector_vector) mul: \t %lu \n",clock_mv_vv_mul/count_enc);
-	printf("Average times single (matrix_vector + vector_vector) mul: \t %lu \n",clock_mv_vv_mul/((SABER_K*SABER_K+SABER_K)*count_enc));
-	printf("Average times polynomial mul: \t %lu \n",clock_mul/(SABER_K*count_mul));
+	printf("Average times single (matrix_vector + vector_vector) mul: \t %lu \n",clock_mv_vv_mul/((SABER_L*SABER_L+SABER_L)*count_enc));
+	printf("Average times polynomial mul: \t %lu \n",clock_mul/(SABER_L*count_mul));
 	printf("Only indcpa key-pair: \t %lu \n",clock_kp_kex/repeat);
 	printf("Time for (KEM_kp-indcpa_kp): \t %lu \n", clock_kp_temp/repeat);
 	printf("Only indcpa enc: \t %lu \n",clock_enc_kex/repeat);

