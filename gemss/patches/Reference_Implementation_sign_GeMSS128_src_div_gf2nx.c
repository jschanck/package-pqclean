--- upstream/Reference_Implementation/sign/GeMSS128/src/div_gf2nx.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/div_gf2nx.c
@@ -120,8 +120,11 @@
         }
 
         leading_coef=A+da*NB_WORD_GFqn;
-        i=(db<<1)-da;
-        i=MAXI(0,(int)i);
+        i=0;
+        if(2*db > da)
+        {
+            i = 2*db - da;
+        }
         res=A+(da-db+i)*NB_WORD_GFqn;
 
         for(;i<db;++i)
@@ -274,7 +277,7 @@
  * @remark  This implementation is not in constant-time.
  */
 unsigned int PREFIX_NAME(div_r_HFE_gf2nx)(gf2nx poly, unsigned int dp,
-                                          const complete_sparse_monic_gf2nx F,
+                                          complete_sparse_monic_gf2nx F,
                                           cst_gf2n cst)
 {
     static_gf2n mul_coef[NB_WORD_GFqn];
@@ -343,7 +346,7 @@
  * @remark  Constant-time implementation when dp is not secret.
  */
 void PREFIX_NAME(div_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
-                                         const complete_sparse_monic_gf2nx F,
+                                         complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst)
 {
     static_gf2n mul_coef[NB_WORD_GFqn];
@@ -385,7 +388,7 @@
  * @remark  Constant-time implementation.
  */
 void PREFIX_NAME(div_r_HFE_cst_gf2nx)(gf2nx poly,
-                                      const complete_sparse_monic_gf2nx F,
+                                      complete_sparse_monic_gf2nx F,
                                       cst_gf2n cst)
 {
     static_gf2n mul_coef[NB_WORD_GFqn];
@@ -430,7 +433,7 @@
  * @remark  Constant-time implementation when dp is not secret.
  */
 void PREFIX_NAME(divsqr_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
-                                           const complete_sparse_monic_gf2nx F,
+                                           complete_sparse_monic_gf2nx F,
                                            cst_gf2n cst)
 {
     static_gf2n mul_coef[NB_WORD_GFqn];
@@ -489,7 +492,7 @@
  * @remark  Constant-time implementation.
  */
 void PREFIX_NAME(divsqr_r_HFE_cst_gf2nx)(gf2nx poly,
-                                         const complete_sparse_monic_gf2nx F,
+                                         complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst)
 {
     static_gf2n mul_coef[NB_WORD_GFqn];

