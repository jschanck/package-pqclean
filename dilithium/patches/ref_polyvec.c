--- upstream/ref/polyvec.c
+++ upstream-patched/ref/polyvec.c
@@ -17,9 +17,11 @@
 void polyvec_matrix_expand(polyvecl mat[K], const uint8_t rho[SEEDBYTES]) {
   unsigned int i, j;
 
-  for(i = 0; i < K; ++i)
-    for(j = 0; j < L; ++j)
-      poly_uniform(&mat[i].vec[j], rho, (i << 8) + j);
+  for(i = 0; i < K; ++i) {
+    for(j = 0; j < L; ++j) {
+      poly_uniform(&mat[i].vec[j], rho, (uint16_t) ((i << 8) + j));
+    }
+  }
 }
 
 void polyvec_matrix_pointwise_montgomery(polyveck *t, const polyvecl mat[K], const polyvecl *v) {
@@ -44,7 +46,7 @@
   unsigned int i;
 
   for(i = 0; i < L; ++i)
-    poly_uniform_gamma1(&v->vec[i], seed, L*nonce + i);
+    poly_uniform_gamma1(&v->vec[i], seed, (uint16_t) (L*nonce + i));
 }
 
 void polyvecl_reduce(polyvecl *v) {
@@ -155,9 +157,10 @@
 int polyvecl_chknorm(const polyvecl *v, int32_t bound)  {
   unsigned int i;
 
-  for(i = 0; i < L; ++i)
+  for(i = 0; i < L; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }
@@ -322,9 +325,10 @@
 int polyveck_chknorm(const polyveck *v, int32_t bound) {
   unsigned int i;
 
-  for(i = 0; i < K; ++i)
+  for(i = 0; i < K; ++i) {
     if(poly_chknorm(&v->vec[i], bound))
       return 1;
+  }
 
   return 0;
 }

