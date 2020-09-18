--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/vecMatProduct_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/vecMatProduct_gf2.c
@@ -115,65 +115,124 @@
         res a vector of length n in GF(2)
         res = dotproduct(v,S) = v.S
 */
-#define VECMATPROD(NAME,SET0,LOOPIR,REM,nq) \
-void NAME(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S)\
-{\
-    cst_Mn_gf2 S_cp;\
-    UINT bit_ir, vec_ir;\
-    unsigned int iq,ir;\
-\
-    /* initialization of res to 0 */\
-    SET0(res);\
-\
-    S_cp=S;\
-    /* for each bit of vec excepted the last block */\
-    for(iq=0;iq<nq;++iq)\
-    {\
-        bit_ir=vec[iq];\
-        LOOPIR(NB_BITS_UINT);\
-    }\
-    /* the last block */\
-    REM(LOOPIR);\
+void PREFIX_NAME(vecMatProductnv_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2nv(res);
+
+    S_cp=S;
+    /* for each bit of vec excepted the last block */
+    for(iq=0;iq<HFEnvq;++iq)
+    {
+        bit_ir=vec[iq];
+        LOOPIR_NV(NB_BITS_UINT);
+    }
+    /* the last block */
+    REM_NV(LOOPIR_NV);
 }
 
+void PREFIX_NAME(vecMatProductnvn_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2n(res);
+
+    S_cp=S;
+    /* for each bit of vec excepted the last block */
+    for(iq=0;iq<HFEnvq;++iq)
+    {
+        bit_ir=vec[iq];
+        LOOPIR_N(NB_BITS_UINT);
+    }
+    /* the last block */
+    REM_NV(LOOPIR_N);
+}
 
-VECMATPROD(PREFIX_NAME(vecMatProductnv_64),set0_gf2nv,LOOPIR_NV,REM_NV,HFEnvq)
-VECMATPROD(PREFIX_NAME(vecMatProductnvn_64),set0_gf2n,LOOPIR_N,REM_NV,HFEnvq)
-VECMATPROD(PREFIX_NAME(vecMatProductv_64),set0_gf2n,LOOPIR_N,REM_V,HFEvq)
-VECMATPROD(PREFIX_NAME(vecMatProductn_64),set0_gf2n,LOOPIR_N,REM_N,HFEnq)
-VECMATPROD(PREFIX_NAME(vecMatProductm_64),set0_gf2m,LOOPIR_M,REM_M,HFEnq)
-
-
-#define VECMATPROD_START(NAME,SET0,LOOPIR_START,REM_START,nq) \
-void NAME(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S, unsigned int start)\
-{\
-    cst_Mn_gf2 S_cp;\
-    UINT bit_ir, vec_ir;\
-    unsigned int iq,ir;\
-\
-    /* initialization of res to 0 */\
-    SET0(res);\
-\
-    S_cp=S;\
-    ir=start&63U;\
-    /* for each bit of vec excepted the last block */\
-    for(iq=start>>6;iq<nq;++iq)\
-    {\
-        bit_ir=vec[iq]>>ir;\
-        LOOPIR_START(NB_BITS_UINT);\
-        ir=0;\
-    }\
-    /* the last block */\
-    REM_START(LOOPIR_START);\
+void PREFIX_NAME(vecMatProductv_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2n(res);
+
+    S_cp=S;
+    /* for each bit of vec excepted the last block */
+    for(iq=0;(int)iq<HFEvq;++iq)
+    {
+        bit_ir=vec[iq];
+        LOOPIR_N(NB_BITS_UINT);
+    }
+    /* the last block */
+    REM_V(LOOPIR_N);
+}
+
+void PREFIX_NAME(vecMatProductn_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2n(res);
+
+    S_cp=S;
+    /* for each bit of vec excepted the last block */
+    for(iq=0;iq<HFEnq;++iq)
+    {
+        bit_ir=vec[iq];
+        LOOPIR_N(NB_BITS_UINT);
+    }
+    /* the last block */
+    REM_N(LOOPIR_N);
+}
+
+void PREFIX_NAME(vecMatProductm_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2m(res);
+
+    S_cp=S;
+    /* for each bit of vec excepted the last block */
+    for(iq=0;iq<HFEnq;++iq)
+    {
+        bit_ir=vec[iq];
+        LOOPIR_M(NB_BITS_UINT);
+    }
+    /* the last block */
+    REM_M(LOOPIR_M);
+}
+
+
+void PREFIX_NAME(vecMatProductnvn_start_64)(vecn_gf2 res, cst_vecn_gf2 vec, cst_Mn_gf2 S, unsigned int start) {
+    cst_Mn_gf2 S_cp;
+    UINT bit_ir, vec_ir;
+    unsigned int iq,ir;
+
+    /* initialization of res to 0 */
+    set0_gf2n(res);
+
+    S_cp=S;
+    ir=start&63U;
+    /* for each bit of vec excepted the last block */
+    for(iq=start>>6;iq<HFEnvq;++iq)
+    {
+        bit_ir=vec[iq]>>ir;
+        LOOPIR_START_N(NB_BITS_UINT);
+        ir=0;
+    }
+    /* the last block */
+    REM_START_NV(LOOPIR_START_N);
 }
 
 
-VECMATPROD_START(PREFIX_NAME(vecMatProductnvn_start_64),set0_gf2n,
-                 LOOPIR_START_N,REM_START_NV,HFEnvq)
-/*
-VECMATPROD_START(PREFIX_NAME(vecMatProductn_start_64),set0_gf2n,
-                 LOOPIR_START_N,REM_START_N,HFEnq)
-*/
 
 
 
