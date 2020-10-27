--- upstream/avx2/polyvec.c
+++ upstream-patched/avx2/polyvec.c
@@ -9,10 +9,11 @@
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
 static void poly_compress10(uint8_t r[320], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
+  uint32_t low;
   __m256i f0, f1, f2;
   __m128i t0, t1;
-  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
+  const __m256i v = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XV]);
   const __m256i v8 = _mm256_slli_epi16(v,3);
   const __m256i off = _mm256_set1_epi16(15);
   const __m256i shift1 = _mm256_set1_epi16(1 << 12);
@@ -42,13 +43,17 @@
     t1 = _mm256_extracti128_si256(f0,1);
     t0 = _mm_blend_epi16(t0,t1,0xE0);
     _mm_storeu_si128((__m128i *)&r[20*i+ 0],t0);
-    _mm_store_ss((float *)&r[20*i+16],_mm_castsi128_ps(t1));
+    _mm_store_ss((float *)&low,_mm_castsi128_ps(t1));
+    r[20*i+16] = (uint8_t)low;
+    r[20*i+17] = (uint8_t)(low>>0x08);
+    r[20*i+18] = (uint8_t)(low>>0x10);
+    r[20*i+19] = (uint8_t)(low>>0x18);
   }
 }
 
 static void poly_decompress10(poly * restrict r, const uint8_t a[320+12])
 {
-  unsigned int i;
+  size_t i;
   __m256i f;
   const __m256i q = _mm256_set1_epi32((KYBER_Q << 16) + 4*KYBER_Q);
   const __m256i shufbidx = _mm256_set_epi8(11,10,10, 9, 9, 8, 8, 7,
@@ -73,10 +78,10 @@
 #elif (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 352))
 static void poly_compress11(uint8_t r[352+2], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1, f2;
   __m128i t0, t1;
-  const __m256i v = _mm256_load_si256((__m256i *)&qdata[_16XV]);
+  const __m256i v = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XV]);
   const __m256i v8 = _mm256_slli_epi16(v,3);
   const __m256i off = _mm256_set1_epi16(36);
   const __m256i shift1 = _mm256_set1_epi16(1 << 13);
@@ -116,9 +121,9 @@
 
 static void poly_decompress11(poly * restrict r, const uint8_t a[352+10])
 {
-  unsigned int i;
+  size_t i;
   __m256i f;
-  const __m256i q = _mm256_load_si256((__m256i *)&qdata[_16XQ]);
+  const __m256i q = _mm256_load_si256((__m256i *)&qdata.as_arr[_16XQ]);
   const __m256i shufbidx = _mm256_set_epi8(13,12,12,11,10, 9, 9, 8,
                                             8, 7, 6, 5, 5, 4, 4, 3,
                                            10, 9, 9, 8, 7, 6, 6, 5,
@@ -156,7 +161,7 @@
 void polyvec_compress(uint8_t r[KYBER_POLYVECCOMPRESSEDBYTES+2],
                       polyvec * restrict a)
 {
-  unsigned int i;
+  size_t i;
 
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
   for(i=0;i<KYBER_K;i++)
@@ -180,7 +185,7 @@
 void polyvec_decompress(polyvec * restrict r,
                         const uint8_t a[KYBER_POLYVECCOMPRESSEDBYTES+12])
 {
-  unsigned int i;
+  size_t i;
 
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
   for(i=0;i<KYBER_K;i++)
@@ -202,9 +207,10 @@
 **************************************************/
 void polyvec_tobytes(uint8_t r[KYBER_POLYVECBYTES], polyvec *a)
 {
-  unsigned int i;
-  for(i=0;i<KYBER_K;i++)
+  size_t i;
+  for(i=0;i<KYBER_K;i++) {
     poly_tobytes(r+i*KYBER_POLYBYTES, &a->vec[i]);
+  }
 }
 
 /*************************************************
@@ -219,9 +225,10 @@
 **************************************************/
 void polyvec_frombytes(polyvec *r, const uint8_t a[KYBER_POLYVECBYTES])
 {
-  unsigned int i;
-  for(i=0;i<KYBER_K;i++)
+  size_t i;
+  for(i=0;i<KYBER_K;i++) {
     poly_frombytes(&r->vec[i], a+i*KYBER_POLYBYTES);
+  }
 }
 
 /*************************************************
@@ -233,9 +240,10 @@
 **************************************************/
 void polyvec_ntt(polyvec *r)
 {
-  unsigned int i;
-  for(i=0;i<KYBER_K;i++)
+  size_t i;
+  for(i=0;i<KYBER_K;i++) {
     poly_ntt(&r->vec[i]);
+  }
 }
 
 /*************************************************
@@ -248,9 +256,10 @@
 **************************************************/
 void polyvec_invntt_tomont(polyvec *r)
 {
-  unsigned int i;
-  for(i=0;i<KYBER_K;i++)
+  size_t i;
+  for(i=0;i<KYBER_K;i++) {
     poly_invntt_tomont(&r->vec[i]);
+  }
 }
 
 /*************************************************
@@ -267,7 +276,7 @@
                                       const polyvec *a,
                                       const polyvec *b)
 {
-  unsigned int i;
+  size_t i;
   poly tmp;
 
   poly_basemul_montgomery(r,&a->vec[0],&b->vec[0]);
@@ -288,7 +297,7 @@
 **************************************************/
 void polyvec_reduce(polyvec *r)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_reduce(&r->vec[i]);
 }
@@ -304,7 +313,7 @@
 **************************************************/
 void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_add(&r->vec[i], &a->vec[i], &b->vec[i]);
 }

