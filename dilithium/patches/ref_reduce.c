--- upstream/ref/reduce.c
+++ upstream-patched/ref/reduce.c
@@ -15,7 +15,7 @@
 int32_t montgomery_reduce(int64_t a) {
   int32_t t;
 
-  t = (int64_t)(int32_t)a*QINV;
+  t = (int32_t)((uint64_t)a*(uint64_t)QINV);
   t = (a - (int64_t)t*Q) >> 32;
   return t;
 }

