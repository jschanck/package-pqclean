--- upstream/Reference_Implementation/sign/GeMSS128/include/mul_gf2n.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/mul_gf2n.h
@@ -60,11 +60,7 @@
 
 
 /* Function mul in GF(2^x), then modular reduction */
-#define MUL_THEN_REM_GF2N void \
-            PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], \
-                                    const uint64_t A[NB_WORD_GFqn], \
-                                    const uint64_t B[NB_WORD_GFqn])
-MUL_THEN_REM_GF2N;
+void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn]);
 #define mul_then_rem_gf2n PREFIX_NAME(mul_then_rem_gf2n)
 
 
