--- upstream/ref/poly.h
+++ upstream-patched/ref/poly.h
@@ -25,7 +25,7 @@
 #define poly_frommsg KYBER_NAMESPACE(poly_frommsg)
 void poly_frommsg(poly *r, const uint8_t msg[KYBER_INDCPA_MSGBYTES]);
 #define poly_tomsg KYBER_NAMESPACE(poly_tomsg)
-void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], const poly *r);
+void poly_tomsg(uint8_t msg[KYBER_INDCPA_MSGBYTES], const poly *a);
 
 #define poly_getnoise_eta1 KYBER_NAMESPACE(poly_getnoise_eta1)
 void poly_getnoise_eta1(poly *r, const uint8_t seed[KYBER_SYMBYTES], uint8_t nonce);

