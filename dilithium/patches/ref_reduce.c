--- upstream/ref/reduce.c
+++ upstream-patched/ref/reduce.c
@@ -13,11 +13,14 @@
 * Returns r.
 **************************************************/
 int32_t montgomery_reduce(int64_t a) {
-  int32_t t;
+  int64_t t;
+  int32_t u;
 
-  t = (int32_t)a*QINV;
-  t = (a - (int64_t)t*Q) >> 32;
-  return t;
+  u = (int32_t)(a*(int64_t)QINV);
+  t = (int64_t)u*Q;
+  t = a - t;
+  t >>= 32;
+  return (int32_t)t;
 }
 
 /*************************************************

