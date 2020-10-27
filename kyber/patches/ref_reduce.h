--- upstream/ref/reduce.h
+++ upstream-patched/ref/reduce.h
@@ -14,6 +14,6 @@
 int16_t barrett_reduce(int16_t a);
 
 #define csubq KYBER_NAMESPACE(_csubq)
-int16_t csubq(int16_t x);
+int16_t csubq(int16_t a);
 
 #endif

