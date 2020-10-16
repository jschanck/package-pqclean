--- upstream/Reference_Implementation_KEM/poly.c
+++ upstream-patched/Reference_Implementation_KEM/poly.c
@@ -1,4 +1,4 @@
-#include <stdio.h>
+#include <stddef.h>
 #include "api.h"
 #include "poly.h"
 #include "poly_mul.h"
@@ -6,44 +6,44 @@
 #include "cbd.h"
 #include "fips202.h"
 
-void MatrixVectorMul(const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose)
+void MatrixVectorMul(uint16_t res[SABER_L][SABER_N], const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], int16_t transpose)
 {
-	int i, j;
+	size_t i, j;
 	for (i = 0; i < SABER_L; i++)
 	{
 		for (j = 0; j < SABER_L; j++)
 		{
 			if (transpose == 1)
 			{
-				poly_mul_acc(A[j][i], s[j], res[i]);
+				poly_mul_acc(res[i], A[j][i], s[j]);
 			}
 			else
 			{
-				poly_mul_acc(A[i][j], s[j], res[i]);
+				poly_mul_acc(res[i], A[i][j], s[j]);
 			}	
 		}
 	}
 }
 
-void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N])
+void InnerProd(uint16_t res[SABER_N], const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N])
 {
-	int j;
+	size_t j;
 	for (j = 0; j < SABER_L; j++)
 	{
-		poly_mul_acc(b[j], s[j], res);
+		poly_mul_acc(res, b[j], s[j]);
 	}
 }
 
 void GenMatrix(uint16_t A[SABER_L][SABER_L][SABER_N], const uint8_t seed[SABER_SEEDBYTES])
 {
 	uint8_t buf[SABER_L * SABER_POLYVECBYTES];
-	int i;
+	size_t i;
 
 	shake128(buf, sizeof(buf), seed, SABER_SEEDBYTES);
 
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLVECq(buf + i * SABER_POLYVECBYTES, A[i]);
+		BS2POLVECq(A[i], buf + i * SABER_POLYVECBYTES);
 	}
 }
 

