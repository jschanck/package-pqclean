--- upstream/Optimized_Implementation/hqc-rmrs-192/src/gf2x.h
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-192/src/gf2x.h
@@ -8,6 +8,6 @@
 
 #include <stdint.h>
 
-void vect_mul(uint64_t *o, const uint64_t *v1, const uint64_t *v2);
+void vect_mul(uint64_t *o, const uint64_t *a1, const uint64_t *a2);
 
 #endif

