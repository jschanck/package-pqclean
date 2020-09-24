--- upstream/Reference_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
@@ -30,7 +30,7 @@
 
 #if HFEv
     #define LINEAR_VCASE_REF(a_veci) \
-        a_veci-=(HFEn-1)*NB_WORD_GFqn;\
+        (a_veci)-=(HFEn-1)*NB_WORD_GFqn;\
         MQS_cp=MQS+(HFEn+1)*NB_WORD_GFqn;\
         for(j=0;j<HFEv;++j)\
         {\
@@ -47,7 +47,7 @@
                 add2_gf2n(MQS_cp,tmp1);\
                 MQS_cp+=NB_WORD_GFqn;\
             }\
-            a_veci+=NB_WORD_GFqn;\
+            (a_veci)+=NB_WORD_GFqn;\
         }\
         F_cp+=HFEv*NB_WORD_GFqn;
 #else
@@ -64,7 +64,7 @@
     for(j=1;j<HFEn;++j)\
     {\
         mul_gf2n(lin_cp,F_cp,a_vec);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;
@@ -80,7 +80,7 @@
     {\
         mul_gf2n(tmp1,F_cp,a_vec);\
         add2_gf2n(lin_cp,tmp1);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;\
@@ -97,7 +97,7 @@
     for(j=1;j<HFEn;++j)\
     {\
         add2_gf2n(lin_cp,a_vec);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }
 
@@ -124,7 +124,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_vec+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_vec)+ja*NB_WORD_GFqn);\
         mul_gf2n(MQS_cp,tmp1,F_cp);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
@@ -143,16 +143,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,tmp_i,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_i,(a_vecj)+ja*NB_WORD_GFqn);\
             copy_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,tmp_j,a_vec+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_j,(a_vec)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_vec+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;
 
@@ -175,7 +175,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_veci+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_veci)+ja*NB_WORD_GFqn);\
         mul_gf2n(tmp_i,tmp1,F_cp);\
         add2_gf2n(MQS_cp,tmp_i);\
         MQS_cp+=NB_WORD_GFqn;\
@@ -196,16 +196,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,tmp_i,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_i,(a_vecj)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,tmp_j,a_veci+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_j,(a_veci)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_veci+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_veci)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     /* Here, a_veci = row i+1 */\
     /* Here, a_vecj = row j+1 */\
@@ -229,7 +229,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_veci+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_veci)+ja*NB_WORD_GFqn);\
         add2_gf2n(MQS_cp,tmp1);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
@@ -246,16 +246,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,a_veci,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_veci,(a_vecj)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,a_vecj,a_veci+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vecj,(a_veci)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_veci+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_veci)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     /* Here, a_veci = row i+1 */\
     /* Here, a_vecj = row j+1 */
@@ -276,7 +276,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(MQS_cp,a_vecj+ja*NB_WORD_GFqn,a_vec+ja*NB_WORD_GFqn);\
+        add_gf2n(MQS_cp,(a_vecj)+ja*NB_WORD_GFqn,(a_vec)+ja*NB_WORD_GFqn);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
 \
@@ -291,16 +291,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,a_vec,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vec,(a_vecj)+ja*NB_WORD_GFqn);\
             copy_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,a_vecj,a_vec+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vecj,(a_vec)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_vec+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }
 
 
@@ -322,6 +322,11 @@
 int PREFIX_NAME(genSecretMQS_gf2_ref)(mqsnv_gf2n MQS, cst_sparse_monic_gf2nx F)
 {
     /* if there is not quadratic terms X^(2^i + 2^j) */
+    mqsnv_gf2n MQS_cp;
+    UINT lin[HFEn*NB_WORD_GFqn]={0};
+    UINT *lin_cp;
+    cst_vec_gf2n a_vec;
+    unsigned int i,j;
     #if (HFEDeg<3)
         #if (HFEDeg==2)
             cst_vec_gf2n a_veci;
@@ -329,63 +334,41 @@
         #if ((HFEDeg==2)||(HFEv))
             cst_sparse_monic_gf2nx F_cp;
         #endif
-        mqsnv_gf2n MQS_cp;
-        vecn_gf2n lin,lin_cp;
-        cst_vec_gf2n a_vec;
-        unsigned int i,j;
     #else
-        mqsnv_gf2n MQS_cp;
-        vecn_gf2n lin,lin_cp;
         static_gf2n tmp1[NB_WORD_GFqn];
         #if (HFEDeg!=3)
             static_gf2n tmp_i[NB_WORD_GFqn],tmp_j[NB_WORD_GFqn];
         #endif
         cst_sparse_monic_gf2nx F_cp;
-        cst_vec_gf2n a_vec,a_veci,a_vecj;
-        unsigned int i,j,ia,ja;
-    #endif
-
-    #if(HFEDeg<3)
-        /* there are not quadratic terms X^(2^i + 2^j) */
-        for(i=0;i<MQnv_GFqn_SIZE;++i)
-        {
-            MQS[i]=0;
-        }
+        cst_vec_gf2n a_veci,a_vecj;
+        unsigned int ia,ja;
     #endif
 
     /* Precompute alpha_vec is disabled in the submission */
     #if PRECOMPUTED_CBASIS
         static cst_vec_gf2n alpha_vec=cbasis_h;
     #else
-        vec_gf2n alpha_vec;
-
         /* Matrix in GF(2^n) with (HFEDegI+1) rows and HFEn-1 columns */
         /* calloc is useful when it initialises a multiple precision element
            to 1 */
         #if(HFEDegI!=HFEDegJ)
-            alpha_vec=(UINT*)calloc((HFEDegI+1)*(HFEn-1)*NB_WORD_GFqn,
-                                    sizeof(UINT));
+            UINT alpha_vec[(HFEDegI+1)*(HFEn-1)*NB_WORD_GFqn] = {0};
         #else
             /* An additional row for the leading term X^(2^i + 2^j)
                                                     = X^(2^(i+1)) */
-            alpha_vec=(UINT*)calloc((HFEDegI+2)*(HFEn-1)*NB_WORD_GFqn,
-                                    sizeof(UINT));
+            UINT alpha_vec[(HFEDegI+2)*(HFEn-1)*NB_WORD_GFqn] = {0};
         #endif
-        VERIFY_ALLOC_RET(alpha_vec);
 
         genCanonicalBasis_gf2n(alpha_vec);
     #endif
 
-    /* Temporary linear vector */
-    lin=(UINT*)calloc(HFEn*NB_WORD_GFqn,sizeof(UINT));
-    if(!lin)
-    {
-        #if (!PRECOMPUTED_CBASIS)
-            free(alpha_vec);
-        #endif
-        return ERROR_ALLOC;
-    }
-
+    #if(HFEDeg<3)
+        /* there are not quadratic terms X^(2^i + 2^j) */
+        for(i=0;i<MQnv_GFqn_SIZE;++i)
+        {
+            MQS[i]=0;
+        }
+    #endif
 
     /* Constant : copy the first coefficient of F in MQS */
     copy_gf2n(MQS,F);
@@ -482,16 +465,13 @@
     /* The current term is X^(q^i + q^j) */
     for(i=2;i<HFEDegI;++i)
     {
-        /* Here a_vec = row i */
+        j = 0;
         #if ENABLED_REMOVE_ODD_DEGREE
-        j=(((ONE32<<i)+ONE32)<=HFE_odd_degree)?0:1;
+        if (((ONE32<<i)+ONE32) > HFE_odd_degree) j=1;
+        #endif
+        /* Here a_vec = row i */
         a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
         for(;j<i;++j)
-        #else
-        /* Here a_vec = row i */
-        a_vecj=alpha_vec;
-        for(j=0;j<i;++j)
-        #endif
         {
             a_veci=a_vec;
             QUADRATIC_CASE_REF(a_veci,a_vecj);
@@ -509,19 +489,19 @@
     /* The current term is X^(q^HFEDegi + q^j) */
 
     /* Here a_vec = row i */
+    j = 0;
     #if ENABLED_REMOVE_ODD_DEGREE
-    j=(((ONE32<<i)+ONE32)<=HFE_odd_degree)?0:1;
-    a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
-    for(;j<HFEDegJ;++j)
-    #else
-    /* Here a_vec = row i */
-    a_vecj=alpha_vec;
-    for(j=0;j<HFEDegJ;++j)
+    if (((ONE32<<i)+ONE32) > HFE_odd_degree) j=1;
     #endif
+    /* Here a_vec = row i */
+    a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
+    #if HFEDegJ
+    for(; j<HFEDegJ;++j)
     {
         a_veci=a_vec;
         QUADRATIC_CASE_REF(a_veci,a_vecj);
     }
+    #endif
     /* Here a_veci = row i+1 */
 
     /* j=HFEDegJ */
@@ -539,10 +519,6 @@
     #endif
     #endif
 
-    #if (!PRECOMPUTED_CBASIS)
-        free(alpha_vec);
-    #endif
-
     /* Put linear part on "diagonal" of MQS */
     lin_cp=lin;
     MQS_cp=MQS+NB_WORD_GFqn;
@@ -553,7 +529,6 @@
         MQS_cp+=i*NB_WORD_GFqn;
     }
 
-    free(lin);
     return 0;
 }
 

