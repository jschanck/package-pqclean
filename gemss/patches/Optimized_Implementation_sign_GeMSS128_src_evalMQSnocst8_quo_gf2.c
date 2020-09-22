--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/evalMQSnocst8_quo_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/evalMQSnocst8_quo_gf2.c
@@ -1,4 +1,4 @@
-#include "evalMQSnocst8_gf2.h"
+#include "evalMQSnocst8_quo_gf2.h"
 #include "add_gf2x.h"
 #include "init.h"
 #include "simd.h"
@@ -117,7 +117,7 @@
 
 
 #define LOOPJR_NOCST_64(START,NB_IT) \
-    for(jr=START;jr<NB_IT;++jr)\
+    for(jr=(START);jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\
@@ -134,7 +134,7 @@
 #else
 
 #define LOOPJR_UNROLLED_64(START,NB_IT) \
-    for(jr=START;jr<(NB_IT-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
+    for(jr=(START);jr<((NB_IT)-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
     {\
         for(h=0;h<LEN_UNROLLED_64;++h)\
         {\
@@ -146,7 +146,7 @@
             xj>>=1;\
         }\
     }\
-    for(;jr<NB_IT;++jr)\
+    for(;jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\

