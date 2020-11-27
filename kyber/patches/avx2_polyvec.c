--- upstream/avx2/polyvec.c
+++ upstream-patched/avx2/polyvec.c
@@ -9,7 +9,8 @@
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
 static void poly_compress10(uint8_t r[320], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
+  uint32_t low;
   __m256i f0, f1, f2;
   __m128i t0, t1;
   const __m256i v = _mm256_load_si256(&qdata.vec[_16XV/16]);
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
@@ -155,7 +160,7 @@
 **************************************************/
 void polyvec_compress(uint8_t r[KYBER_POLYVECCOMPRESSEDBYTES+2], polyvec *a)
 {
-  unsigned int i;
+  size_t i;
 
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
   for(i=0;i<KYBER_K;i++)
@@ -178,7 +183,7 @@
 **************************************************/
 void polyvec_decompress(polyvec *r, const uint8_t a[KYBER_POLYVECCOMPRESSEDBYTES+12])
 {
-  unsigned int i;
+  size_t i;
 
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
   for(i=0;i<KYBER_K;i++)
@@ -200,9 +205,10 @@
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
@@ -217,9 +223,10 @@
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
@@ -231,9 +238,10 @@
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
@@ -246,9 +254,10 @@
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
@@ -263,7 +272,7 @@
 **************************************************/
 void polyvec_basemul_acc_montgomery(poly *r, const polyvec *a, const polyvec *b)
 {
-  unsigned int i;
+  size_t i;
   poly tmp;
 
   poly_basemul_montgomery(r,&a->vec[0],&b->vec[0]);
@@ -284,7 +293,7 @@
 **************************************************/
 void polyvec_reduce(polyvec *r)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_reduce(&r->vec[i]);
 }
@@ -300,7 +309,7 @@
 **************************************************/
 void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_add(&r->vec[i], &a->vec[i], &b->vec[i]);
 }

