--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/conv_gf2nx.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/conv_gf2nx.h
@@ -10,7 +10,7 @@
 
 
 void PREFIX_NAME(convHFEpolynomialSparseToDense_gf2nx)(gf2nx F_dense,
-                                          const complete_sparse_monic_gf2nx F);
+                                          complete_sparse_monic_gf2nx F);
 #define convHFEpolynomialSparseToDense_gf2nx \
             PREFIX_NAME(convHFEpolynomialSparseToDense_gf2nx)
 

