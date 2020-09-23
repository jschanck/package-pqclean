--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/vecMatProduct_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/vecMatProduct_gf2.c
@@ -9,12 +9,12 @@
 
 /* for a block of bits of vec */
 #define LOOPIR_M(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir)\
+    for(ir=0;ir<(NB_IT);++ir)\
     {\
         /* multiply the (iq*NB_BITS_UINT)+ir bit of vec
             by the (iq*NB_BITS_UINT)+ir row of S */\
         vec_ir=-(bit_ir&1);\
-        xorLoadMask1_gf2m(res,S_cp,vec_ir);\
+        XORLOADMASK1((unsigned char *)res,(unsigned char *)S_cp,vec_ir,8*NB_WORD_GF2m);\
         /* next row of S */\
         S_cp+=NB_WORD_GFqn;\
         bit_ir>>=1;\
@@ -22,7 +22,7 @@
 
 /* for a block of bits of vec */
 #define LOOPIR_N(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir)\
+    for(ir=0;ir<(NB_IT);++ir)\
     {\
         /* multiply the (iq*NB_BITS_UINT)+ir bit of vec
             by the (iq*NB_BITS_UINT)+ir row of S */\
@@ -35,7 +35,7 @@
 
 /* for a block of bits of vec */
 #define LOOPIR_START_N(NB_IT) \
-    for(;ir<NB_IT;++ir)\
+    for(;ir<(NB_IT);++ir)\
     {\
         /* multiply the (iq*NB_BITS_UINT)+ir bit of vec
             by the (iq*NB_BITS_UINT)+ir row of S */\
@@ -48,7 +48,7 @@
 
 /* for a block of bits of vec */
 #define LOOPIR_NV(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir)\
+    for(ir=0;ir<(NB_IT);++ir)\
     {\
         /* multiply the (iq*NB_BITS_UINT)+ir bit of vec
             by the (iq*NB_BITS_UINT)+ir row of S */\
@@ -69,7 +69,10 @@
 #endif
 
 #if HFEmr
-    #define CLEAN_M (res)[NB_WORD_GF2m-1]&=MASK_GF2m;
+    #define CLEAN_M \
+      LOAD_UINT(vec_ir, (((unsigned char *)res)+(8*(NB_WORD_GF2m-1)))) \
+      vec_ir &= MASK_GF2m; \
+      STORE_UINT((((unsigned char *)res)+(8*(NB_WORD_GF2m-1))), vec_ir)
 #else
     #define CLEAN_M
 #endif
@@ -115,65 +118,134 @@
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
+    iq = 0;
+    ir = 0;
+    while(NB_BITS_UINT*iq + ir < HFEv)
+    {
+        bit_ir = vec[iq];
+        for(ir=0;(NB_BITS_UINT*iq + ir < HFEv) && (ir<NB_BITS_UINT);++ir)
+        {
+            /* multiply the (iq*NB_BITS_UINT)+ir bit of vec
+                by the (iq*NB_BITS_UINT)+ir row of S */
+            vec_ir=-(bit_ir&1);
+            xorLoadMask1_gf2n(res,S_cp,vec_ir);
+            /* next row of S */
+            S_cp+=NB_WORD_GFqn;
+            bit_ir>>=1;
+        }
+        ++iq;
+    }
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
 
 
 

