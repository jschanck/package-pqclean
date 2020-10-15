--- upstream/Reference_Implementation_KEM/poly.h
+++ upstream-patched/Reference_Implementation_KEM/poly.h
@@ -4,8 +4,8 @@
 #include <stdint.h>
 #include "SABER_params.h"
 
-void MatrixVectorMul(const uint16_t a[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose);
-void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N]);
+void MatrixVectorMul(uint16_t res[SABER_L][SABER_N], const uint16_t a[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], int16_t transpose);
+void InnerProd(uint16_t res[SABER_N], const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N]);
 void GenMatrix(uint16_t a[SABER_L][SABER_L][SABER_N], const uint8_t seed[SABER_SEEDBYTES]);
 void GenSecret(uint16_t s[SABER_L][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES]);
 

