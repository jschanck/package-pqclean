--- upstream/Reference_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/changeVariablesMQS_gf2.c
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
 

