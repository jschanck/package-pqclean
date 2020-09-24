--- upstream/Reference_Implementation/sign/GeMSS128/include/sqr_gf2n.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/sqr_gf2n.h
@@ -36,14 +36,8 @@
 
 
 /* Function sqr in GF(2^x), then modular reduction */
-#define SQR_THEN_REM_GF2N void \
-            PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], \
-                                     const uint64_t A[NB_WORD_GFqn])
-#define SQR_NOCST_THEN_REM_GF2N void \
-            PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], \
-                                           const uint64_t A[NB_WORD_GFqn])
-SQR_THEN_REM_GF2N;
-SQR_NOCST_THEN_REM_GF2N;
+void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn]);
+void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn]);
 #define sqr_then_rem_gf2n PREFIX_NAME(sqr_then_rem_gf2n)
 #define sqr_nocst_then_rem_gf2n PREFIX_NAME(sqr_nocst_then_rem_gf2n)
 

