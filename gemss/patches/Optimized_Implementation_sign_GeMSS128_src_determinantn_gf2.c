--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/determinantn_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/determinantn_gf2.c
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
 
 

