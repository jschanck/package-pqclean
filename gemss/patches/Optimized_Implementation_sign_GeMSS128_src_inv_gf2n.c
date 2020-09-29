--- upstream/Optimized_Implementation/sign/GeMSS128/src/inv_gf2n.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/inv_gf2n.c
@@ -3,7 +3,6 @@
 #include "add_gf2n.h"
 #include "mul_gf2n.h"
 #include "sqr_gf2n.h"
-#include "rem_gf2x.h"
 #include "rem_gf2n.h"
 #include "ITMIA_addchains.h"
 
@@ -222,7 +221,7 @@
     /* res=res * res^(2^((HFEn-1)>>i)) */\
     /* res^(2^((HFEn-1)>>i)) */\
     PINIT_GF2N_(r_128_copy,r2_128_copy,r3_128_copy,r4_128_copy,r5_128_copy,r);\
-    for(j=0;j<val;++j)\
+    for(j=0;j<(val);++j)\
     {\
         SQR_GF2N_(r,r_128,r2_128,r3_128,r4_128,r5_128,ra,rem_function);\
     }\
@@ -266,6 +265,7 @@
  * in GF(2^n). However, the complexity of the squarings can be improved with
  * multi-squaring tables.
  */
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(inv_ITMIA_gf2n)(static_gf2n res[NB_WORD_GFqn],
                              cst_static_gf2n A[NB_WORD_GFqn])
 {

