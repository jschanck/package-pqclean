--- upstream/crypto_core/weightsntrup761/avx/weight.c
+++ upstream-patched/crypto_core/weightsntrup761/avx/weight.c
@@ -40,8 +40,8 @@
   sum = _mm256_hadd_epi16(sum,sum);
   /* want sum[0]+sum[8] */
 
-  weight = _mm256_extract_epi16(sum,0);
-  weight += _mm256_extract_epi16(sum,8);
+  weight = (int16) _mm256_extract_epi16(sum,0);
+  weight += (int16) _mm256_extract_epi16(sum,8);
 
   crypto_encode_int16(outbytes,&weight);
   return 0;

