--- upstream/Reference_Implementation/hqc-rmrs-192/src/gf2x.h
+++ upstream-patched/Reference_Implementation/hqc-rmrs-192/src/gf2x.h
@@ -9,6 +9,6 @@
 #include "rng.h"
 #include <stdint.h>
 
-void vect_mul(uint64_t *o, const uint32_t *v1, const uint64_t *v2, const uint16_t weight, AES_XOF_struct *ctx);
+void vect_mul(uint64_t *o, const uint32_t *a1, const uint64_t *a2, uint16_t weight, AES_XOF_struct *ctx);
 
 #endif

