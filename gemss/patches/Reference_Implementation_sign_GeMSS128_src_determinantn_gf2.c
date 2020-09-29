--- upstream/Reference_Implementation/sign/GeMSS128/src/determinantn_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/determinantn_gf2.c
@@ -26,7 +26,7 @@
 
 #define ADDROW(LOOPK) \
         /* pivot */\
-        pivot=-(((*S_cpj)>>ir)&1);\
+        pivot=1+~((((*S_cpj)>>ir)&1));\
         LOOPK;
 
 
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
+    return (gf2) bit_ir;
 }
 
 
@@ -133,10 +138,10 @@
     }
 
 #define LOOPIR_CST(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* row i += (1-pivot_i)* row j */\
-        LOOPJ_CST({mask=(-(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\
+        LOOPJ_CST({mask=(1+~(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\
                         LOOPK(XORLOADMASK1_1(S_cpi+k,S_cpj+k,mask);)});\
 \
         /* Here, the pivot is 1 if S is invertible */\
@@ -158,7 +163,7 @@
            algorithm. */\
 \
         /* row j += (pivot_j) * row_i */\
-        LOOPJ_CST({mask=(-(((*S_cpj)>>ir)&UINT_1));\
+        LOOPJ_CST({mask=(1+~(((*S_cpj)>>ir)&UINT_1));\
                         LOOPK(XORLOADMASK1_1(S_cpj+k,S_cpi+k,mask);)});\
 \
         /* Next row */\
@@ -214,7 +219,7 @@
         det_i&=(*S_cpi)>>ir;
     #endif
 
-    return det_i;
+    return (gf2) det_i;
 }
 
 

