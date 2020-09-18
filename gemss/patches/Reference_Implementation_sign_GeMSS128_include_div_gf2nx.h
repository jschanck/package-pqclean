--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/div_gf2nx.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/div_gf2nx.h
@@ -47,8 +47,8 @@
     #define divsqr_r_HFE_cstdeg_gf2nx PREFIX_NAME(divsqr_r_HFE_cstdeg_gf2nx)
     #define divsqr_r_HFE_cst_gf2nx PREFIX_NAME(divsqr_r_HFE_cst_gf2nx)
 #else
-    #define divsqr_r_HFE_cstdeg_gf2nx PREFIX_NAME(div_r_HFE_cstdeg_gf2nx)
-    #define divsqr_r_HFE_cst_gf2nx PREFIX_NAME(div_r_HFE_cst_gf2nx)
+    #define divsqr_r_HFE_cstdeg_gf2nx div_r_HFE_cstdeg_gf2nx
+    #define divsqr_r_HFE_cst_gf2nx div_r_HFE_cst_gf2nx
 #endif
 
 

