--- upstream/avx2/polyvec.c
+++ upstream-patched/avx2/polyvec.c
@@ -17,7 +17,7 @@
 void polyvec_compress(uint8_t r[KYBER_POLYVECCOMPRESSEDBYTES],
                       polyvec * restrict a)
 {
-  unsigned int i,j,k;
+  size_t i,j,k;
 
   polyvec_csubq(a);
 
@@ -25,9 +25,10 @@
   uint16_t t[8];
   for(i=0;i<KYBER_K;i++) {
     for(j=0;j<KYBER_N/8;j++) {
-      for(k=0;k<8;k++)
+      for(k=0;k<8;k++) {
         t[k] = ((((uint32_t)a->vec[i].coeffs[8*j+k] << 11) + KYBER_Q/2)
                 /KYBER_Q) & 0x7ff;
+      }
 
       r[ 0] = (t[0] >>  0);
       r[ 1] = (t[0] >>  8) | (t[1] << 3);
@@ -47,9 +48,10 @@
   uint16_t t[4];
   for(i=0;i<KYBER_K;i++) {
     for(j=0;j<KYBER_N/4;j++) {
-      for(k=0;k<4;k++)
+      for(k=0;k<4;k++) {
         t[k] = ((((uint32_t)a->vec[i].coeffs[4*j+k] << 10) + KYBER_Q/2)
                 / KYBER_Q) & 0x3ff;
+      }
 
       r[0] = (t[0] >> 0);
       r[1] = (t[0] >> 8) | (t[1] << 2);
@@ -77,7 +79,7 @@
 void polyvec_decompress(polyvec * restrict r,
                         const uint8_t a[KYBER_POLYVECCOMPRESSEDBYTES])
 {
-  unsigned int i,j,k;
+  size_t i,j,k;
 
 #if (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 352))
   uint16_t t[8];
@@ -93,8 +95,9 @@
       t[7] = (a[9] >> 5) | ((uint16_t)a[10] << 3);
       a += 11;
 
-      for(k=0;k<8;k++)
+      for(k=0;k<8;k++) {
         r->vec[i].coeffs[8*j+k] = ((uint32_t)(t[k] & 0x7FF)*KYBER_Q + 1024) >> 11;
+      }
     }
   }
 #elif (KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K * 320))
@@ -107,8 +110,9 @@
       t[3] = (a[3] >> 6) | ((uint16_t)a[4] << 2);
       a += 5;
 
-      for(k=0;k<4;k++)
+      for(k=0;k<4;k++) {
         r->vec[i].coeffs[4*j+k] = ((uint32_t)(t[k] & 0x3FF)*KYBER_Q + 512) >> 10;
+      }
     }
   }
 #else
@@ -127,9 +131,10 @@
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
@@ -144,9 +149,10 @@
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
@@ -158,9 +164,10 @@
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
@@ -173,9 +180,10 @@
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
@@ -192,7 +200,7 @@
                                       const polyvec *a,
                                       const polyvec *b)
 {
-  basemul_acc_avx(r->coeffs, a->vec->coeffs, b->vec->coeffs, qdata);
+  basemul_acc_avx(r->coeffs, a->vec->coeffs, b->vec->coeffs, & qdata);
 }
 
 /*************************************************
@@ -206,7 +214,7 @@
 **************************************************/
 void polyvec_reduce(polyvec *r)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_reduce(&r->vec[i]);
 }
@@ -223,7 +231,7 @@
 **************************************************/
 void polyvec_csubq(polyvec *r)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_csubq(&r->vec[i]);
 }
@@ -239,7 +247,7 @@
 **************************************************/
 void polyvec_add(polyvec *r, const polyvec *a, const polyvec *b)
 {
-  unsigned int i;
+  size_t i;
   for(i=0;i<KYBER_K;i++)
     poly_add(&r->vec[i], &a->vec[i], &b->vec[i]);
 }

