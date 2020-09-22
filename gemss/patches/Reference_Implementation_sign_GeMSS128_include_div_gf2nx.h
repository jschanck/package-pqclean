--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/div_gf2nx.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/div_gf2nx.h
@@ -24,13 +24,13 @@
 
 
 unsigned int PREFIX_NAME(div_r_HFE_gf2nx)(gf2nx poly, unsigned int dp,
-                                          const complete_sparse_monic_gf2nx F,
+                                          complete_sparse_monic_gf2nx F,
                                           cst_gf2n cst);
 void PREFIX_NAME(div_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
-                                         const complete_sparse_monic_gf2nx F,
+                                         complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst);
 void PREFIX_NAME(div_r_HFE_cst_gf2nx)(gf2nx poly,
-                                      const complete_sparse_monic_gf2nx F,
+                                      complete_sparse_monic_gf2nx F,
                                       cst_gf2n cst);
 #define div_r_HFE_gf2nx PREFIX_NAME(div_r_HFE_gf2nx)
 #define div_r_HFE_cstdeg_gf2nx PREFIX_NAME(div_r_HFE_cstdeg_gf2nx)
@@ -39,16 +39,16 @@
 
 #if ENABLED_REMOVE_ODD_DEGREE
     void PREFIX_NAME(divsqr_r_HFE_cstdeg_gf2nx)(gf2nx poly, unsigned int dp,
-                                           const complete_sparse_monic_gf2nx F,
+                                           complete_sparse_monic_gf2nx F,
                                            cst_gf2n cst);
     void PREFIX_NAME(divsqr_r_HFE_cst_gf2nx)(gf2nx poly,
-                                         const complete_sparse_monic_gf2nx F,
+                                         complete_sparse_monic_gf2nx F,
                                          cst_gf2n cst);
     #define divsqr_r_HFE_cstdeg_gf2nx PREFIX_NAME(divsqr_r_HFE_cstdeg_gf2nx)
     #define divsqr_r_HFE_cst_gf2nx PREFIX_NAME(divsqr_r_HFE_cst_gf2nx)
 #else
-    #define divsqr_r_HFE_cstdeg_gf2nx PREFIX_NAME(div_r_HFE_cstdeg_gf2nx)
-    #define divsqr_r_HFE_cst_gf2nx PREFIX_NAME(div_r_HFE_cst_gf2nx)
+    #define divsqr_r_HFE_cstdeg_gf2nx div_r_HFE_cstdeg_gf2nx
+    #define divsqr_r_HFE_cst_gf2nx div_r_HFE_cst_gf2nx
 #endif
 
 

