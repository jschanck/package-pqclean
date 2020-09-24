--- upstream/Reference_Implementation/sign/GeMSS128/include/conv_gf2nx.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/conv_gf2nx.h
@@ -10,7 +10,7 @@
 
 
 void PREFIX_NAME(convHFEpolynomialSparseToDense_gf2nx)(gf2nx F_dense,
-                                          const complete_sparse_monic_gf2nx F);
+                                          complete_sparse_monic_gf2nx F);
 #define convHFEpolynomialSparseToDense_gf2nx \
             PREFIX_NAME(convHFEpolynomialSparseToDense_gf2nx)
 

