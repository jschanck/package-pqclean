--- upstream/Optimized_Implementation/sign/GeMSS128/src/randMatrix_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/randMatrix_gf2.c
@@ -135,92 +135,85 @@
 #endif
 
 
-#define CLEANLOWMATRIX_GF2(NAME,LTRIANGULAR_SIZE,nq,nr) \
-void NAME(Tn_gf2 L) \
-{\
-    UINT mask;\
-    unsigned int iq,ir;\
-\
-    /* for each row */\
-    for(iq=1;iq<=nq;++iq)\
-    {\
-        mask=0;\
-        for(ir=0;ir<NB_BITS_UINT;++ir)\
-        {\
-            /* Put the bit of diagonal to 1 + zeros after the diagonal */\
-            *L&=mask;\
-            *L^=UINT_1<<ir;\
-            mask<<=1;\
-            ++mask;\
-\
-            L+=iq;\
-        }\
-        /* Next column */\
-        ++L;\
-    }\
-\
-    /* iq = HFEnq */\
-    mask=0;\
-    for(ir=0;ir<nr;++ir)\
-    {\
-        /* Put the bit of diagonal to 1 + zeros after the diagonal */\
-        *L&=mask;\
-        *L^=UINT_1<<ir;\
-        mask<<=1;\
-        ++mask;\
-\
-        L+=iq;\
-    }\
-}
+void PREFIX_NAME(cleanLowerMatrixn)(Tn_gf2 L)
+{
+    UINT mask;
+    unsigned int iq,ir;
+
+    /* for each row */
+    for(iq=1;iq<=HFEnq;++iq)
+    {
+        mask=0;
+        for(ir=0;ir<NB_BITS_UINT;++ir)
+        {
+            /* Put the bit of diagonal to 1 + zeros after the diagonal */
+            *L&=mask;
+            *L^=UINT_1<<ir;
+            mask<<=1;
+            ++mask;
+
+            L+=iq;
+        }
+        /* Next column */
+        ++L;
+    }
 
+    #if HFEnr
+    /* iq = HFEnq */
+    mask=0;
+    for(ir=0;ir<HFEnr;++ir)
+    {
+        /* Put the bit of diagonal to 1 + zeros after the diagonal */
+        *L&=mask;
+        *L^=UINT_1<<ir;
+        mask<<=1;
+        ++mask;
 
-CLEANLOWMATRIX_GF2(PREFIX_NAME(cleanLowerMatrixn),LTRIANGULAR_N_SIZE,HFEnq,
-                   HFEnr);
+        L+=iq;
+    }
+    #endif
+}
 #if HFEv
-    CLEANLOWMATRIX_GF2(PREFIX_NAME(cleanLowerMatrixnv),LTRIANGULAR_NV_SIZE,
-                       HFEnvq,HFEnvr);
-#endif
+void PREFIX_NAME(cleanLowerMatrixnv)(Tn_gf2 L)
+{
+    UINT mask;
+    unsigned int iq,ir;
+
+    /* for each row */
+    for(iq=1;iq<=HFEnvq;++iq)
+    {
+        mask=0;
+        for(ir=0;ir<NB_BITS_UINT;++ir)
+        {
+            /* Put the bit of diagonal to 1 + zeros after the diagonal */
+            *L&=mask;
+            *L^=UINT_1<<ir;
+            mask<<=1;
+            ++mask;
+
+            L+=iq;
+        }
+        /* Next column */
+        ++L;
+    }
 
+    #if HFEnvr
+    /* iq = HFEnq */
+    mask=0;
+    for(ir=0;ir<HFEnvr;++ir)
+    {
+        /* Put the bit of diagonal to 1 + zeros after the diagonal */
+        *L&=mask;
+        *L^=UINT_1<<ir;
+        mask<<=1;
+        ++mask;
 
-#define GENLOWMATRIX_GF2(NAME,LTRIANGULAR_SIZE,nq,nr) \
-void NAME(Tn_gf2 L) \
-{\
-    UINT mask;\
-    unsigned int iq,ir;\
-\
-    randombytes((unsigned char*)L,LTRIANGULAR_SIZE<<3);\
-\
-    /* for each row */\
-    for(iq=1;iq<=nq;++iq)\
-    {\
-        mask=0;\
-        for(ir=0;ir<NB_BITS_UINT;++ir)\
-        {\
-            /* Put the bit of diagonal to 1 + zeros after the diagonal */\
-            *L&=mask;\
-            *L^=UINT_1<<ir;\
-            mask<<=1;\
-            ++mask;\
-\
-            L+=iq;\
-        }\
-        /* Next column */\
-        ++L;\
-    }\
-\
-    /* iq = HFEnq */\
-    mask=0;\
-    for(ir=0;ir<nr;++ir)\
-    {\
-        /* Put the bit of diagonal to 1 + zeros after the diagonal */\
-        *L&=mask;\
-        *L^=UINT_1<<ir;\
-        mask<<=1;\
-        ++mask;\
-\
-        L+=iq;\
-    }\
+        L+=iq;
+    }
+    #endif
 }
+#endif
+
 
 /**
  * @brief   Generate a random invertible lower triangular matrix (n,n) L in 
@@ -231,7 +224,47 @@
  * words equal to zero in the upper trigular part are not stored.
  * @remark  Constant-time implementation.
  */
-GENLOWMATRIX_GF2(PREFIX_NAME(genLowerMatrixn),LTRIANGULAR_N_SIZE,HFEnq,HFEnr);
+void PREFIX_NAME(genLowerMatrixn)(Tn_gf2 L)
+{
+    UINT mask;
+    unsigned int iq,ir;
+
+    randombytes((unsigned char*)L,LTRIANGULAR_N_SIZE<<3);
+
+    /* for each row */
+    for(iq=1;iq<=HFEnq;++iq)
+    {
+        mask=0;
+        for(ir=0;ir<NB_BITS_UINT;++ir)
+        {
+            /* Put the bit of diagonal to 1 + zeros after the diagonal */
+            *L&=mask;
+            *L^=UINT_1<<ir;
+            mask<<=1;
+            ++mask;
+
+            L+=iq;
+        }
+        /* Next column */
+        ++L;
+    }
+
+    #if HFEnr
+    /* iq = HFEnq */
+    mask=0;
+    for(ir=0;ir<HFEnr;++ir)
+    {
+        /* Put the bit of diagonal to 1 + zeros after the diagonal */
+        *L&=mask;
+        *L^=UINT_1<<ir;
+        mask<<=1;
+        ++mask;
+
+        L+=iq;
+    }
+    #endif
+}
+
 #if HFEv
     /**
      * @brief   Generate a random invertible lower triangular matrix (n+v,n+v) L
@@ -243,15 +276,53 @@
      * the words equal to zero in the upper trigular part are not stored.
      * @remark  Constant-time implementation.
      */
-    GENLOWMATRIX_GF2(PREFIX_NAME(genLowerMatrixnv),LTRIANGULAR_NV_SIZE,HFEnvq,
-                     HFEnvr);
+void PREFIX_NAME(genLowerMatrixnv)(Tn_gf2 L)
+{
+    UINT mask;
+    unsigned int iq,ir;
+
+    randombytes((unsigned char*)L,LTRIANGULAR_NV_SIZE<<3);
+
+    /* for each row */
+    for(iq=1;iq<=HFEnvq;++iq)
+    {
+        mask=0;
+        for(ir=0;ir<NB_BITS_UINT;++ir)
+        {
+            /* Put the bit of diagonal to 1 + zeros after the diagonal */
+            *L&=mask;
+            *L^=UINT_1<<ir;
+            mask<<=1;
+            ++mask;
+
+            L+=iq;
+        }
+        /* Next column */
+        ++L;
+    }
+
+    #if HFEnvr
+    /* iq = HFEnq */
+    mask=0;
+    for(ir=0;ir<HFEnvr;++ir)
+    {
+        /* Put the bit of diagonal to 1 + zeros after the diagonal */
+        *L&=mask;
+        *L^=UINT_1<<ir;
+        mask<<=1;
+        ++mask;
+
+        L+=iq;
+    }
+    #endif
+}
 #endif
 
 
 #define LOOPJR(NB_IT) \
     mini=MINI(iq,jq);\
     *S=0;\
-    for(jr=0;jr<NB_IT;++jr)\
+    for(jr=0;jr<(NB_IT);++jr)\
     {\
         /* Dot product */\
         tmp=L_cp[0]&U_cp[0];\
@@ -267,36 +338,19 @@
 
 
 #define LOOPIR(NB_IT,nq,nr,REM) \
-    for(ir=0;ir<NB_IT;++ir)\
+    for(ir=0;ir<(NB_IT);++ir)\
     {\
         U_cp=U;\
         /* for each row of U (multiply by the transpose) */\
-        for(jq=1;jq<=nq;++jq)\
+        for(jq=1;jq<=(nq);++jq)\
         {\
             LOOPJR(NB_BITS_UINT);\
         }\
-        REM;\
+        { REM };\
         L_cp+=iq;\
     }
 
 
-#define MULMATRICESLU_GF2(NAME,nq,nr,REM) \
-void NAME(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U) \
-{\
-    cst_Tn_gf2 L_cp,U_cp;\
-    UINT tmp;\
-    unsigned int iq,ir,jq,jr,k,mini;\
-\
-    /* Computation of S = L*U */\
-    L_cp=L;\
-    /* for each row of L (and S) */\
-    for(iq=1;iq<=nq;++iq)\
-    {\
-        LOOPIR(NB_BITS_UINT,nq,nr,REM);\
-    }\
-    LOOPIR(nr,nq,nr,REM);\
-}
-
 /**
  * @brief   Compute the matrix (n,n) L*U in GF(2).
  * @param[out]  S   S=L*U is a matrix (n,n) in GF(2).
@@ -304,9 +358,37 @@
  * @remark  Constant-time implementation.
  */
 #if HFEnr
-MULMATRICESLU_GF2(PREFIX_NAME(mulMatricesLU_gf2_n),HFEnq,HFEnr,LOOPJR(HFEnr));
+void PREFIX_NAME(mulMatricesLU_gf2_n)(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U)
+{
+    cst_Tn_gf2 L_cp,U_cp;
+    UINT tmp;
+    unsigned int iq,ir,jq,jr,k,mini;
+
+    /* Computation of S = L*U */
+    L_cp=L;
+    /* for each row of L (and S) */
+    for(iq=1;iq<=HFEnq;++iq)
+    {
+        LOOPIR(NB_BITS_UINT,HFEnq,HFEnr,LOOPJR(HFEnr));
+    }
+    LOOPIR(HFEnr,HFEnq,HFEnr,LOOPJR(HFEnr));
+}
 #else
-MULMATRICESLU_GF2(PREFIX_NAME(mulMatricesLU_gf2_n),HFEnq,HFEnr,);
+void PREFIX_NAME(mulMatricesLU_gf2_n)(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U)
+{
+    cst_Tn_gf2 L_cp,U_cp;
+    UINT tmp;
+    unsigned int iq,ir,jq,jr,k,mini;
+
+    /* Computation of S = L*U */
+    L_cp=L;
+    /* for each row of L (and S) */
+    for(iq=1;iq<=HFEnq;++iq)
+    {
+        LOOPIR(NB_BITS_UINT,HFEnq,HFEnr,);
+    }
+    LOOPIR(HFEnr,HFEnq,HFEnr,);
+}
 #endif
 
 #if HFEv
@@ -317,10 +399,36 @@
      * @remark  Constant-time implementation.
      */
     #if HFEnvr
-        MULMATRICESLU_GF2(PREFIX_NAME(mulMatricesLU_gf2_nv),HFEnvq,HFEnvr,
-                          LOOPJR(HFEnvr));
+        void PREFIX_NAME(mulMatricesLU_gf2_nv)(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U)
+        {
+            cst_Tn_gf2 L_cp,U_cp;
+            UINT tmp;
+            unsigned int iq,ir,jq,jr,k,mini;
+
+            /* Computation of S = L*U */
+            L_cp=L;
+            /* for each row of L (and S) */
+            for(iq=1;iq<=HFEnvq;++iq)
+            {
+                LOOPIR(NB_BITS_UINT,HFEnvq,HFEnvr,LOOPJR(HFEnvr));
+            }
+            LOOPIR(HFEnvr,HFEnvq,HFEnvr,LOOPJR(HFEnvr));
+        }
     #else
-        MULMATRICESLU_GF2(PREFIX_NAME(mulMatricesLU_gf2_nv),HFEnvq,HFEnvr,);
+        void PREFIX_NAME(mulMatricesLU_gf2_nv)(Mn_gf2 S, cst_Tn_gf2 L, cst_Tn_gf2 U)
+        {
+            cst_Tn_gf2 L_cp,U_cp;
+            UINT tmp;
+            unsigned int iq,ir,jq,jr,k,mini;
+
+            /* Computation of S = L*U */
+            L_cp=L;
+            /* for each row of L (and S) */
+            for(iq=1;iq<=HFEnvq;++iq)
+            {
+                LOOPIR(NB_BITS_UINT,HFEnvq,HFEnvr,);
+            }
+        }
     #endif
 #endif
 

