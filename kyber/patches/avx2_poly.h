--- upstream/avx2/poly.h
+++ upstream-patched/avx2/poly.h
@@ -1,6 +1,7 @@
 #ifndef POLY_H
 #define POLY_H
 
+#include <immintrin.h>
 #include <stdint.h>
 #include "params.h"
 
@@ -8,8 +9,9 @@
  * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
  * coeffs[0] + X*coeffs[1] + X^2*xoeffs[2] + ... + X^{n-1}*coeffs[n-1]
  */
-typedef struct{
-  int16_t coeffs[KYBER_N] __attribute__((aligned(32)));
+typedef union{
+  __m256i dummy;
+  int16_t coeffs[KYBER_N];
 } poly;
 
 #define poly_compress KYBER_NAMESPACE(_poly_compress)
@@ -25,7 +27,7 @@
 #define poly_frommsg KYBER_NAMESPACE(_poly_frommsg)
 void poly_frommsg(poly *r, const uint8_t msg[KYBER_INDCPA_MSGBYTES]);
 #define poly_tomsg KYBER_NAMESPACE(_poly_tomsg)
-void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], poly *r);
+void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], poly *a);
 
 #define poly_getnoise_eta2 KYBER_NAMESPACE(_poly_getnoise_eta2)
 void poly_getnoise_eta2(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint8_t nonce);
@@ -52,6 +54,7 @@
                      uint8_t nonce1,
                      uint8_t nonce2,
                      uint8_t nonce3);
+#define poly_getnoise_eta1122_4x KYBER_NAMESPACE(_poly_getnoise_eta1122_4x)
 void poly_getnoise_eta1122_4x(poly *r0,
                      poly *r1,
                      poly *r2,

