--- upstream/Reference_Implementation/sign/GeMSS128/src/evalMQSnocst8_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/evalMQSnocst8_gf2.c
@@ -35,7 +35,7 @@
     #define NB_BYTES_EQ NB_EQq
 #endif
 
-#define MASK_EQ mask64(NB_EQ&63)
+#define MASK_EQ ((UINT_1<<(NB_EQ&63))-UINT_1)
 #if (NB_EQ&63)
     #define MASK_64(c) (c)&=MASK_EQ;
     #define MASK2_64(c,a) (c)=(a)&MASK_EQ;
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

