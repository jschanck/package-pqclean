--- upstream/avx2/fips202x4.c
+++ upstream-patched/avx2/fips202x4.c
@@ -5,6 +5,36 @@
 #include "fips202.h"
 #include "fips202x4.h"
 
+#define NROUNDS 24
+
+/* Keccak round constants */
+static const uint64_t KeccakF_RoundConstants[NROUNDS] = {
+  (uint64_t)0x0000000000000001ULL,
+  (uint64_t)0x0000000000008082ULL,
+  (uint64_t)0x800000000000808aULL,
+  (uint64_t)0x8000000080008000ULL,
+  (uint64_t)0x000000000000808bULL,
+  (uint64_t)0x0000000080000001ULL,
+  (uint64_t)0x8000000080008081ULL,
+  (uint64_t)0x8000000000008009ULL,
+  (uint64_t)0x000000000000008aULL,
+  (uint64_t)0x0000000000000088ULL,
+  (uint64_t)0x0000000080008009ULL,
+  (uint64_t)0x000000008000000aULL,
+  (uint64_t)0x000000008000808bULL,
+  (uint64_t)0x800000000000008bULL,
+  (uint64_t)0x8000000000008089ULL,
+  (uint64_t)0x8000000000008003ULL,
+  (uint64_t)0x8000000000008002ULL,
+  (uint64_t)0x8000000000000080ULL,
+  (uint64_t)0x000000000000800aULL,
+  (uint64_t)0x800000008000000aULL,
+  (uint64_t)0x8000000080008081ULL,
+  (uint64_t)0x8000000000008080ULL,
+  (uint64_t)0x0000000080000001ULL,
+  (uint64_t)0x8000000080008008ULL
+};
+
 static void keccakx4_absorb_once(__m256i s[25],
                                  unsigned int r,
                                  const uint8_t *in0,
@@ -42,14 +72,14 @@
 
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
 
@@ -62,17 +92,22 @@
                                    __m256i s[25])
 {
   unsigned int i;
+  double temp0, temp1;
   __m128d t;
 
   while(nblocks > 0) {
     f1600x4(s, KeccakF_RoundConstants);
     for(i=0; i < r/8; ++i) {
       t = _mm_castsi128_pd(_mm256_castsi256_si128(s[i]));
-      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out0[8*i], t);
-      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out1[8*i], t);
+      _mm_storel_pd(&temp0, t);
+      _mm_storeh_pd(&temp1, t);
+      memcpy(&out0[8 * i], &temp0, sizeof(double));
+      memcpy(&out1[8 * i], &temp1, sizeof(double));
       t = _mm_castsi128_pd(_mm256_extracti128_si256(s[i],1));
-      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out2[8*i], t);
-      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out3[8*i], t);
+      _mm_storel_pd(&temp0, t);
+      _mm_storeh_pd(&temp1, t);
+      memcpy(&out2[8 * i], &temp0, sizeof(double));
+      memcpy(&out3[8 * i], &temp1, sizeof(double));
     }
 
     out0 += r;

