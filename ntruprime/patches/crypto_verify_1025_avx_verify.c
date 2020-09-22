--- upstream/crypto_verify/1025/avx/verify.c
+++ upstream-patched/crypto_verify/1025/avx/verify.c
@@ -26,10 +26,10 @@
   diff |= _mm256_srli_epi32(diff,16);
   diff |= _mm256_srli_epi64(diff,32);
 
-  differentbits = _mm256_extract_epi8(diff,0);
-  differentbits |= _mm256_extract_epi8(diff,8);
-  differentbits |= _mm256_extract_epi8(diff,16);
-  differentbits |= _mm256_extract_epi8(diff,24);
+  differentbits = (unsigned int) _mm256_extract_epi8(diff,0);
+  differentbits |= (unsigned int) _mm256_extract_epi8(diff,8);
+  differentbits |= (unsigned int) _mm256_extract_epi8(diff,16);
+  differentbits |= (unsigned int) _mm256_extract_epi8(diff,24);
 
-  return (1 & ((differentbits - 1) >> 8)) - 1;
+  return (int) (1 & ((differentbits - 1) >> 8)) - 1;
 }

