--- upstream/AVX_Implementation_KEM/poly.c
+++ upstream-patched/AVX_Implementation_KEM/poly.c
@@ -0,0 +1,67 @@
+#include "cbd.h"
+#include "poly.h"
+#include "pack_unpack.h"
+#include "fips202.h"
+
+void MatrixVectorMul(poly c[SABER_L], const poly A[SABER_L][SABER_L], const toom4_points s_eval[SABER_L], int transpose)
+{
+	size_t i,j;
+	toom4_points_product c_eval;
+
+	if(transpose){
+		for(i=0;i<SABER_L;i++){
+			toom4_mul_A_by_B_eval(&c_eval, &A[0][i], &s_eval[0], 0);
+			for(j=1;j<SABER_L;j++){
+				toom4_mul_A_by_B_eval(&c_eval, &A[j][i], &s_eval[j], 1);
+			}
+			toom4_interp(&c[i], &c_eval);
+		}
+	}else{
+		for(i=0;i<SABER_L;i++){
+			toom4_mul_A_by_B_eval(&c_eval, &A[i][0], &s_eval[0], 0);
+			for(j=1;j<SABER_L;j++){
+				toom4_mul_A_by_B_eval(&c_eval, &A[i][j], &s_eval[j], 1);
+			}
+			toom4_interp(&c[i], &c_eval);
+		}
+	}
+}
+
+void InnerProd(poly *c, const poly b[SABER_L], const toom4_points s_eval[SABER_L])
+{
+	size_t i;
+	toom4_points_product c_eval; //Holds results for 9 Karatsuba at a time
+
+	toom4_mul_A_by_B_eval(&c_eval, &b[0], &s_eval[0], 0);
+	for(i=1;i<SABER_L;i++){
+		toom4_mul_A_by_B_eval(&c_eval, &b[i], &s_eval[i], 1);
+	}
+
+	toom4_interp(c, &c_eval);
+}
+
+void GenMatrix(poly A[SABER_L][SABER_L], const uint8_t seed[SABER_SEEDBYTES])
+{
+	size_t i;
+	uint8_t buf[SABER_L * SABER_POLYVECBYTES];
+
+	shake128(buf, sizeof(buf), seed, SABER_SEEDBYTES);
+
+	for(i=0;i<SABER_L;i++)
+	{
+		BS2POLVECq(A[i], buf + i * SABER_POLYVECBYTES);
+	}
+}
+
+void GenSecret(poly s[SABER_L], const uint8_t seed[SABER_NOISESEEDBYTES])
+{
+	size_t i;
+	uint8_t buf[SABER_L * SABER_POLYCOINBYTES];
+
+	shake128(buf, sizeof(buf), seed, SABER_NOISESEEDBYTES);
+
+	for(i=0;i<SABER_L;i++)
+	{
+		cbd(s[i].coeffs, buf+i*SABER_POLYCOINBYTES);
+	}
+}

