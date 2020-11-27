--- upstream/avx2/poly.h
+++ upstream-patched/avx2/poly.h
@@ -1,6 +1,7 @@
 #ifndef POLY_H
 #define POLY_H
 
+#include <immintrin.h>
 #include <stdint.h>
 #include "align.h"
 #include "params.h"
@@ -20,7 +21,7 @@
 #define poly_frommsg KYBER_NAMESPACE(_poly_frommsg)
 void poly_frommsg(poly *r, const uint8_t msg[KYBER_INDCPA_MSGBYTES]);
 #define poly_tomsg KYBER_NAMESPACE(_poly_tomsg)
-void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], poly *r);
+void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], poly *a);
 
 #define poly_getnoise_eta1 KYBER_NAMESPACE(_poly_getnoise_eta1)
 void poly_getnoise_eta1(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint8_t nonce);

