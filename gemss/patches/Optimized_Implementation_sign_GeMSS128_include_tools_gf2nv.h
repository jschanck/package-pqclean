--- upstream/Optimized_Implementation/sign/GeMSS128/include/tools_gf2nv.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/tools_gf2nv.h
@@ -24,13 +24,13 @@
 /* The number of word that an element of GF(2^(n+v)) needs */
 #if (HFEnvr)
     #define NB_WORD_GF2nv_TMP (HFEnvq+1)
+    /* Mask for arithmetic in GF(2^(n+v)) */
+    #define MASK_GF2nv ((UINT_1<<(HFEnvr))-UINT_1)
 #else
     #define NB_WORD_GF2nv_TMP HFEnvq
+    #define MASK_GF2nv UINT_M1
 #endif
 
-/* Mask for arithmetic in GF(2^(n+v)) */
-#define MASK_GF2nv maskUINT(HFEnvr)
-
 #define HFEnvq8 (HFEnv>>3)
 #define HFEnvr8 (HFEnv&7)
 #define MASK8_GF2nv ((1U<<HFEnvr8)-1)
@@ -79,18 +79,17 @@
 
 
 
+#define set0_gf2nv(c) SET0((unsigned char *)(c),8*NB_WORD_GF2nv)
 
 #if (NB_WORD_GF2nv<7)
     #define add_gf2nv CONCAT(CONCAT_NB_WORD_GF2nv_SUP(ADD),_GF2X)
     #define add2_gf2nv CONCAT(CONCAT_NB_WORD_GF2nv_SUP(ADD),_2,_GF2X)
     #define swap_gf2nv CONCAT_NB_WORD_GF2nv_SUP(SWAP)
-    #define set0_gf2nv CONCAT_NB_WORD_GF2nv_SUP(SET0_)
     #define xorLoadMask1_gf2nv CONCAT_NB_WORD_GF2nv_SUP(XORLOADMASK1_)
 #else
     #define add_gf2nv(a,b,c) ADD_GF2X(a,b,c,NB_WORD_GF2nv)
     #define add2_gf2nv(a,b) ADD_2_GF2X(a,b,NB_WORD_GF2nv)
     #define swap_gf2nv(a,b) SWAP(XOR_2,a,b,NB_WORD_GF2nv)
-    #define set0_gf2nv(c) SET0(c,NB_WORD_GF2nv)
     #define xorLoadMask1_gf2nv(res,a,b) XORLOADMASK1(res,a,b,NB_WORD_GF2nv)
 #endif
 

