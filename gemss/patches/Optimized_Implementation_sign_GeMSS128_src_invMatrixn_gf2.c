--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/invMatrixn_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/invMatrixn_gf2.c
@@ -49,7 +49,7 @@
 
 #define LOOPIR(NB_IT,LOOPK1,LOOPK2) \
     bit_ir=UINT_1;\
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* If the pivot is 0, search the pivot */\
         if(!((*S_cpi)&bit_ir))\
@@ -70,7 +70,7 @@
 
 /* Only modify S_inv */
 #define LOOPIR_DOWN_TO_UP(NB_IT) \
-    for(ir=NB_IT-1;ir!=(unsigned int)(-1);--ir,--i)\
+    for(ir=(NB_IT)-1;ir!=(unsigned int)(-1);--ir,--i)\
     {\
         S_cpj=S_cpi;\
         Sinv_cpj=Sinv_cpi;\
@@ -133,7 +133,6 @@
         LOOPIR(HFEnr-1,SWAP_WORD(*S_cpj,*S_cpi),*S_cpj^=*S_cpi&mask);
 
         /* Step 2 */
-        bit_ir=UINT_1<<(HFEnr-1);
         LOOPIR_DOWN_TO_UP(HFEnr);
     #else
         /* To begin to last row */
@@ -178,7 +177,7 @@
     }
 
 #define LOOPIR_CST(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* row i += (1-pivot_i)* row j */\
         LOOPJ_CST({mask=(-(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\

