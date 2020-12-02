--- upstream/avx2/poly.c
+++ upstream-patched/avx2/poly.c
@@ -172,7 +172,7 @@
 #elif (KYBER_POLYCOMPRESSEDBYTES == 160)
 void poly_compress(uint8_t r[160], const poly * restrict a)
 {
-  unsigned int i;
+  size_t i;
   __m256i f0, f1;
   __m128i t0, t1;
   const __m256i v = _mm256_load_si256(&qdata.vec[_16XV/16]);
@@ -289,7 +289,7 @@
   const __m256i hqs = _mm256_set1_epi16((KYBER_Q+1)/2);
 
 #define FROMMSG64(i)						\
-  g3 = _mm256_shuffle_epi32(f,0x55*i);				\
+  g3 = _mm256_shuffle_epi32(f,0x55*(i));				\
   g3 = _mm256_sllv_epi32(g3,shift);				\
   g3 = _mm256_shuffle_epi8(g3,idx);				\
   g0 = _mm256_slli_epi16(g3,12);				\
@@ -311,10 +311,10 @@
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

