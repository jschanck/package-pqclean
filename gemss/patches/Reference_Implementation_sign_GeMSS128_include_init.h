--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/init.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/init.h
@@ -116,23 +116,23 @@
 
 #define SET1_2(c) \
     SET1_1(c);\
-    SET0_1(c+1);
+    SET0_1((c)+1);
 
 #define SET1_3(c) \
     SET1_1(c);\
-    SET0_2(c+1);
+    SET0_2((c)+1);
 
 #define SET1_4(c) \
     SET1_1(c);\
-    SET0_3(c+1);
+    SET0_3((c)+1);
 
 #define SET1_5(c) \
     SET1_1(c);\
-    SET0_4(c+1);
+    SET0_4((c)+1);
 
 #define SET1_6(c) \
     SET1_1(c);\
-    SET0_5(c+1);
+    SET0_5((c)+1);
 
 
 #endif

