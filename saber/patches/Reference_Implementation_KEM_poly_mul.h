--- upstream/Reference_Implementation_KEM/poly_mul.h
+++ upstream-patched/Reference_Implementation_KEM/poly_mul.h
@@ -4,6 +4,6 @@
 #include "SABER_params.h"
 #include <stdint.h>
 
-void poly_mul_acc(const uint16_t a[SABER_N], const uint16_t b[SABER_N], uint16_t res[SABER_N]);
+void poly_mul_acc(uint16_t res[SABER_N], const uint16_t a[SABER_N], const uint16_t b[SABER_N]);
 
-#endif
\ No newline at end of file
+#endif

