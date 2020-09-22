--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/evalMQSnocst8_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/evalMQSnocst8_gf2.c
@@ -103,7 +103,7 @@
 
 
 #define LOOPJR_NOCST_64(START,NB_IT) \
-    for(jr=START;jr<NB_IT;++jr)\
+    for(jr=(START);jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\
@@ -120,7 +120,7 @@
 #else
 
 #define LOOPJR_UNROLLED_64(START,NB_IT) \
-    for(jr=START;jr<(NB_IT-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
+    for(jr=(START);jr<((NB_IT)-LEN_UNROLLED_64+1);jr+=LEN_UNROLLED_64)\
     {\
         for(h=0;h<LEN_UNROLLED_64;++h)\
         {\
@@ -132,7 +132,7 @@
             xj>>=1;\
         }\
     }\
-    for(;jr<NB_IT;++jr)\
+    for(;jr<(NB_IT);++jr)\
     {\
         if(xj&UINT_1)\
         {\

