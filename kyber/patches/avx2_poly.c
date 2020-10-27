--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -1,5 +1,6 @@
 #include <stdint.h>
 #include <immintrin.h>
+#include "align.h"
 #include "params.h"
 #include "poly.h"
 #include "ntt.h"
@@ -133,7 +134,7 @@
 **************************************************/
 void poly_tobytes(uint8_t r[KYBER_POLYBYTES], poly *a)
 {
-  ntttobytes_avx(r, a->coeffs, qdata);
+  ntttobytes_avx(r, a->coeffs, & qdata);
 }
 
 /*************************************************
@@ -148,7 +149,7 @@
 **************************************************/
 void poly_frombytes(poly *r, const uint8_t a[KYBER_POLYBYTES])
 {
-  nttfrombytes_avx(r->coeffs, a, qdata);
+  nttfrombytes_avx(r->coeffs, a, & qdata);
 }
 
 /*************************************************
@@ -162,16 +163,13 @@
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
@@ -193,10 +191,10 @@
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
@@ -256,10 +254,9 @@
 **************************************************/
 void poly_getnoise(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint8_t nonce)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[KYBER_ETA*KYBER_N/4];
-  prf(buf, sizeof(buf), seed, nonce);
-  cbd(r, buf);
+  ALIGN32_ARRAY(uint8_t, KYBER_ETA * KYBER_N / 4) buf;
+  prf(buf.arr, sizeof(buf.arr), seed, nonce);
+  cbd(r, buf.arr);
 }
 
 #ifndef KYBER_90S
@@ -273,29 +270,28 @@
                      uint8_t nonce2,
                      uint8_t nonce3)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[4][160];
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
-  cbd(r0, buf[0]);
-  cbd(r1, buf[1]);
-  cbd(r2, buf[2]);
-  cbd(r3, buf[3]);
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
+  cbd(r0, buf.arr[0]);
+  cbd(r1, buf.arr[1]);
+  cbd(r2, buf.arr[2]);
+  cbd(r3, buf.arr[3]);
 }
 #endif
 
@@ -310,7 +306,7 @@
 **************************************************/
 void poly_ntt(poly *r)
 {
-  ntt_avx(r->coeffs, qdata);
+  ntt_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -324,12 +320,12 @@
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
@@ -343,7 +339,7 @@
 **************************************************/
 void poly_basemul_montgomery(poly *r, const poly *a, const poly *b)
 {
-  basemul_avx(r->coeffs, a->coeffs, b->coeffs, qdata);
+  basemul_avx(r->coeffs, a->coeffs, b->coeffs, & qdata);
 }
 
 /*************************************************
@@ -356,7 +352,7 @@
 **************************************************/
 void poly_tomont(poly *r)
 {
-  tomont_avx(r->coeffs, qdata);
+  tomont_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -369,7 +365,7 @@
 **************************************************/
 void poly_reduce(poly *r)
 {
-  reduce_avx(r->coeffs, qdata);
+  reduce_avx(r->coeffs, & qdata);
 }
 
 /*************************************************
@@ -383,7 +379,7 @@
 **************************************************/
 void poly_csubq(poly *r)
 {
-  csubq_avx(r->coeffs, qdata);
+  csubq_avx(r->coeffs, & qdata);
 }
 
 /*************************************************

