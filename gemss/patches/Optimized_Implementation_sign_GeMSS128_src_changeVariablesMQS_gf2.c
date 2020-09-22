--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
@@ -142,7 +142,7 @@
 
 /* Compute a dot product with one word of S */
 #define LOOPKR(START,NB_IT) \
-    for(kr=START;kr<NB_IT;++kr)\
+    for(kr=(START);kr<(NB_IT);++kr)\
     {\
         /* multiply one bit of S by one element of MQS_cpj */\
         mask=-(bit_kr&UINT_1); \
@@ -192,7 +192,7 @@
 
 /* Loop for a block of rows */
 #define LOOPIR(STARTIR,NB_ITIR,LOOPK) \
-    for(ir=STARTIR;ir<NB_ITIR;++ir)\
+    for(ir=(STARTIR);ir<(NB_ITIR);++ir)\
     {\
         /* Compute a dot product */\
         LOOPK;\
@@ -204,7 +204,7 @@
 /* Loop for a block of rows */
 /* Init to 0 the res */
 #define LOOPIR_INIT(STARTIR,NB_ITIR) \
-    for(ir=STARTIR;ir<NB_ITIR;++ir)\
+    for(ir=(STARTIR);ir<(NB_ITIR);++ir)\
     {\
         set0_gf2n(MQS2_cp);\
         MQS_cpj=MQS_cpi;\

