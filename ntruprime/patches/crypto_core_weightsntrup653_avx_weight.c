--- upstream/crypto_core/weightsntrup653/avx/weight.c
+++ upstream-patched/crypto_core/weightsntrup653/avx/weight.c
@@ -18,7 +18,7 @@
   int16 weight;
 
   sum = _mm256_loadu_si256((__m256i *) (in+p-32));
-  sum &= endingmask;
+  sum &= _mm256_set_epi8(1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
 
   for (i = p-32;i >= 0;i -= 32) {
     __m256i bits = _mm256_loadu_si256((__m256i *) in);
@@ -40,8 +40,8 @@
   sum = _mm256_hadd_epi16(sum,sum);
   /* want sum[0]+sum[8] */
 
-  weight = _mm256_extract_epi16(sum,0);
-  weight += _mm256_extract_epi16(sum,8);
+  weight = (int16) _mm256_extract_epi16(sum,0);
+  weight += (int16) _mm256_extract_epi16(sum,8);
 
   crypto_encode_int16(outbytes,&weight);
   return 0;

