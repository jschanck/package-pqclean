--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/determinantnv_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/determinantnv_gf2.c
@@ -44,7 +44,7 @@
 
 #define LOOPIR(NB_IT,LOOPK1,LOOPK2) \
     bit_ir=1;\
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* If the pivot is 0, search the pivot */\
         if(!((*S_cpi)&bit_ir))\
@@ -117,7 +117,12 @@
 
     /* We know there are 1 on diagonal excepted for the last line */
     bit_ir&=*S_cpi;
-    return bit_ir?1:0;
+    if (bit_ir) {
+      bit_ir = 1;
+    } else {
+      bit_ir = 0;
+    }
+    return bit_ir;
 }
 
 
@@ -133,7 +138,7 @@
     }
 
 #define LOOPIR_CST(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* row i += (1-pivot_i)* row j */\
         LOOPJ_CST({mask=(-(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\

