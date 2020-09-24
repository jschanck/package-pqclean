--- upstream/Optimized_Implementation/sign/GeMSS128/include/tools_gf2v.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/tools_gf2v.h
@@ -12,8 +12,11 @@
 /* The number of word that an element of GF(2^v) needs */
 #if (HFEvr)
     #define NB_WORD_GFqv_TMP (HFEvq+1)
+    /* Mask for arithmetic in GF(2^v) */
+    #define HFE_MASKv ((UINT_1<<(HFEvr))-UINT_1)
 #else
     #define NB_WORD_GFqv_TMP HFEvq
+    #define HFE_MASKv UINT_M1
 #endif
 
 #if (NB_WORD_GFqv_TMP == 1)
@@ -24,10 +27,6 @@
     #define NB_WORD_GFqv NB_WORD_GFqv_TMP
 #endif
 
-
-/* Mask for arithmetic in GF(2^v) */
-#define HFE_MASKv maskUINT(HFEvr)
-
 #define HFEvr8 (HFEv&7)
 /* Number of bytes that an element of GF(2^(n+v)) needs */
 #define NB_BYTES_GFqv ((HFEv>>3)+((HFEvr8)?1:0))

