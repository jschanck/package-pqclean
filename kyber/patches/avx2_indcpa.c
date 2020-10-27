--- upstream/avx2/indcpa.c
+++ upstream-patched/avx2/indcpa.c
@@ -1,5 +1,6 @@
 #include <stddef.h>
 #include <stdint.h>
+#include "align.h"
 #include "params.h"
 #include "indcpa.h"
 #include "poly.h"
@@ -175,10 +176,8 @@
 void gen_matrix(polyvec *a, const uint8_t seed[KYBER_SYMBYTES], int transposed)
 {
   unsigned int ctr, i, j;
-  __attribute__((aligned(16)))
-  uint64_t nonce;
-  __attribute__((aligned(32)))
-  uint8_t buf[GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES];
+  ALIGN16_TYPE(uint64_t) nonce = {.orig = 0};
+  ALIGN32_ARRAY(uint8_t, GEN_MATRIX_NBLOCKS * XOF_BLOCKBYTES) buf;
   aes256ctr_ctx state;
 
   aes256ctr_init(&state, seed, 0);
@@ -186,17 +185,17 @@
   for(i=0;i<KYBER_K;i++) {
     for(j=0;j<KYBER_K;j++) {
       if(transposed)
-        nonce = (j << 8) | i;
+        nonce.orig = (j << 8) | i;
       else
-        nonce = (i << 8) | j;
+        nonce.orig = (i << 8) | j;
 
-      state.n = _mm_loadl_epi64((__m128i *)&nonce);
-      aes256ctr_squeezeblocks(buf, GEN_MATRIX_NBLOCKS, &state);
-      ctr = rej_uniform_avx(a[i].vec[j].coeffs, buf);
+      state.n = _mm_loadl_epi64(&nonce.vec);
+      aes256ctr_squeezeblocks(buf.arr, GEN_MATRIX_NBLOCKS, &state);
+      ctr = rej_uniform_avx(a[i].vec[j].coeffs, buf.arr);
 
       while(ctr < KYBER_N) {
-        aes256ctr_squeezeblocks(buf, 1, &state);
-        ctr += rej_uniform(a[i].vec[j].coeffs + ctr, KYBER_N - ctr, buf,
+        aes256ctr_squeezeblocks(buf.arr, 1, &state);
+        ctr += rej_uniform(a[i].vec[j].coeffs + ctr, KYBER_N - ctr, buf.arr,
                            XOF_BLOCKBYTES);
       }
 
@@ -209,57 +208,56 @@
 void gen_matrix(polyvec *a, const uint8_t seed[32], int transposed)
 {
   unsigned int ctr0, ctr1, ctr2, ctr3;
-  __attribute__((aligned(32)))
-  uint8_t buf[4][(GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES+31)/32*32];
+  ALIGN32_ARRAY_2D(uint8_t, 4, (GEN_MATRIX_NBLOCKS * XOF_BLOCKBYTES + 31) / 32 * 32) buf;
   __m256i f;
   keccakx4_state state;
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
 
   if(transposed) {
-    buf[0][KYBER_SYMBYTES+0] = 0;
-    buf[0][KYBER_SYMBYTES+1] = 0;
-    buf[1][KYBER_SYMBYTES+0] = 0;
-    buf[1][KYBER_SYMBYTES+1] = 1;
-    buf[2][KYBER_SYMBYTES+0] = 1;
-    buf[2][KYBER_SYMBYTES+1] = 0;
-    buf[3][KYBER_SYMBYTES+0] = 1;
-    buf[3][KYBER_SYMBYTES+1] = 1;
+    buf.arr[0][KYBER_SYMBYTES+0] = 0;
+    buf.arr[0][KYBER_SYMBYTES+1] = 0;
+    buf.arr[1][KYBER_SYMBYTES+0] = 0;
+    buf.arr[1][KYBER_SYMBYTES+1] = 1;
+    buf.arr[2][KYBER_SYMBYTES+0] = 1;
+    buf.arr[2][KYBER_SYMBYTES+1] = 0;
+    buf.arr[3][KYBER_SYMBYTES+0] = 1;
+    buf.arr[3][KYBER_SYMBYTES+1] = 1;
   }
   else {
-    buf[0][KYBER_SYMBYTES+0] = 0;
-    buf[0][KYBER_SYMBYTES+1] = 0;
-    buf[1][KYBER_SYMBYTES+0] = 1;
-    buf[1][KYBER_SYMBYTES+1] = 0;
-    buf[2][KYBER_SYMBYTES+0] = 0;
-    buf[2][KYBER_SYMBYTES+1] = 1;
-    buf[3][KYBER_SYMBYTES+0] = 1;
-    buf[3][KYBER_SYMBYTES+1] = 1;
+    buf.arr[0][KYBER_SYMBYTES+0] = 0;
+    buf.arr[0][KYBER_SYMBYTES+1] = 0;
+    buf.arr[1][KYBER_SYMBYTES+0] = 1;
+    buf.arr[1][KYBER_SYMBYTES+1] = 0;
+    buf.arr[2][KYBER_SYMBYTES+0] = 0;
+    buf.arr[2][KYBER_SYMBYTES+1] = 1;
+    buf.arr[3][KYBER_SYMBYTES+0] = 1;
+    buf.arr[3][KYBER_SYMBYTES+1] = 1;
   }
 
-  shake128x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], KYBER_SYMBYTES+2);
-  shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], GEN_MATRIX_NBLOCKS,
+  shake128x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], KYBER_SYMBYTES+2);
+  shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], GEN_MATRIX_NBLOCKS,
                            &state);
 
-  ctr0 = rej_uniform_avx(a[0].vec[0].coeffs, buf[0]);
-  ctr1 = rej_uniform_avx(a[0].vec[1].coeffs, buf[1]);
-  ctr2 = rej_uniform_avx(a[1].vec[0].coeffs, buf[2]);
-  ctr3 = rej_uniform_avx(a[1].vec[1].coeffs, buf[3]);
+  ctr0 = rej_uniform_avx(a[0].vec[0].coeffs, buf.arr[0]);
+  ctr1 = rej_uniform_avx(a[0].vec[1].coeffs, buf.arr[1]);
+  ctr2 = rej_uniform_avx(a[1].vec[0].coeffs, buf.arr[2]);
+  ctr3 = rej_uniform_avx(a[1].vec[1].coeffs, buf.arr[3]);
 
   while(ctr0 < KYBER_N || ctr1 < KYBER_N || ctr2 < KYBER_N || ctr3 < KYBER_N) {
-    shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 1, &state);
+    shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 1, &state);
 
-    ctr0 += rej_uniform(a[0].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf[0],
+    ctr0 += rej_uniform(a[0].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf.arr[0],
                         XOF_BLOCKBYTES);
-    ctr1 += rej_uniform(a[0].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf[1],
+    ctr1 += rej_uniform(a[0].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf.arr[1],
                         XOF_BLOCKBYTES);
-    ctr2 += rej_uniform(a[1].vec[0].coeffs + ctr2, KYBER_N - ctr2, buf[2],
+    ctr2 += rej_uniform(a[1].vec[0].coeffs + ctr2, KYBER_N - ctr2, buf.arr[2],
                         XOF_BLOCKBYTES);
-    ctr3 += rej_uniform(a[1].vec[1].coeffs + ctr3, KYBER_N - ctr3, buf[3],
+    ctr3 += rej_uniform(a[1].vec[1].coeffs + ctr3, KYBER_N - ctr3, buf.arr[3],
                         XOF_BLOCKBYTES);
   }
 
@@ -272,58 +270,57 @@
 void gen_matrix(polyvec *a, const uint8_t seed[32], int transposed)
 {
   unsigned int ctr0, ctr1, ctr2, ctr3;
-  __attribute__((aligned(32)))
-  uint8_t buf[4][(GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES+31)/32*32];
+  ALIGN32_ARRAY_2D(uint8_t, 4, (GEN_MATRIX_NBLOCKS * XOF_BLOCKBYTES + 31) / 32 * 32) buf;
   __m256i f;
   keccakx4_state state;
-  keccak_state state1x;
+  xof_state state1x;
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
 
   if(transposed) {
-    buf[0][KYBER_SYMBYTES+0] = 0;
-    buf[0][KYBER_SYMBYTES+1] = 0;
-    buf[1][KYBER_SYMBYTES+0] = 0;
-    buf[1][KYBER_SYMBYTES+1] = 1;
-    buf[2][KYBER_SYMBYTES+0] = 0;
-    buf[2][KYBER_SYMBYTES+1] = 2;
-    buf[3][KYBER_SYMBYTES+0] = 1;
-    buf[3][KYBER_SYMBYTES+1] = 0;
+    buf.arr[0][KYBER_SYMBYTES+0] = 0;
+    buf.arr[0][KYBER_SYMBYTES+1] = 0;
+    buf.arr[1][KYBER_SYMBYTES+0] = 0;
+    buf.arr[1][KYBER_SYMBYTES+1] = 1;
+    buf.arr[2][KYBER_SYMBYTES+0] = 0;
+    buf.arr[2][KYBER_SYMBYTES+1] = 2;
+    buf.arr[3][KYBER_SYMBYTES+0] = 1;
+    buf.arr[3][KYBER_SYMBYTES+1] = 0;
   }
   else {
-    buf[0][KYBER_SYMBYTES+0] = 0;
-    buf[0][KYBER_SYMBYTES+1] = 0;
-    buf[1][KYBER_SYMBYTES+0] = 1;
-    buf[1][KYBER_SYMBYTES+1] = 0;
-    buf[2][KYBER_SYMBYTES+0] = 2;
-    buf[2][KYBER_SYMBYTES+1] = 0;
-    buf[3][KYBER_SYMBYTES+0] = 0;
-    buf[3][KYBER_SYMBYTES+1] = 1;
+    buf.arr[0][KYBER_SYMBYTES+0] = 0;
+    buf.arr[0][KYBER_SYMBYTES+1] = 0;
+    buf.arr[1][KYBER_SYMBYTES+0] = 1;
+    buf.arr[1][KYBER_SYMBYTES+1] = 0;
+    buf.arr[2][KYBER_SYMBYTES+0] = 2;
+    buf.arr[2][KYBER_SYMBYTES+1] = 0;
+    buf.arr[3][KYBER_SYMBYTES+0] = 0;
+    buf.arr[3][KYBER_SYMBYTES+1] = 1;
   }
 
-  shake128x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], KYBER_SYMBYTES+2);
-  shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], GEN_MATRIX_NBLOCKS,
+  shake128x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], KYBER_SYMBYTES+2);
+  shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], GEN_MATRIX_NBLOCKS,
                            &state);
 
-  ctr0 = rej_uniform_avx(a[0].vec[0].coeffs, buf[0]);
-  ctr1 = rej_uniform_avx(a[0].vec[1].coeffs, buf[1]);
-  ctr2 = rej_uniform_avx(a[0].vec[2].coeffs, buf[2]);
-  ctr3 = rej_uniform_avx(a[1].vec[0].coeffs, buf[3]);
+  ctr0 = rej_uniform_avx(a[0].vec[0].coeffs, buf.arr[0]);
+  ctr1 = rej_uniform_avx(a[0].vec[1].coeffs, buf.arr[1]);
+  ctr2 = rej_uniform_avx(a[0].vec[2].coeffs, buf.arr[2]);
+  ctr3 = rej_uniform_avx(a[1].vec[0].coeffs, buf.arr[3]);
 
   while(ctr0 < KYBER_N || ctr1 < KYBER_N || ctr2 < KYBER_N || ctr3 < KYBER_N) {
-    shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 1, &state);
+    shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 1, &state);
 
-    ctr0 += rej_uniform(a[0].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf[0],
+    ctr0 += rej_uniform(a[0].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf.arr[0],
                         XOF_BLOCKBYTES);
-    ctr1 += rej_uniform(a[0].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf[1],
+    ctr1 += rej_uniform(a[0].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf.arr[1],
                         XOF_BLOCKBYTES);
-    ctr2 += rej_uniform(a[0].vec[2].coeffs + ctr2, KYBER_N - ctr2, buf[2],
+    ctr2 += rej_uniform(a[0].vec[2].coeffs + ctr2, KYBER_N - ctr2, buf.arr[2],
                         XOF_BLOCKBYTES);
-    ctr3 += rej_uniform(a[1].vec[0].coeffs + ctr3, KYBER_N - ctr3, buf[3],
+    ctr3 += rej_uniform(a[1].vec[0].coeffs + ctr3, KYBER_N - ctr3, buf.arr[3],
                         XOF_BLOCKBYTES);
   }
 
@@ -333,51 +330,51 @@
   poly_nttunpack(&a[1].vec[0]);
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
 
   if(transposed) {
-    buf[0][KYBER_SYMBYTES+0] = 1;
-    buf[0][KYBER_SYMBYTES+1] = 1;
-    buf[1][KYBER_SYMBYTES+0] = 1;
-    buf[1][KYBER_SYMBYTES+1] = 2;
-    buf[2][KYBER_SYMBYTES+0] = 2;
-    buf[2][KYBER_SYMBYTES+1] = 0;
-    buf[3][KYBER_SYMBYTES+0] = 2;
-    buf[3][KYBER_SYMBYTES+1] = 1;
+    buf.arr[0][KYBER_SYMBYTES+0] = 1;
+    buf.arr[0][KYBER_SYMBYTES+1] = 1;
+    buf.arr[1][KYBER_SYMBYTES+0] = 1;
+    buf.arr[1][KYBER_SYMBYTES+1] = 2;
+    buf.arr[2][KYBER_SYMBYTES+0] = 2;
+    buf.arr[2][KYBER_SYMBYTES+1] = 0;
+    buf.arr[3][KYBER_SYMBYTES+0] = 2;
+    buf.arr[3][KYBER_SYMBYTES+1] = 1;
   }
   else {
-    buf[0][KYBER_SYMBYTES+0] = 1;
-    buf[0][KYBER_SYMBYTES+1] = 1;
-    buf[1][KYBER_SYMBYTES+0] = 2;
-    buf[1][KYBER_SYMBYTES+1] = 1;
-    buf[2][KYBER_SYMBYTES+0] = 0;
-    buf[2][KYBER_SYMBYTES+1] = 2;
-    buf[3][KYBER_SYMBYTES+0] = 1;
-    buf[3][KYBER_SYMBYTES+1] = 2;
+    buf.arr[0][KYBER_SYMBYTES+0] = 1;
+    buf.arr[0][KYBER_SYMBYTES+1] = 1;
+    buf.arr[1][KYBER_SYMBYTES+0] = 2;
+    buf.arr[1][KYBER_SYMBYTES+1] = 1;
+    buf.arr[2][KYBER_SYMBYTES+0] = 0;
+    buf.arr[2][KYBER_SYMBYTES+1] = 2;
+    buf.arr[3][KYBER_SYMBYTES+0] = 1;
+    buf.arr[3][KYBER_SYMBYTES+1] = 2;
   }
 
-  shake128x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], KYBER_SYMBYTES+2);
-  shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], GEN_MATRIX_NBLOCKS,
+  shake128x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], KYBER_SYMBYTES+2);
+  shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], GEN_MATRIX_NBLOCKS,
                            &state);
 
-  ctr0 = rej_uniform_avx(a[1].vec[1].coeffs, buf[0]);
-  ctr1 = rej_uniform_avx(a[1].vec[2].coeffs, buf[1]);
-  ctr2 = rej_uniform_avx(a[2].vec[0].coeffs, buf[2]);
-  ctr3 = rej_uniform_avx(a[2].vec[1].coeffs, buf[3]);
+  ctr0 = rej_uniform_avx(a[1].vec[1].coeffs, buf.arr[0]);
+  ctr1 = rej_uniform_avx(a[1].vec[2].coeffs, buf.arr[1]);
+  ctr2 = rej_uniform_avx(a[2].vec[0].coeffs, buf.arr[2]);
+  ctr3 = rej_uniform_avx(a[2].vec[1].coeffs, buf.arr[3]);
 
   while(ctr0 < KYBER_N || ctr1 < KYBER_N || ctr2 < KYBER_N || ctr3 < KYBER_N) {
-    shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 1, &state);
+    shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 1, &state);
 
-    ctr0 += rej_uniform(a[1].vec[1].coeffs + ctr0, KYBER_N - ctr0, buf[0],
+    ctr0 += rej_uniform(a[1].vec[1].coeffs + ctr0, KYBER_N - ctr0, buf.arr[0],
                         XOF_BLOCKBYTES);
-    ctr1 += rej_uniform(a[1].vec[2].coeffs + ctr1, KYBER_N - ctr1, buf[1],
+    ctr1 += rej_uniform(a[1].vec[2].coeffs + ctr1, KYBER_N - ctr1, buf.arr[1],
                         XOF_BLOCKBYTES);
-    ctr2 += rej_uniform(a[2].vec[0].coeffs + ctr2, KYBER_N - ctr2, buf[2],
+    ctr2 += rej_uniform(a[2].vec[0].coeffs + ctr2, KYBER_N - ctr2, buf.arr[2],
                         XOF_BLOCKBYTES);
-    ctr3 += rej_uniform(a[2].vec[1].coeffs + ctr3, KYBER_N - ctr3, buf[3],
+    ctr3 += rej_uniform(a[2].vec[1].coeffs + ctr3, KYBER_N - ctr3, buf.arr[3],
                         XOF_BLOCKBYTES);
   }
 
@@ -387,18 +384,19 @@
   poly_nttunpack(&a[2].vec[1]);
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  buf[0][KYBER_SYMBYTES+0] = 2;
-  buf[0][KYBER_SYMBYTES+1] = 2;
-  shake128_absorb(&state1x, buf[0], KYBER_SYMBYTES+2);
-  shake128_squeezeblocks(buf[0], GEN_MATRIX_NBLOCKS, &state1x);
-  ctr0 = rej_uniform_avx(a[2].vec[2].coeffs, buf[0]);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  buf.arr[0][KYBER_SYMBYTES+0] = 2;
+  buf.arr[0][KYBER_SYMBYTES+1] = 2;
+  shake128_absorb(&state1x, buf.arr[0], KYBER_SYMBYTES+2);
+  shake128_squeezeblocks(buf.arr[0], GEN_MATRIX_NBLOCKS, &state1x);
+  ctr0 = rej_uniform_avx(a[2].vec[2].coeffs, buf.arr[0]);
   while(ctr0 < KYBER_N)
   {
-    shake128_squeezeblocks(buf[0], 1, &state1x);
-    ctr0 += rej_uniform(a[2].vec[2].coeffs + ctr0, KYBER_N - ctr0, buf[0],
+    shake128_squeezeblocks(buf.arr[0], 1, &state1x);
+    ctr0 += rej_uniform(a[2].vec[2].coeffs + ctr0, KYBER_N - ctr0, buf.arr[0],
                         XOF_BLOCKBYTES);
   }
+  shake128_ctx_release(&state1x);
 
   poly_nttunpack(&a[2].vec[2]);
 }
@@ -406,58 +404,57 @@
 void gen_matrix(polyvec *a, const uint8_t seed[32], int transposed)
 {
   unsigned int i, ctr0, ctr1, ctr2, ctr3;
-  __attribute__((aligned(32)))
-  uint8_t buf[4][(GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES+31)/32*32];
+  ALIGN32_ARRAY_2D(uint8_t, 4, (GEN_MATRIX_NBLOCKS * XOF_BLOCKBYTES + 31) / 32 * 32) buf;
   __m256i f;
   keccakx4_state state;
 
   for(i=0;i<4;i++) {
     f = _mm256_load_si256((__m256i *)seed);
-    _mm256_store_si256((__m256i *)buf[0], f);
-    _mm256_store_si256((__m256i *)buf[1], f);
-    _mm256_store_si256((__m256i *)buf[2], f);
-    _mm256_store_si256((__m256i *)buf[3], f);
+    _mm256_store_si256((__m256i *)buf.arr[0], f);
+    _mm256_store_si256((__m256i *)buf.arr[1], f);
+    _mm256_store_si256((__m256i *)buf.arr[2], f);
+    _mm256_store_si256((__m256i *)buf.arr[3], f);
 
     if(transposed) {
-      buf[0][KYBER_SYMBYTES+0] = i;
-      buf[0][KYBER_SYMBYTES+1] = 0;
-      buf[1][KYBER_SYMBYTES+0] = i;
-      buf[1][KYBER_SYMBYTES+1] = 1;
-      buf[2][KYBER_SYMBYTES+0] = i;
-      buf[2][KYBER_SYMBYTES+1] = 2;
-      buf[3][KYBER_SYMBYTES+0] = i;
-      buf[3][KYBER_SYMBYTES+1] = 3;
+      buf.arr[0][KYBER_SYMBYTES+0] = i;
+      buf.arr[0][KYBER_SYMBYTES+1] = 0;
+      buf.arr[1][KYBER_SYMBYTES+0] = i;
+      buf.arr[1][KYBER_SYMBYTES+1] = 1;
+      buf.arr[2][KYBER_SYMBYTES+0] = i;
+      buf.arr[2][KYBER_SYMBYTES+1] = 2;
+      buf.arr[3][KYBER_SYMBYTES+0] = i;
+      buf.arr[3][KYBER_SYMBYTES+1] = 3;
     }
     else {
-      buf[0][KYBER_SYMBYTES+0] = 0;
-      buf[0][KYBER_SYMBYTES+1] = i;
-      buf[1][KYBER_SYMBYTES+0] = 1;
-      buf[1][KYBER_SYMBYTES+1] = i;
-      buf[2][KYBER_SYMBYTES+0] = 2;
-      buf[2][KYBER_SYMBYTES+1] = i;
-      buf[3][KYBER_SYMBYTES+0] = 3;
-      buf[3][KYBER_SYMBYTES+1] = i;
+      buf.arr[0][KYBER_SYMBYTES+0] = 0;
+      buf.arr[0][KYBER_SYMBYTES+1] = i;
+      buf.arr[1][KYBER_SYMBYTES+0] = 1;
+      buf.arr[1][KYBER_SYMBYTES+1] = i;
+      buf.arr[2][KYBER_SYMBYTES+0] = 2;
+      buf.arr[2][KYBER_SYMBYTES+1] = i;
+      buf.arr[3][KYBER_SYMBYTES+0] = 3;
+      buf.arr[3][KYBER_SYMBYTES+1] = i;
     }
 
-    shake128x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], KYBER_SYMBYTES+2);
-    shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3],
+    shake128x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], KYBER_SYMBYTES+2);
+    shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3],
                              GEN_MATRIX_NBLOCKS, &state);
 
-    ctr0 = rej_uniform_avx(a[i].vec[0].coeffs, buf[0]);
-    ctr1 = rej_uniform_avx(a[i].vec[1].coeffs, buf[1]);
-    ctr2 = rej_uniform_avx(a[i].vec[2].coeffs, buf[2]);
-    ctr3 = rej_uniform_avx(a[i].vec[3].coeffs, buf[3]);
+    ctr0 = rej_uniform_avx(a[i].vec[0].coeffs, buf.arr[0]);
+    ctr1 = rej_uniform_avx(a[i].vec[1].coeffs, buf.arr[1]);
+    ctr2 = rej_uniform_avx(a[i].vec[2].coeffs, buf.arr[2]);
+    ctr3 = rej_uniform_avx(a[i].vec[3].coeffs, buf.arr[3]);
 
     while(ctr0 < KYBER_N || ctr1 < KYBER_N || ctr2 < KYBER_N || ctr3 < KYBER_N) {
-      shake128x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 1, &state);
+      shake128x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 1, &state);
 
-      ctr0 += rej_uniform(a[i].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf[0],
+      ctr0 += rej_uniform(a[i].vec[0].coeffs + ctr0, KYBER_N - ctr0, buf.arr[0],
                           XOF_BLOCKBYTES);
-      ctr1 += rej_uniform(a[i].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf[1],
+      ctr1 += rej_uniform(a[i].vec[1].coeffs + ctr1, KYBER_N - ctr1, buf.arr[1],
                           XOF_BLOCKBYTES);
-      ctr2 += rej_uniform(a[i].vec[2].coeffs + ctr2, KYBER_N - ctr2, buf[2],
+      ctr2 += rej_uniform(a[i].vec[2].coeffs + ctr2, KYBER_N - ctr2, buf.arr[2],
                           XOF_BLOCKBYTES);
-      ctr3 += rej_uniform(a[i].vec[3].coeffs + ctr3, KYBER_N - ctr3, buf[3],
+      ctr3 += rej_uniform(a[i].vec[3].coeffs + ctr3, KYBER_N - ctr3, buf.arr[3],
                           XOF_BLOCKBYTES);
     }
 
@@ -485,35 +482,32 @@
                     uint8_t sk[KYBER_INDCPA_SECRETKEYBYTES])
 {
   unsigned int i;
-  __attribute__((aligned(32)))
-  uint8_t buf[2*KYBER_SYMBYTES];
-  const uint8_t *publicseed = buf;
-  const uint8_t *noiseseed = buf+KYBER_SYMBYTES;
+  ALIGN32_ARRAY(uint8_t, 2 * KYBER_SYMBYTES) buf;
+  const uint8_t *publicseed = buf.arr;
+  const uint8_t *noiseseed = buf.arr+KYBER_SYMBYTES;
   polyvec a[KYBER_K], e, pkpv, skpv;
 
-  randombytes(buf, KYBER_SYMBYTES);
-  hash_g(buf, buf, KYBER_SYMBYTES);
+  randombytes(buf.arr, KYBER_SYMBYTES);
+  hash_g(buf.arr, buf.arr, KYBER_SYMBYTES);
 
   gen_a(a, publicseed);
 
 #ifdef KYBER_90S
-  __attribute__((aligned(16)))
-  uint64_t nonce = 0;
+  ALIGN16_TYPE(uint64_t) nonce = {.orig = 0};
   aes256ctr_ctx state;
-  __attribute__((aligned(32)))
-  uint8_t coins[128];
-  aes256ctr_init(&state, noiseseed, nonce++);
+  ALIGN32_ARRAY(uint8_t, 128) coins;
+  aes256ctr_init(&state, noiseseed, nonce.orig++);
   for(i=0;i<KYBER_K;i++) {
-    aes256ctr_squeezeblocks(coins, 2, &state);
-    state.n = _mm_loadl_epi64((__m128i *)&nonce);
-    nonce++;
-    cbd(&skpv.vec[i], coins);
+    aes256ctr_squeezeblocks(coins.arr, 2, &state);
+    state.n = _mm_loadl_epi64(&nonce.vec);
+    nonce.orig++;
+    cbd(&skpv.vec[i], coins.arr);
   }
   for(i=0;i<KYBER_K;i++) {
-    aes256ctr_squeezeblocks(coins, 2, &state);
-    state.n = _mm_loadl_epi64((__m128i *)&nonce);
-    nonce++;
-    cbd(&e.vec[i], coins);
+    aes256ctr_squeezeblocks(coins.arr, 2, &state);
+    state.n = _mm_loadl_epi64(&nonce.vec);
+    nonce.orig++;
+    cbd(&e.vec[i], coins.arr);
   }
 #else
 #if KYBER_K == 2
@@ -571,38 +565,35 @@
                 const uint8_t coins[KYBER_SYMBYTES])
 {
   unsigned int i;
-  __attribute__((aligned(32)))
-  uint8_t seed[KYBER_SYMBYTES];
+  ALIGN32_ARRAY(uint8_t, KYBER_SYMBYTES) seed;
   polyvec sp, pkpv, ep, at[KYBER_K], bp;
   poly v, k, epp;
 
-  unpack_pk(&pkpv, seed, pk);
+  unpack_pk(&pkpv, seed.arr, pk);
   poly_frommsg(&k, m);
-  gen_at(at, seed);
+  gen_at(at, seed.arr);
 
 #ifdef KYBER_90S
-  __attribute__((aligned(16)))
-  uint64_t nonce = 0;
+  ALIGN16_TYPE(uint64_t) nonce = {.orig = 0};
   aes256ctr_ctx state;
-  __attribute__((aligned(32)))
-  uint8_t buf[128];
-  aes256ctr_init(&state, coins, nonce++);
+  ALIGN32_ARRAY(uint8_t, 128) buf;
+  aes256ctr_init(&state, coins, nonce.orig++);
   for(i=0;i<KYBER_K;i++) {
-    aes256ctr_squeezeblocks(buf, 2, &state);
-    state.n = _mm_loadl_epi64((__m128i *)&nonce);
-    nonce++;
-    cbd(&sp.vec[i], buf);
+    aes256ctr_squeezeblocks(buf.arr, 2, &state);
+    state.n = _mm_loadl_epi64(&nonce.vec);
+    nonce.orig++;
+    cbd(&sp.vec[i], buf.arr);
   }
   for(i=0;i<KYBER_K;i++) {
-    aes256ctr_squeezeblocks(buf, 2, &state);
-    state.n = _mm_loadl_epi64((__m128i *)&nonce);
-    nonce++;
-    cbd(&ep.vec[i], buf);
-  }
-  aes256ctr_squeezeblocks(buf, 2, &state);
-  state.n = _mm_loadl_epi64((__m128i *)&nonce);
-  nonce++;
-  cbd(&epp, buf);
+    aes256ctr_squeezeblocks(buf.arr, 2, &state);
+    state.n = _mm_loadl_epi64(&nonce.vec);
+    nonce.orig++;
+    cbd(&ep.vec[i], buf.arr);
+  }
+  aes256ctr_squeezeblocks(buf.arr, 2, &state);
+  state.n = _mm_loadl_epi64(&nonce.vec);
+  nonce.orig++;
+  cbd(&epp, buf.arr);
 #else
 #if KYBER_K == 2
   poly_getnoise4x(sp.vec+0, sp.vec+1, ep.vec+0, ep.vec+1, coins,

