--- upstream/avx2/polyvec.c
+++ upstream-patched/avx2/polyvec.c
@@ -8,6 +8,8 @@
 #include "aes256ctr.h"
 #endif
 
+#define UNUSED(x) (void)x
+
 /*************************************************
 * Name:        expand_mat
 *
@@ -45,7 +47,8 @@
   polyvec_matrix_expand_row3(&mat[3], NULL, rho);
 }
 
-void polyvec_matrix_expand_row0(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row0(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 0, 1, 2, 3);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -53,7 +56,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row1(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row1(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 256, 257, 258, 259);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -61,7 +65,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row2(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row2(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 512, 513, 514, 515);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -69,7 +74,8 @@
   poly_nttunpack(&rowa->vec[3]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[0], &rowa->vec[1], &rowa->vec[2], &rowa->vec[3], rho, 768, 769, 770, 771);
   poly_nttunpack(&rowa->vec[0]);
   poly_nttunpack(&rowa->vec[1]);
@@ -117,7 +123,8 @@
   poly_nttunpack(&rowb->vec[0]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[1], &rowa->vec[2], &rowa->vec[3], &rowa->vec[4], rho, 769, 770, 771, 772);
   poly_nttunpack(&rowa->vec[1]);
   poly_nttunpack(&rowa->vec[2]);
@@ -195,7 +202,8 @@
   poly_nttunpack(&rowb->vec[2]);
 }
 
-void polyvec_matrix_expand_row3(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row3(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[3], &rowa->vec[4], &rowa->vec[5], &rowa->vec[6], rho, 771, 772, 773, 774);
   poly_nttunpack(&rowa->vec[3]);
   poly_nttunpack(&rowa->vec[4]);
@@ -242,7 +250,8 @@
   poly_nttunpack(&rowb->vec[2]);
 }
 
-void polyvec_matrix_expand_row7(polyvecl *rowa, __attribute__((unused)) polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+void polyvec_matrix_expand_row7(polyvecl *rowa, polyvecl *rowb, const uint8_t rho[SEEDBYTES]) {
+  UNUSED(rowb);
   poly_uniform_4x(&rowa->vec[3], &rowa->vec[4], &rowa->vec[5], &rowa->vec[6], rho, 1795, 1796, 1797, 1798);
   poly_nttunpack(&rowa->vec[3]);
   poly_nttunpack(&rowa->vec[4]);
@@ -377,9 +386,10 @@
 int polyvecl_chknorm(const polyvecl *v, int32_t bound)  {
   unsigned int i;
 
-  for(i = 0; i < L; ++i)
+  for(i = 0; i < L; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }
@@ -543,9 +553,10 @@
 int polyveck_chknorm(const polyveck *v, int32_t bound) {
   unsigned int i;
 
-  for(i = 0; i < K; ++i)
+  for(i = 0; i < K; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }

