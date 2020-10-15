--- upstream/AVX_Implementation_KEM/poly.h
+++ upstream-patched/AVX_Implementation_KEM/poly.h
@@ -12,12 +12,6 @@
 #include <stdint.h>
 #include "SABER_params.h"
 
-uint64_t clock_mul, clock_matrix, clock_secret, count_mul;
-
-uint64_t clock_mv_vv_mul;
-
-uint64_t count_enc;
-
 typedef struct
 {
   uint16_t coeffs[SABER_N];
@@ -31,5 +25,4 @@
 
 void poly_getnoise4x(uint16_t *r0, uint16_t *r1, uint16_t *r2, const unsigned char *seed, unsigned char nonce0, unsigned char nonce1, unsigned char nonce2, unsigned char nonce3);
 
-
 #endif

