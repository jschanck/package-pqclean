--- upstream/Optimized_Implementation/sign/GeMSS128/src/conv_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/conv_gf2nx.c
@@ -41,7 +41,7 @@
  * @remark  Constant-time implementation.
  */
 void PREFIX_NAME(convHFEpolynomialSparseToDense_gf2nx)(gf2nx F_dense,
-                                          const complete_sparse_monic_gf2nx F)
+                                          complete_sparse_monic_gf2nx F)
 {
     cst_sparse_monic_gf2nx F_cp=F.poly;
     gf2nx F_dense_cp=F_dense;

