--- upstream/Optimized_Implementation/sign/GeMSS128/include/tools_gf2n.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/tools_gf2n.h
@@ -52,13 +52,13 @@
 /* The number of word that an element of GF(2^n) needs */
 #if (HFEnr)
     #define NB_WORD_GFqn_TMP (HFEnq+1)
+    /* Mask for arithmetic in GF(2^n) */
+    #define MASK_GF2n ((UINT_1<<(HFEnr))-UINT_1)
 #else
     #define NB_WORD_GFqn_TMP HFEnq
+    #define MASK_GF2n UINT_M1
 #endif
 
-/* Mask for arithmetic in GF(2^n) */
-#define MASK_GF2n maskUINT(HFEnr)
-
 #define HFEnr8 (HFEn&7)
 #define MASK8_GF2n ((1U<<HFEnr8)-1)
 /* Number of bytes that an element of GF(2^n) needs */
@@ -112,16 +112,16 @@
 #define cmp_lt_gf2n(a,b) f_CMP_LT(a,b,NB_WORD_GFqn)
 #define cmp_gt_gf2n(a,b) f_CMP_GT(a,b,NB_WORD_GFqn)
 
+#define set0_gf2n(c) SET0((unsigned char *)(c),8*NB_WORD_GFqn)
+
 #if (NB_WORD_GFqn<7)
     #define swap_gf2n CONCAT_NB_WORD_GFqn_SUP(SWAP)
     #define copy_gf2n CONCAT_NB_WORD_GFqn_SUP(COPY)
-    #define set0_gf2n CONCAT_NB_WORD_GFqn_SUP(SET0_)
     #define set1_gf2n CONCAT_NB_WORD_GFqn_SUP(SET1_)
     #define xorLoadMask1_gf2n CONCAT_NB_WORD_GFqn_SUP(XORLOADMASK1_)
 #else
     #define swap_gf2n(a,b) SWAP(XOR_2,a,b,NB_WORD_GFqn)
     #define copy_gf2n(c,a) COPY(c,a,NB_WORD_GFqn)
-    #define set0_gf2n(c) SET0(c,NB_WORD_GFqn)
     #define set1_gf2n(c) SET1(c,NB_WORD_GFqn)
     #define xorLoadMask1_gf2n(res,a,b) XORLOADMASK1(res,a,b,NB_WORD_GFqn)
 #endif
@@ -328,11 +328,7 @@
 
 
 
-#if (NB_WORD_MMUL<7)
-    #define set0_product_gf2n CONCAT_NB_WORD_MMUL(SET0_)
-#else
-    #define set0_product_gf2n(c) SET0(c,NB_WORD_MMUL)
-#endif
+#define set0_product_gf2n(c) SET0((unsigned char*)(c),8*NB_WORD_MMUL)
 
 #if (NB_WORD_MMUL==NB_WORD_GFqn)
     /* Nothing to set to 0 */

