--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -1,5 +1,6 @@
 #include <stdint.h>
 #include <immintrin.h>
+#include "align.h"
 #include "params.h"
 #include "poly.h"
 #include "ntt.h"
@@ -20,10 +21,10 @@
 #if (KYBER_POLYCOMPRESSEDBYTES == 96)
 void poly_compress(uint8_t r[96], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1, f2, f3;
   __m128i t0, t1;
-  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
+  const __m256i v = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XV]);
   const __m256i shift1 = _mm256_set1_epi16(1 << 8);
   const __m256i mask = _mm256_set1_epi16(7);
   const __m256i shift2 = _mm256_set1_epi16((8 << 8) + 1);
@@ -70,9 +71,9 @@
 
 void poly_decompress(poly * restrict r, const uint8_t a[96+2])
 {
-  unsigned int i;
+  size_t i;
   __m256i f;
-  const __m256i q = _mm256_load_si256((__m256i *)&qdata[_16XQ]);
+  const __m256i q = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XQ]);
   const __m256i shufbidx = _mm256_set_epi8(5,5,5,5,5,4,4,4,4,4,4,3,3,3,3,3,
                                            2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0);
   const __m256i mask = _mm256_set_epi16(224,28,896,112,14,448,56,7,
@@ -94,9 +95,9 @@
 
 void poly_compress(uint8_t r[128], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1, f2, f3;
-  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
+  const __m256i v = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XV]);
   const __m256i shift1 = _mm256_set1_epi16(1 << 9);
   const __m256i mask = _mm256_set1_epi16(15);
   const __m256i shift2 = _mm256_set1_epi16((16 << 8) + 1);
@@ -131,9 +132,9 @@
 
 void poly_decompress(poly * restrict r, const uint8_t a[128])
 {
-  unsigned int i;
+  size_t i;
   __m256i f;
-  const __m256i q = _mm256_load_si256((__m256i *)&qdata[_16XQ]);
+  const __m256i q = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XQ]);
   const __m256i shufbidx = _mm256_set_epi8(7,7,7,7,6,6,6,6,5,5,5,5,4,4,4,4,
                                            3,3,3,3,2,2,2,2,1,1,1,1,0,0,0,0);
   const __m256i mask = _mm256_set1_epi32(0x00F0000F);
@@ -153,10 +154,11 @@
 
 void poly_compress(uint8_t r[160], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
+  uint32_t low;
   __m256i f0, f1;
   __m128i t0, t1;
-  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
+  const __m256i v = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XV]);
   const __m256i shift1 = _mm256_set1_epi16(1 << 10);
   const __m256i mask = _mm256_set1_epi16(31);
   const __m256i shift2 = _mm256_set1_epi16((32 << 8) + 1);
@@ -184,15 +186,19 @@
     t1 = _mm256_extracti128_si256(f0,1);
     t0 = _mm_blendv_epi8(t0,t1,_mm256_castsi256_si128(shufbidx));
     _mm_storeu_si128((__m128i *)&r[20*i+ 0],t0);
-    _mm_store_ss((float *)&r[20*i+16],_mm_castsi128_ps(t1));
+    _mm_store_ss((float *)&low,_mm_castsi128_ps(t1));
+    r[20*i+16] = (uint8_t)low;
+    r[20*i+17] = (uint8_t)(low>>0x08);
+    r[20*i+18] = (uint8_t)(low>>0x10);
+    r[20*i+19] = (uint8_t)(low>>0x18);
   }
 }
 
 void poly_decompress(poly * restrict r, const uint8_t a[160+6])
 {
-  unsigned int i;
+  size_t i;
   __m256i f;
-  const __m256i q = _mm256_load_si256((__m256i *)&qdata[_16XQ]);
+  const __m256i q = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XQ]);
   const __m256i shufbidx = _mm256_set_epi8(9,9,9,8,8,8,8,7,7,6,6,6,6,5,5,5,
                                            4,4,4,3,3,3,3,2,2,1,1,1,1,0,0,0);
   const __m256i mask = _mm256_set_epi16(248,1984,62,496,3968,124,992,31,
@@ -223,7 +229,7 @@
 **************************************************/
 void poly_tobytes(uint8_t r[KYBER_POLYBYTES], poly *a)
 {
-  ntttobytes_avx(r, a->coeffs, qdata);
+  ntttobytes_avx(r, a->coeffs, & qdata);
 }
 
 /*************************************************
@@ -238,7 +244,7 @@
 **************************************************/
 void poly_frombytes(poly *r, const uint8_t a[KYBER_POLYBYTES])
 {
-  nttfrombytes_avx(r->coeffs, a, qdata);
+  nttfrombytes_avx(r->coeffs, a, & qdata);
 }
 
 /*************************************************
@@ -252,16 +258,13 @@
 void poly_frommsg(poly * restrict r,
                   const uint8_t msg[KYBER_INDCPA_MSGBYTES])
 {
-#if (KYBER_INDCPA_MSGBYTES != 32)
-#error "KYBER_INDCPA_MSGBYTES must be equal to 32!"
-#endif
   __m256i f, g0, g1, g2, g3, h0, h1, h2, h3;
   const __m256i shift = _mm256_broadcastsi128_si256(_mm_set_epi32(0,1,2,3));
   const __m256i idx = _mm256_broadcastsi128_si256(_mm_set_epi8(15,14,11,10,7,6,3,2,13,12,9,8,5,4,1,0));
   const __m256i hqs = _mm256_set1_epi16((KYBER_Q+1)/2);
 
 #define FROMMSG64(i)						\
-  g3 = _mm256_shuffle_epi32(f,0x55*i);				\
+  g3 = _mm256_shuffle_epi32(f,0x55*(i));				\
   g3 = _mm256_sllv_epi32(g3,shift);				\
   g3 = _mm256_shuffle_epi8(g3,idx);				\
   g0 = _mm256_slli_epi16(g3,12);				\
@@ -283,10 +286,10 @@
   g2 = _mm256_permute2x128_si256(h0,h1,0x31);			\
   g1 = _mm256_permute2x128_si256(h2,h3,0x20);			\
   g3 = _mm256_permute2x128_si256(h2,h3,0x31);			\
-  _mm256_store_si256((__m256i *)&r->coeffs[  0+32*i+ 0],g0);	\
-  _mm256_store_si256((__m256i *)&r->coeffs[  0+32*i+16],g1);	\
-  _mm256_store_si256((__m256i *)&r->coeffs[128+32*i+ 0],g2);	\
-  _mm256_store_si256((__m256i *)&r->coeffs[128+32*i+16],g3)
+  _mm256_store_si256((__m256i *)&r->coeffs[  0+32*(i)+ 0],g0);	\
+  _mm256_store_si256((__m256i *)&r->coeffs[  0+32*(i)+16],g1);	\
+  _mm256_store_si256((__m256i *)&r->coeffs[128+32*(i)+ 0],g2);	\
+  _mm256_store_si256((__m256i *)&r->coeffs[128+32*(i)+16],g3)
 
   f = _mm256_load_si256((__m256i *)msg);
   FROMMSG64(0);
@@ -305,7 +308,7 @@
 **************************************************/
 void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
   uint32_t small;
   __m256i f0, f1, g0, g1;
   const __m256i hqs = _mm256_set1_epi16((KYBER_Q - 1)/2);
@@ -346,10 +349,9 @@
 **************************************************/
 void poly_getnoise_eta2(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint8_t nonce)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[KYBER_ETA2*KYBER_N/4];
-  prf(buf, sizeof(buf), seed, nonce);
-  cbd_eta2(r, buf);
+  ALIGN32_ARRAY(uint8_t, KYBER_ETA2 * KYBER_N / 4) buf;
+  prf(buf.arr, sizeof(buf.arr), seed, nonce);
+  cbd_eta2(r, buf.arr);
 }
 
 
@@ -364,29 +366,28 @@
                      uint8_t nonce2,
                      uint8_t nonce3)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[4][160]; /* 160 instead of SHAKE256_RATE for better alignment */
+  ALIGN32_ARRAY_2D(uint8_t, 4, 160) buf;
   __m256i f;
   keccakx4_state state;
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
-
-  buf[0][32] = nonce0;
-  buf[1][32] = nonce1;
-  buf[2][32] = nonce2;
-  buf[3][32] = nonce3;
-
-  shake256x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], 33);
-  shake256x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 1, &state);
-
-  cbd_eta2(r0, buf[0]);
-  cbd_eta2(r1, buf[1]);
-  cbd_eta2(r2, buf[2]);
-  cbd_eta2(r3, buf[3]);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
+
+  buf.arr[0][32] = nonce0;
+  buf.arr[1][32] = nonce1;
+  buf.arr[2][32] = nonce2;
+  buf.arr[3][32] = nonce3;
+
+  shake256x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 33);
+  shake256x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 1, &state);
+
+  cbd_eta2(r0, buf.arr[0]);
+  cbd_eta2(r1, buf.arr[1]);
+  cbd_eta2(r2, buf.arr[2]);
+  cbd_eta2(r3, buf.arr[3]);
 }
 
 #if KYBER_ETA1 == 3
@@ -400,29 +401,29 @@
                      uint8_t nonce2,
                      uint8_t nonce3)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[4][288]; /* 288 instead of 2*SHAKE256_RATE for better alignment, also 2 extra bytes needed in cbd3 */
+  /* 288 instead of 2*SHAKE256_RATE for better alignment, also 2 extra bytes needed in cbd3 */
+  ALIGN32_ARRAY_2D(uint8_t, 4, 288) buf;
   __m256i f;
   keccakx4_state state;
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
-
-  buf[0][32] = nonce0;
-  buf[1][32] = nonce1;
-  buf[2][32] = nonce2;
-  buf[3][32] = nonce3;
-
-  shake256x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], 33);
-  shake256x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 2, &state);
-
-  cbd_eta1(r0, buf[0]);
-  cbd_eta1(r1, buf[1]);
-  cbd_eta1(r2, buf[2]);
-  cbd_eta1(r3, buf[3]);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
+
+  buf.arr[0][32] = nonce0;
+  buf.arr[1][32] = nonce1;
+  buf.arr[2][32] = nonce2;
+  buf.arr[3][32] = nonce3;
+
+  shake256x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 33);
+  shake256x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 2, &state);
+
+  cbd_eta1(r0, buf.arr[0]);
+  cbd_eta1(r1, buf.arr[1]);
+  cbd_eta1(r2, buf.arr[2]);
+  cbd_eta1(r3, buf.arr[3]);
 }
 
 void poly_getnoise_eta1122_4x(poly *r0,
@@ -435,29 +436,29 @@
                      uint8_t nonce2,
                      uint8_t nonce3)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[4][288]; /* 288 instead of 2*SHAKE256_RATE for better alignment, also 2 extra bytes needed in cbd3 */
+  /* 288 instead of 2*SHAKE256_RATE for better alignment, also 2 extra bytes needed in cbd3 */
+  ALIGN32_ARRAY_2D(uint8_t, 4, 288) buf;
   __m256i f;
   keccakx4_state state;
 
   f = _mm256_load_si256((__m256i *)seed);
-  _mm256_store_si256((__m256i *)buf[0], f);
-  _mm256_store_si256((__m256i *)buf[1], f);
-  _mm256_store_si256((__m256i *)buf[2], f);
-  _mm256_store_si256((__m256i *)buf[3], f);
-
-  buf[0][32] = nonce0;
-  buf[1][32] = nonce1;
-  buf[2][32] = nonce2;
-  buf[3][32] = nonce3;
-
-  shake256x4_absorb(&state, buf[0], buf[1], buf[2], buf[3], 33);
-  shake256x4_squeezeblocks(buf[0], buf[1], buf[2], buf[3], 2, &state);
-
-  cbd_eta1(r0, buf[0]);
-  cbd_eta1(r1, buf[1]);
-  cbd_eta2(r2, buf[2]);
-  cbd_eta2(r3, buf[3]);
+  _mm256_store_si256((__m256i *)buf.arr[0], f);
+  _mm256_store_si256((__m256i *)buf.arr[1], f);
+  _mm256_store_si256((__m256i *)buf.arr[2], f);
+  _mm256_store_si256((__m256i *)buf.arr[3], f);
+
+  buf.arr[0][32] = nonce0;
+  buf.arr[1][32] = nonce1;
+  buf.arr[2][32] = nonce2;
+  buf.arr[3][32] = nonce3;
+
+  shake256x4_absorb(&state, buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 33);
+  shake256x4_squeezeblocks(buf.arr[0], buf.arr[1], buf.arr[2], buf.arr[3], 2, &state);
+
+  cbd_eta1(r0, buf.arr[0]);
+  cbd_eta1(r1, buf.arr[1]);
+  cbd_eta2(r2, buf.arr[2]);
+  cbd_eta2(r3, buf.arr[3]);
 }
 #endif
 #endif
@@ -473,7 +474,7 @@
 **************************************************/
 void poly_ntt(poly *r)
 {
-  ntt_avx(r->coeffs, qdata);
+  ntt_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -487,12 +488,12 @@
 **************************************************/
 void poly_invntt_tomont(poly *r)
 {
-  invntt_avx(r->coeffs, qdata);
+  invntt_avx(r->coeffs, & qdata);
 }
 
 void poly_nttunpack(poly *r)
 {
-  nttunpack_avx(r->coeffs, qdata);
+  nttunpack_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -506,7 +507,7 @@
 **************************************************/
 void poly_basemul_montgomery(poly *r, const poly *a, const poly *b)
 {
-  basemul_avx(r->coeffs, a->coeffs, b->coeffs, qdata);
+  basemul_avx(r->coeffs, a->coeffs, b->coeffs, & qdata);
 }
 
 /*************************************************
@@ -519,7 +520,7 @@
 **************************************************/
 void poly_tomont(poly *r)
 {
-  tomont_avx(r->coeffs, qdata);
+  tomont_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -532,7 +533,7 @@
 **************************************************/
 void poly_reduce(poly *r)
 {
-  reduce_avx(r->coeffs, qdata);
+  reduce_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -546,7 +547,7 @@
 **************************************************/
 void poly_add(poly *r, const poly *a, const poly *b)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1;
 
   for(i=0;i<KYBER_N;i+=16) {
@@ -568,7 +569,7 @@
 **************************************************/
 void poly_sub(poly *r, const poly *a, const poly *b)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1;
 
   for(i=0;i<KYBER_N;i+=16) {

