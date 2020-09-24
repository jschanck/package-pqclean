--- upstream/Optimized_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
@@ -26,16 +26,14 @@
  */
 int PREFIX_NAME(changeVariablesMQS_simd_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S)
 {
-    UINT tmp[NB_WORD_GFqn];
-    mqsnv_gf2n MQS2, MQS2_cp;
+    UINT tmp[NB_WORD_GFqn]={0};
+    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
+    UINT MQS2[HFEnv*HFEnv*NB_WORD_GFqn]={0};
+    UINT *MQS2_cp;
     cst_mqsnv_gf2n MQS_cpi,MQS_cpj;
     cst_GLnv_gf2 S_cpi,S_cpj;
     unsigned int i,j;
 
-    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
-    MQS2=(UINT*)malloc(HFEnv*HFEnv*NB_WORD_GFqn*sizeof(UINT));
-    VERIFY_ALLOC_RET(MQS2);
-
     /* To avoid the constant of MQS */
     MQS+=NB_WORD_GFqn;
 
@@ -129,8 +127,6 @@
         S_cpj+=NB_WORD_GF2nv;
     }
 
-
-    free(MQS2);
     return 0;
 }
 
@@ -142,7 +138,7 @@
 
 /* Compute a dot product with one word of S */
 #define LOOPKR(START,NB_IT) \
-    for(kr=START;kr<NB_IT;++kr)\
+    for(kr=(START);kr<(NB_IT);++kr)\
     {\
         /* multiply one bit of S by one element of MQS_cpj */\
         mask=-(bit_kr&UINT_1); \
@@ -192,7 +188,7 @@
 
 /* Loop for a block of rows */
 #define LOOPIR(STARTIR,NB_ITIR,LOOPK) \
-    for(ir=STARTIR;ir<NB_ITIR;++ir)\
+    for(ir=(STARTIR);ir<(NB_ITIR);++ir)\
     {\
         /* Compute a dot product */\
         LOOPK;\
@@ -204,7 +200,7 @@
 /* Loop for a block of rows */
 /* Init to 0 the res */
 #define LOOPIR_INIT(STARTIR,NB_ITIR) \
-    for(ir=STARTIR;ir<NB_ITIR;++ir)\
+    for(ir=(STARTIR);ir<(NB_ITIR);++ir)\
     {\
         set0_gf2n(MQS2_cp);\
         MQS_cpj=MQS_cpi;\
@@ -236,16 +232,14 @@
  */
 int PREFIX_NAME(changeVariablesMQS64_gf2)(mqsnv_gf2n MQS, cst_GLnv_gf2 S)
 {
-    mqsnv_gf2n MQS2, MQS2_cp;
+    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
+    UINT MQS2[HFEnv*HFEnv*NB_WORD_GFqn]={0};
+    UINT *MQS2_cp;
     UINT bit_kr, mask;
     cst_mqsnv_gf2n MQS_cpi,MQS_cpj;
     cst_GLnv_gf2 S_cpi,S_cpj;
     unsigned int iq,ir,j,jq,jr,kq,kr;
 
-    /* Tmp matrix (n+v)*(n+v) of quadratic terms to compute S*Q */
-    MQS2=(UINT*)calloc(HFEnv*HFEnv*NB_WORD_GFqn,sizeof(UINT));
-    VERIFY_ALLOC_RET(MQS2);
-
     /* To avoid the constant of MQS */
     MQS_cpi=MQS+NB_WORD_GFqn;
 
@@ -401,8 +395,6 @@
        }
     #endif
 
-
-    free(MQS2);
     return 0;
 }
 

