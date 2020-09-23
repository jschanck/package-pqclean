--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/include/tools_gf2nv.h
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/include/tools_gf2nv.h
@@ -79,18 +79,17 @@
 
 
 
+#define set0_gf2nv(c) SET0((unsigned char *)c,8*NB_WORD_GF2nv)
 
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
 

