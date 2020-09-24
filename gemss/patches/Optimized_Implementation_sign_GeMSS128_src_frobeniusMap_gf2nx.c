--- upstream/Optimized_Implementation/sign/GeMSS128/src/frobeniusMap_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/frobeniusMap_gf2nx.c
@@ -271,9 +271,10 @@
 {
     static_gf2n cst[NB_WORD_GFqn];
     static_gf2n mul_coef[NB_WORD_GFqn];
-    gf2nx Xqn_cp;
-    vec_gf2nx table,table_cp;
-    gf2nx Xqn_sqr;
+    UINT table[(KX*HFEDeg+POW_II)*NB_WORD_GFqn];
+    UINT Xqn_sqr[HFEDeg*NB_WORD_GFqn]={0};
+    UINT *table_cp;
+    UINT *Xqn_cp;
     gf2n current_coef;
     #if CONSTANT_TIME
         UINT b,mask;
@@ -284,16 +285,12 @@
     add_gf2n(cst,F.poly,U);
 
     /* Table of the X^(k*2^II) mod F. */
-    table=(UINT*)malloc((KX*HFEDeg+POW_II)*NB_WORD_GFqn*sizeof(UINT));
     precompute_table(table,F,cst);
 
     /* X^(2^(HFEDegI+II)) = X^( (2^HFEDegI) * (2^II)) */
     /* We take the polynomial from the table */
-    table+=(((ONE32<<HFEDegI)-KP)*HFEDeg)*NB_WORD_GFqn;
-    copy_gf2nx(Xqn,table,HFEDeg,i);
-    table-=(((ONE32<<HFEDegI)-KP)*HFEDeg)*NB_WORD_GFqn;
+    copy_gf2nx(Xqn,table+((((ONE32<<HFEDegI)-KP)*HFEDeg)*NB_WORD_GFqn),HFEDeg,i);
 
-    Xqn_sqr=(UINT*)calloc(HFEDeg*NB_WORD_GFqn,sizeof(UINT));
     for(i=0;i<((HFEn-HFEDegI-II)/II);++i)
     {
         /* Step 1: Xqn^(2^II) with II squarings */
@@ -349,9 +346,6 @@
         }
     }
 
-    free(table);
-    free(Xqn_sqr);
-
     #if ((HFEn-HFEDegI)%II)
         #if (!CONSTANT_TIME)
             d=HFEDeg-1;

