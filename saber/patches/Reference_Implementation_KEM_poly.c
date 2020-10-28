--- upstream/Reference_Implementation_KEM/poly.c
+++ upstream-patched/Reference_Implementation_KEM/poly.c
@@ -1,61 +1,64 @@
-#include <stdio.h>
+#include <stddef.h>
 #include "api.h"
 #include "poly.h"
-#include "poly_mul.h"
 #include "pack_unpack.h"
 #include "cbd.h"
 #include "fips202.h"
 
-void MatrixVectorMul(const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose)
+void MatrixVectorMul(poly c[SABER_L], const poly A[SABER_L][SABER_L], const poly s[SABER_L], int16_t transpose)
 {
-	int i, j;
-	for (i = 0; i < SABER_L; i++)
-	{
-		for (j = 0; j < SABER_L; j++)
-		{
-			if (transpose == 1)
-			{
-				poly_mul_acc(A[j][i], s[j], res[i]);
+	size_t i, j;
+
+	if(transpose){
+		for(i=0;i<SABER_L;i++){
+			poly_mul(&c[i], &A[0][i], &s[0], 0);
+			for(j=1;j<SABER_L;j++){
+				poly_mul(&c[i], &A[j][i], &s[j], 1);
+			}
+		}
+	}else{
+		for(i=0;i<SABER_L;i++){
+			poly_mul(&c[i], &A[i][0], &s[0], 0);
+			for(j=1;j<SABER_L;j++){
+				poly_mul(&c[i], &A[i][j], &s[j], 1);
 			}
-			else
-			{
-				poly_mul_acc(A[i][j], s[j], res[i]);
-			}	
 		}
 	}
 }
 
-void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N])
+void InnerProd(poly *c, const poly b[SABER_L], const poly s[SABER_L])
 {
-	int j;
-	for (j = 0; j < SABER_L; j++)
+	size_t i;
+
+	poly_mul(c, &b[0], &s[0], 0);
+	for (i = 1; i < SABER_L; i++)
 	{
-		poly_mul_acc(b[j], s[j], res);
+		poly_mul(c, &b[i], &s[i], 1);
 	}
 }
 
-void GenMatrix(uint16_t A[SABER_L][SABER_L][SABER_N], const uint8_t seed[SABER_SEEDBYTES])
+void GenMatrix(poly A[SABER_L][SABER_L], const uint8_t seed[SABER_SEEDBYTES])
 {
+	size_t i;
 	uint8_t buf[SABER_L * SABER_POLYVECBYTES];
-	int i;
 
 	shake128(buf, sizeof(buf), seed, SABER_SEEDBYTES);
 
-	for (i = 0; i < SABER_L; i++)
+	for(i=0;i<SABER_L;i++)
 	{
-		BS2POLVECq(buf + i * SABER_POLYVECBYTES, A[i]);
+		BS2POLVECq(A[i], buf + i * SABER_POLYVECBYTES);
 	}
 }
 
-void GenSecret(uint16_t s[SABER_L][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES])
+void GenSecret(poly s[SABER_L], const uint8_t seed[SABER_NOISESEEDBYTES])
 {
-	uint8_t buf[SABER_L * SABER_POLYCOINBYTES];
 	size_t i;
+	uint8_t buf[SABER_L * SABER_POLYCOINBYTES];
 
-	shake128(buf, sizeof(buf), seed, SABER_NOISE_SEEDBYTES);
+	shake128(buf, sizeof(buf), seed, SABER_NOISESEEDBYTES);
 
-	for (i = 0; i < SABER_L; i++)
+	for(i=0;i<SABER_L;i++)
 	{
-		cbd(s[i], buf + i * SABER_POLYCOINBYTES);
+		cbd(s[i].coeffs, buf+i*SABER_POLYCOINBYTES);
 	}
 }

