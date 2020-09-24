--- upstream/Optimized_Implementation/sign/GeMSS128/src/evalMQSnocst8_quo_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/evalMQSnocst8_quo_gf2.c
@@ -1,4 +1,4 @@
-#include "evalMQSnocst8_gf2.h"
+#include "evalMQSnocst8_quo_gf2.h"
 #include "add_gf2x.h"
 #include "init.h"
 #include "simd.h"
@@ -49,7 +49,7 @@
     #define NB_BYTES_EQ NB_EQq
 #endif
 
-#define MASK_EQ mask64(NB_EQ&63)
+#define MASK_EQ ((UINT_1<<(NB_EQ&63))-UINT_1)
 #if (NB_EQ&63)
     #define MASK_64(c) (c)&=MASK_EQ;
     #define MASK2_64(c,a) (c)=(a)&MASK_EQ;
@@ -89,68 +89,45 @@
 
 #define CONCAT_NB_WORD_EQ_SUP(name) CONCAT(name,NB_WORD_EQ)
 
-
-
 /*** Tuning ***/
 #define LEN_UNROLLED_64 4
 
-
-
-
-
-
-
 /* 64-bit version */
-
-#if (NB_WORD_EQ<7)
-    #define XOR_ELEM CONCAT(CONCAT_NB_WORD_EQ_SUP(ADD),_2_GF2X)
-#else
-    #define XOR_ELEM(a,b) ADD_2_GF2X(a,b,NB_WORD_EQ);
-#endif
-
-#if (NB_WORD_EQ<10)
-    #define COPY_64bits_variables CONCAT_NB_WORD_EQ_SUP(COPY)
-#else
-    #define COPY_64bits_variables(c,a) COPY(c,a,NB_WORD_EQ)
-#endif
-
-
+#define XOR_ELEM(a,b) ADD_2_GF2X((unsigned char *)(a),(unsigned char *)(b),8*NB_WORD_EQ);
 
 #define LOOPJR_NOCST_64(START,NB_IT) \
-    for(jr=START;jr<NB_IT;++jr)\
+    for(jr=(START);jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\
-            XOR_ELEM(c,(const UINT*)pk);\
+            XOR_ELEM(c,pk);\
         }\
         pk+=NB_BYTES_EQ;\
         xj>>=1;\
     }
 
-
-
 #if (LEN_UNROLLED_64==1)
     #define LOOPJR_UNROLLED_64 LOOPJR_NOCST_64
 #else
 
 #define LOOPJR_UNROLLED_64(START,NB_IT) \
-    for(jr=START;jr<(NB_IT-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
+    for(jr=(START);jr<((NB_IT)-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
     {\
         for(h=0;h<LEN_UNROLLED_64;++h)\
         {\
             if(xj&UINT_1)\
             {\
-                XOR_ELEM(c,(const UINT*)pk);\
+                XOR_ELEM(c,pk);\
             }\
             pk+=NB_BYTES_EQ;\
             xj>>=1;\
         }\
     }\
-    for(;jr<NB_IT;++jr)\
+    for(;jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\
-            XOR_ELEM(c,(const UINT*)pk);\
+            XOR_ELEM(c,pk);\
         }\
         pk+=NB_BYTES_EQ;\
         xj>>=1;\
@@ -172,7 +149,7 @@
     #endif
 
     /* Constant cst_pk */
-    COPY_64bits_variables(c,(const UINT*)pk);
+    LOAD_UINT_ARRAY(c, pk, NB_WORD_EQ)
     pk+=NB_BYTES_EQ;
 
     /* for each row of the quadratic matrix of pk, excepted the last block */
@@ -186,7 +163,7 @@
                 /* for each column of the quadratic matrix of pk */
 
                 /* xj=xi=1 */
-                XOR_ELEM(c,(const UINT*)pk);
+                XOR_ELEM(c,pk);
                 pk+=NB_BYTES_EQ;
 
                 xj=xi>>1;
@@ -222,7 +199,7 @@
                 /* for each column of the quadratic matrix of pk */
 
                 /* xj=xi=1 */
-                XOR_ELEM(c,(const UINT*)pk);
+                XOR_ELEM(c,pk);
                 pk+=NB_BYTES_EQ;
 
                 xj=xi>>1;

