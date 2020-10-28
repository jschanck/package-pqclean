--- upstream/Reference_Implementation_KEM/poly.h
+++ upstream-patched/Reference_Implementation_KEM/poly.h
@@ -4,9 +4,16 @@
 #include <stdint.h>
 #include "SABER_params.h"
 
-void MatrixVectorMul(const uint16_t a[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose);
-void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N]);
-void GenMatrix(uint16_t a[SABER_L][SABER_L][SABER_N], const uint8_t seed[SABER_SEEDBYTES]);
-void GenSecret(uint16_t s[SABER_L][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES]);
+typedef union {
+  uint16_t coeffs[SABER_N];
+} poly;
+
+
+void MatrixVectorMul(poly c[SABER_L], const poly A[SABER_L][SABER_L], const poly s[SABER_L], int16_t transpose);
+void InnerProd(poly *c, const poly b[SABER_L], const poly s[SABER_L]);
+void GenMatrix(poly A[SABER_L][SABER_L], const uint8_t seed[SABER_SEEDBYTES]);
+void GenSecret(poly s[SABER_L], const uint8_t seed[SABER_NOISESEEDBYTES]);
+
+void poly_mul(poly *c, const poly *a, const poly *b, int accumulate);
 
 #endif

