--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/include/dotProduct_gf2.h
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/include/dotProduct_gf2.h
@@ -10,50 +10,50 @@
 
 /* Dot product of vector of bits */
 #define DOTPRODUCT(res,a,b,SIZE) \
-    res=(a)[0]&(b)[0];\
+    (res)=(a)[0]&(b)[0];\
     FOR_LOOP_COMPLETE(1,RESERVED_VARIABLE<(SIZE),++RESERVED_VARIABLE,\
-                        res^=(a)[RESERVED_VARIABLE]&(b)[RESERVED_VARIABLE])\
+                        (res)^=(a)[RESERVED_VARIABLE]&(b)[RESERVED_VARIABLE])\
     XORBITS_UINT(res);
 
 
 /* Inlined version */
 #define DOTPRODUCT1(res,a,b) \
-    res=(a)[0]&(b)[0];\
+    (res)=(a)[0]&(b)[0];\
     XORBITS_UINT(res);
 
 #define DOTPRODUCT2(res,a,b) \
-    res=(a)[0]&(b)[0];\
-    res^=(a)[1]&(b)[1];\
+    (res)=(a)[0]&(b)[0];\
+    (res)^=(a)[1]&(b)[1];\
     XORBITS_UINT(res);
 
 #define DOTPRODUCT3(res,a,b) \
-    res=(a)[0]&(b)[0];\
-    res^=(a)[1]&(b)[1];\
-    res^=(a)[2]&(b)[2];\
+    (res)=(a)[0]&(b)[0];\
+    (res)^=(a)[1]&(b)[1];\
+    (res)^=(a)[2]&(b)[2];\
     XORBITS_UINT(res);
 
 #define DOTPRODUCT4(res,a,b) \
-    res=(a)[0]&(b)[0];\
-    res^=(a)[1]&(b)[1];\
-    res^=(a)[2]&(b)[2];\
-    res^=(a)[3]&(b)[3];\
+    (res)=(a)[0]&(b)[0];\
+    (res)^=(a)[1]&(b)[1];\
+    (res)^=(a)[2]&(b)[2];\
+    (res)^=(a)[3]&(b)[3];\
     XORBITS_UINT(res);
 
 #define DOTPRODUCT5(res,a,b) \
-    res=(a)[0]&(b)[0];\
-    res^=(a)[1]&(b)[1];\
-    res^=(a)[2]&(b)[2];\
-    res^=(a)[3]&(b)[3];\
-    res^=(a)[4]&(b)[4];\
+    (res)=(a)[0]&(b)[0];\
+    (res)^=(a)[1]&(b)[1];\
+    (res)^=(a)[2]&(b)[2];\
+    (res)^=(a)[3]&(b)[3];\
+    (res)^=(a)[4]&(b)[4];\
     XORBITS_UINT(res);
 
 #define DOTPRODUCT6(res,a,b) \
-    res=(a)[0]&(b)[0];\
-    res^=(a)[1]&(b)[1];\
-    res^=(a)[2]&(b)[2];\
-    res^=(a)[3]&(b)[3];\
-    res^=(a)[4]&(b)[4];\
-    res^=(a)[5]&(b)[5];\
+    (res)=(a)[0]&(b)[0];\
+    (res)^=(a)[1]&(b)[1];\
+    (res)^=(a)[2]&(b)[2];\
+    (res)^=(a)[3]&(b)[3];\
+    (res)^=(a)[4]&(b)[4];\
+    (res)^=(a)[5]&(b)[5];\
     XORBITS_UINT(res);
 
 

