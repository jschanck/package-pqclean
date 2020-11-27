--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -171,7 +171,8 @@
 #elif (KYBER_POLYCOMPRESSEDBYTES == 160)
 void poly_compress(uint8_t r[160], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
+  uint32_t low;
   __m256i f0, f1;
   __m128i t0, t1;
   const __m256i v = _mm256_load_si256(&qdata.vec[_16XV/16]);
@@ -202,13 +203,18 @@
     t1 = _mm256_extracti128_si256(f0,1);
     t0 = _mm_blendv_epi8(t0,t1,_mm256_castsi256_si128(shufbidx));
     _mm_storeu_si128((__m128i *)&r[20*i+ 0],t0);
-    _mm_store_ss((float *)&r[20*i+16],_mm_castsi128_ps(t1));
+    _mm_store_ss((float *)&low, _mm_castsi128_ps(t1));
+    r[20 * i + 16] = (uint8_t)low;
+    r[20 * i + 17] = (uint8_t)(low >> 0x08);
+    r[20 * i + 18] = (uint8_t)(low >> 0x10);
+    r[20 * i + 19] = (uint8_t)(low >> 0x18);
   }
 }
 
 void poly_decompress(poly * restrict r, const uint8_t a[160])
 {
   unsigned int i;
+  int16_t h;
   __m128i t;
   __m256i f;
   const __m256i q = _mm256_load_si256(&qdata.vec[_16XQ/16]);
@@ -221,7 +227,8 @@
 
   for(i=0;i<KYBER_N/16;i++) {
     t = _mm_loadl_epi64((__m128i *)&a[10*i+0]);
-    t = _mm_insert_epi16(t,*(int16_t *)&a[10*i+8],4);
+    h = (a[10*i+9] << 8) + a[10*i+8];
+    t = _mm_insert_epi16(t,h,4);
     f = _mm256_broadcastsi128_si256(t);
     f = _mm256_shuffle_epi8(f,shufbidx);
     f = _mm256_and_si256(f,mask);
@@ -286,7 +293,7 @@
   const __m256i hqs = _mm256_set1_epi16((KYBER_Q+1)/2);
 
 #define FROMMSG64(i)						\
-  g3 = _mm256_shuffle_epi32(f,0x55*i);				\
+  g3 = _mm256_shuffle_epi32(f,0x55*(i));				\
   g3 = _mm256_sllv_epi32(g3,shift);				\
   g3 = _mm256_shuffle_epi8(g3,idx);				\
   g0 = _mm256_slli_epi16(g3,12);				\
@@ -308,10 +315,10 @@
   g2 = _mm256_permute2x128_si256(h0,h1,0x31);			\
   g1 = _mm256_permute2x128_si256(h2,h3,0x20);			\
   g3 = _mm256_permute2x128_si256(h2,h3,0x31);			\
-  _mm256_store_si256(&r->vec[0+2*i+0],g0);	\
-  _mm256_store_si256(&r->vec[0+2*i+1],g1);	\
-  _mm256_store_si256(&r->vec[8+2*i+0],g2);	\
-  _mm256_store_si256(&r->vec[8+2*i+1],g3)
+  _mm256_store_si256(&r->vec[0+2*(i)+0],g0);	\
+  _mm256_store_si256(&r->vec[0+2*(i)+1],g1);	\
+  _mm256_store_si256(&r->vec[8+2*(i)+0],g2);	\
+  _mm256_store_si256(&r->vec[8+2*(i)+1],g3)
 
   f = _mm256_loadu_si256((__m256i *)msg);
   FROMMSG64(0);

