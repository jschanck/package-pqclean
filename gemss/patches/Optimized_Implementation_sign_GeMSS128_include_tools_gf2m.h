--- upstream/Optimized_Implementation/sign/GeMSS128/include/tools_gf2m.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/tools_gf2m.h
@@ -25,12 +25,13 @@
 /* The number of word that an element of GF(2^m) needs */
 #if (HFEmr)
     #define NB_WORD_GF2m_TMP (HFEmq+1)
+    /* Mask to truncate the last word */
+    #define MASK_GF2m ((UINT_1<<(HFEmr))-UINT_1)
 #else
     #define NB_WORD_GF2m_TMP HFEmq
+    #define MASK_GF2m UINT_M1
 #endif
 
-/* Mask to truncate the last word */
-#define MASK_GF2m maskUINT(HFEmr)
 
 #define HFEmq8 (HFEm>>3)
 #define HFEmr8 (HFEm&7U)
@@ -75,19 +76,18 @@
 
 #define isEqual_gf2m(a,b) f_ISEQUAL(a,b,NB_WORD_GF2m)
 
+#define set0_gf2m(c) SET0((unsigned char *)(c),8*NB_WORD_GF2m)
+#define xorLoadMask1_gf2m(res,a,b) XORLOADMASK1((unsigned char *)(res),(unsigned char *)(a),b,8*NB_WORD_GF2m)
+
 #if (NB_WORD_GF2m<7)
     #define add_gf2m CONCAT(CONCAT_NB_WORD_GF2m_SUP(ADD),_GF2X)
     #define add2_gf2m CONCAT(CONCAT_NB_WORD_GF2m_SUP(ADD),_2_GF2X)
     #define copy_gf2m CONCAT_NB_WORD_GF2m_SUP(COPY)
-    #define set0_gf2m CONCAT_NB_WORD_GF2m_SUP(SET0_)
-    #define xorLoadMask1_gf2m CONCAT_NB_WORD_GF2m_SUP(XORLOADMASK1_)
     #define dotProduct_gf2_m CONCAT_NB_WORD_GF2m_SUP(DOTPRODUCT)
 #else
     #define add_gf2m(a,b,c) ADD_GF2X(a,b,c,NB_WORD_GF2m); 
     #define add2_gf2m(a,b) ADD_2_GF2X(a,b,NB_WORD_GF2m); 
     #define copy_gf2m(c,a) COPY(c,a,NB_WORD_GF2m)
-    #define set0_gf2m(c) SET0(c,NB_WORD_GF2m)
-    #define xorLoadMask1_gf2m(res,a,b) XORLOADMASK1(res,a,b,NB_WORD_GF2m)
     #define dotProduct_gf2_m(res,a,b) DOTPRODUCT(res,a,b,NB_WORD_GF2m)
 #endif
 

