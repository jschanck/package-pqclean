--- upstream/avx2/fips202x4.c
+++ upstream-patched/avx2/fips202x4.c
@@ -6,7 +6,7 @@
 #include "fips202x4.h"
 
 /* Use implementation from the Keccak Code Package */
-#define KeccakF1600_StatePermute4x FIPS202X4_NAMESPACE(_KeccakP1600times4_PermuteAll_24rounds)
+#define KeccakF1600_StatePermute4x KeccakP1600times4_PermuteAll_24rounds
 extern void KeccakF1600_StatePermute4x(__m256i *s);
 
 static inline void store64(uint8_t x[8], uint64_t u) {
@@ -55,14 +55,14 @@
 
   if(inlen) {
     t = _mm256_i64gather_epi64((long long *)pos, idx, 1);
-    idx = _mm256_set1_epi64x((1ULL << (8*inlen)) - 1);
+    idx = _mm256_set1_epi64x((long long)((1ULL << (8*inlen)) - 1));
     t = _mm256_and_si256(t, idx);
     s[i] = _mm256_xor_si256(s[i], t);
   }
 
   t = _mm256_set1_epi64x((uint64_t)p << 8*inlen);
   s[i] = _mm256_xor_si256(s[i], t);
-  t = _mm256_set1_epi64x(1ULL << 63);
+  t = _mm256_set1_epi64x((long long)(1ULL << 63));
   s[r/8 - 1] = _mm256_xor_si256(s[r/8 - 1], t);
 }
 

