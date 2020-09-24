--- upstream/Optimized_Implementation/sign/GeMSS128/include/frobeniusMap_gf2nx.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/frobeniusMap_gf2nx.h
@@ -9,7 +9,7 @@
 #include "gf2nx.h"
 
 
-unsigned int PREFIX_NAME(frobeniusMap_HFE_gf2nx)(gf2nx Xqn, const
+unsigned int PREFIX_NAME(frobeniusMap_HFE_gf2nx)(gf2nx Xqn,
                                     complete_sparse_monic_gf2nx F, cst_gf2n U);
 #define frobeniusMap_HFE_gf2nx PREFIX_NAME(frobeniusMap_HFE_gf2nx)
 
@@ -87,7 +87,7 @@
 #define KX (HFEDeg-KP)
 
 
-unsigned int PREFIX_NAME(frobeniusMap_multisqr_HFE_gf2nx)(gf2nx Xqn, const
+unsigned int PREFIX_NAME(frobeniusMap_multisqr_HFE_gf2nx)(gf2nx Xqn,
                                     complete_sparse_monic_gf2nx F, cst_gf2n U);
 #define frobeniusMap_multisqr_HFE_gf2nx \
             PREFIX_NAME(frobeniusMap_multisqr_HFE_gf2nx)

