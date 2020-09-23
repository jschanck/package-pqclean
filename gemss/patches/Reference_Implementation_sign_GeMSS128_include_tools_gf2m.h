--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/tools_gf2m.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/tools_gf2m.h
@@ -75,18 +75,18 @@
 
 #define isEqual_gf2m(a,b) f_ISEQUAL(a,b,NB_WORD_GF2m)
 
+#define set0_gf2m(c) SET0((unsigned char *)c,8*NB_WORD_GF2m)
+
 #if (NB_WORD_GF2m<7)
     #define add_gf2m CONCAT(CONCAT_NB_WORD_GF2m_SUP(ADD),_GF2X)
     #define add2_gf2m CONCAT(CONCAT_NB_WORD_GF2m_SUP(ADD),_2_GF2X)
     #define copy_gf2m CONCAT_NB_WORD_GF2m_SUP(COPY)
-    #define set0_gf2m CONCAT_NB_WORD_GF2m_SUP(SET0_)
     #define xorLoadMask1_gf2m CONCAT_NB_WORD_GF2m_SUP(XORLOADMASK1_)
     #define dotProduct_gf2_m CONCAT_NB_WORD_GF2m_SUP(DOTPRODUCT)
 #else
     #define add_gf2m(a,b,c) ADD_GF2X(a,b,c,NB_WORD_GF2m); 
     #define add2_gf2m(a,b) ADD_2_GF2X(a,b,NB_WORD_GF2m); 
     #define copy_gf2m(c,a) COPY(c,a,NB_WORD_GF2m)
-    #define set0_gf2m(c) SET0(c,NB_WORD_GF2m)
     #define xorLoadMask1_gf2m(res,a,b) XORLOADMASK1(res,a,b,NB_WORD_GF2m)
     #define dotProduct_gf2_m(res,a,b) DOTPRODUCT(res,a,b,NB_WORD_GF2m)
 #endif

