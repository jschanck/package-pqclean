--- upstream/Optimized_Implementation/sign/GeMSS128/include/parameters_HFE.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/parameters_HFE.h
@@ -11,9 +11,6 @@
     #define GFq 2U
     #define Log2_q 1
     /* For HFE, the previous parameter is necessarily 2. */
-
-    /** This type stores an element of GF(q). */
-    typedef unsigned char gf2;
 #endif
 
 

