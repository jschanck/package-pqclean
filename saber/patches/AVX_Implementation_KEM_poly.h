--- upstream/AVX_Implementation_KEM/poly.h
+++ upstream-patched/AVX_Implementation_KEM/poly.h
@@ -1,35 +1,32 @@
-/*---------------------------------------------------------------------
-This file has been adapted from the implementation 
-(available at, Public Domain https://github.com/pq-crystals/kyber) 
-of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
-by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
-Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
-----------------------------------------------------------------------*/
-
 #ifndef POLY_H
 #define POLY_H
 
+#include <immintrin.h>
 #include <stdint.h>
 #include "SABER_params.h"
 
-uint64_t clock_mul, clock_matrix, clock_secret, count_mul;
-
-uint64_t clock_mv_vv_mul;
-
-uint64_t count_enc;
-
-typedef struct
-{
-  uint16_t coeffs[SABER_N];
+typedef union {
+	uint16_t coeffs[SABER_N];
+	__m256i dummy;
 } poly;
 
-typedef struct{
-  poly vec[SABER_K];
-} polyvec;
-
-void poly_getnoise(uint16_t *r,const unsigned char *seed, unsigned char nonce);
-
-void poly_getnoise4x(uint16_t *r0, uint16_t *r1, uint16_t *r2, const unsigned char *seed, unsigned char nonce0, unsigned char nonce1, unsigned char nonce2, unsigned char nonce3);
-
+typedef union {
+	uint16_t coeffs[4*SABER_N];
+	__m256i dummy;
+} toom4_points;
+
+typedef union {
+	uint16_t coeffs[8*SABER_N];
+	__m256i dummy;
+} toom4_points_product;
+
+void MatrixVectorMul(poly c[SABER_L], const poly A[SABER_L][SABER_L], const toom4_points s_eval[SABER_L], int transpose);
+void InnerProd(poly *c, const poly b[SABER_L], const toom4_points s_eval[SABER_L]);
+void GenMatrix(poly a[SABER_L][SABER_L], const uint8_t seed[SABER_SEEDBYTES]);
+void GenSecret(poly s[SABER_L], const uint8_t seed[SABER_NOISESEEDBYTES]);
+
+void toom4_interp(poly *res_avx, const toom4_points_product *c_eval);
+void toom4_eval(toom4_points *b_eval, const poly *b);
+void toom4_mul_A_by_B_eval(toom4_points_product *c_eval, const poly *a_avx, const toom4_points *b_eval, int accumulate);
 
 #endif

