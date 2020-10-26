--- upstream/Optimized_Implementation/hqc-rmrs-256/src/gf2x.h
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-256/src/gf2x.h
@@ -6,8 +6,15 @@
  * @brief Header file for gf2x.c
  */
 
+#include "parameters.h"
+#include <immintrin.h>
 #include <stdint.h>
 
-void vect_mul(uint64_t *o, const uint64_t *v1, const uint64_t *v2);
+typedef union {
+  uint64_t arr64[VEC_N_256_SIZE_64];
+  __m256i dummy;
+} aligned_vec_t;
+
+void vect_mul(uint64_t *o, const aligned_vec_t *a1, const aligned_vec_t *a2);
 
 #endif

