--- upstream/Reference_Implementation_KEM/poly.c
+++ upstream-patched/Reference_Implementation_KEM/poly.c
@@ -6,7 +6,7 @@
 #include "cbd.h"
 #include "fips202.h"
 
-void MatrixVectorMul(const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose)
+void MatrixVectorMul(uint16_t res[SABER_L][SABER_N], const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], int16_t transpose)
 {
 	int i, j;
 	for (i = 0; i < SABER_L; i++)
@@ -25,7 +25,7 @@
 	}
 }
 
-void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N])
+void InnerProd(uint16_t res[SABER_N], const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N])
 {
 	int j;
 	for (j = 0; j < SABER_L; j++)
@@ -43,7 +43,7 @@
 
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLVECq(buf + i * SABER_POLYVECBYTES, A[i]);
+		BS2POLVECq(A[i], buf + i * SABER_POLYVECBYTES);
 	}
 }
 

