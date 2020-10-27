--- upstream/ref/reduce.c
+++ upstream-patched/ref/reduce.c
@@ -19,11 +19,11 @@
   int32_t t;
   int16_t u;
 
-  u = a*QINV;
+  u = (int16_t)(a*(int64_t)QINV);
   t = (int32_t)u*KYBER_Q;
   t = a - t;
   t >>= 16;
-  return t;
+  return (int16_t)t;
 }
 
 /*************************************************

