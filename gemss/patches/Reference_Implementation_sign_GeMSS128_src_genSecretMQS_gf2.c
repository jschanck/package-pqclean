--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
@@ -512,11 +512,11 @@
     #if ENABLED_REMOVE_ODD_DEGREE
     j=(((ONE32<<i)+ONE32)<=HFE_odd_degree)?0:1;
     a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
-    for(;j<HFEDegJ;++j)
+    for(;(int)j<HFEDegJ;++j)
     #else
     /* Here a_vec = row i */
     a_vecj=alpha_vec;
-    for(j=0;j<HFEDegJ;++j)
+    for(j=0;(int)j<HFEDegJ;++j)
     #endif
     {
         a_veci=a_vec;

