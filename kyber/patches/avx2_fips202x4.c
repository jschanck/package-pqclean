--- upstream/avx2/fips202x4.c
+++ upstream-patched/avx2/fips202x4.c
@@ -6,7 +6,7 @@
 #include "fips202x4.h"
 
 /* Use implementation from the Keccak Code Package */
-#define KeccakF1600_StatePermute4x FIPS202X4_NAMESPACE(KeccakP1600times4_PermuteAll_24rounds)
+#define KeccakF1600_StatePermute4x KeccakP1600times4_PermuteAll_24rounds
 extern void KeccakF1600_StatePermute4x(__m256i *s);
 
 static void keccakx4_absorb_once(__m256i s[25],
@@ -46,14 +46,14 @@
 
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
 
@@ -67,16 +67,21 @@
 {
   unsigned int i;
   __m128d t;
+  double tmp;
 
   while(nblocks > 0) {
     KeccakF1600_StatePermute4x(s);
     for(i=0; i < r/8; ++i) {
       t = _mm_castsi128_pd(_mm256_castsi256_si128(s[i]));
-      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out0[8*i], t);
-      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out1[8*i], t);
+      _mm_storel_pd(&tmp, t);
+      memcpy(&out0[8*i], &tmp, 8);
+      _mm_storeh_pd(&tmp, t);
+      memcpy(&out1[8*i], &tmp, 8);
       t = _mm_castsi128_pd(_mm256_extracti128_si256(s[i],1));
-      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out2[8*i], t);
-      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out3[8*i], t);
+      _mm_storel_pd(&tmp, t);
+      memcpy(&out2[8*i], &tmp, 8);
+      _mm_storeh_pd(&tmp, t);
+      memcpy(&out3[8*i], &tmp, 8);
     }
 
     out0 += r;

