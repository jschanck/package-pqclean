--- upstream/ref/poly.c
+++ upstream-patched/ref/poly.c
@@ -17,7 +17,7 @@
 **************************************************/
 void poly_compress(uint8_t r[KYBER_POLYCOMPRESSEDBYTES], const poly *a)
 {
-  unsigned int i,j;
+  size_t i,j;
   int16_t u;
   uint8_t t[8];
 
@@ -69,7 +69,7 @@
 **************************************************/
 void poly_decompress(poly *r, const uint8_t a[KYBER_POLYCOMPRESSEDBYTES])
 {
-  unsigned int i;
+  size_t i;
 
 #if (KYBER_POLYCOMPRESSEDBYTES == 128)
   for(i=0;i<KYBER_N/2;i++) {
@@ -78,7 +78,7 @@
     a += 1;
   }
 #elif (KYBER_POLYCOMPRESSEDBYTES == 160)
-  unsigned int j;
+  size_t j;
   uint8_t t[8];
   for(i=0;i<KYBER_N/8;i++) {
     t[0] = (a[0] >> 0);
@@ -110,7 +110,7 @@
 **************************************************/
 void poly_tobytes(uint8_t r[KYBER_POLYBYTES], const poly *a)
 {
-  unsigned int i;
+  size_t i;
   uint16_t t0, t1;
 
   for(i=0;i<KYBER_N/2;i++) {
@@ -119,9 +119,9 @@
     t0 += ((int16_t)t0 >> 15) & KYBER_Q;
     t1 = a->coeffs[2*i+1];
     t1 += ((int16_t)t1 >> 15) & KYBER_Q;
-    r[3*i+0] = (t0 >> 0);
-    r[3*i+1] = (t0 >> 8) | (t1 << 4);
-    r[3*i+2] = (t1 >> 4);
+    r[3*i+0] = (uint8_t)(t0 >> 0);
+    r[3*i+1] = (uint8_t)((t0 >> 8) | (t1 << 4));
+    r[3*i+2] = (uint8_t)(t1 >> 4);
   }
 }
 
@@ -137,7 +137,7 @@
 **************************************************/
 void poly_frombytes(poly *r, const uint8_t a[KYBER_POLYBYTES])
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_N/2;i++) {
     r->coeffs[2*i]   = ((a[3*i+0] >> 0) | ((uint16_t)a[3*i+1] << 8)) & 0xFFF;
     r->coeffs[2*i+1] = ((a[3*i+1] >> 4) | ((uint16_t)a[3*i+2] << 4)) & 0xFFF;
@@ -154,13 +154,9 @@
 **************************************************/
 void poly_frommsg(poly *r, const uint8_t msg[KYBER_INDCPA_MSGBYTES])
 {
-  unsigned int i,j;
+  size_t i,j;
   int16_t mask;
 
-#if (KYBER_INDCPA_MSGBYTES != KYBER_N/8)
-#error "KYBER_INDCPA_MSGBYTES must be equal to KYBER_N/8 bytes!"
-#endif
-
   for(i=0;i<KYBER_N/8;i++) {
     for(j=0;j<8;j++) {
       mask = -(int16_t)((msg[i] >> j)&1);
@@ -179,7 +175,7 @@
 **************************************************/
 void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], const poly *a)
 {
-  unsigned int i,j;
+  size_t i,j;
   uint16_t t;
 
   for(i=0;i<KYBER_N/8;i++) {
@@ -272,7 +268,7 @@
 **************************************************/
 void poly_basemul_montgomery(poly *r, const poly *a, const poly *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_N/4;i++) {
     basemul(&r->coeffs[4*i], &a->coeffs[4*i], &b->coeffs[4*i], zetas[64+i]);
     basemul(&r->coeffs[4*i+2], &a->coeffs[4*i+2], &b->coeffs[4*i+2], -zetas[64+i]);
@@ -289,7 +285,7 @@
 **************************************************/
 void poly_tomont(poly *r)
 {
-  unsigned int i;
+  size_t i;
   const int16_t f = (1ULL << 32) % KYBER_Q;
   for(i=0;i<KYBER_N;i++)
     r->coeffs[i] = montgomery_reduce((int32_t)r->coeffs[i]*f);
@@ -305,7 +301,7 @@
 **************************************************/
 void poly_reduce(poly *r)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_N;i++)
     r->coeffs[i] = barrett_reduce(r->coeffs[i]);
 }
@@ -321,7 +317,7 @@
 **************************************************/
 void poly_add(poly *r, const poly *a, const poly *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_N;i++)
     r->coeffs[i] = a->coeffs[i] + b->coeffs[i];
 }
@@ -337,7 +333,7 @@
 **************************************************/
 void poly_sub(poly *r, const poly *a, const poly *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_N;i++)
     r->coeffs[i] = a->coeffs[i] - b->coeffs[i];
 }

