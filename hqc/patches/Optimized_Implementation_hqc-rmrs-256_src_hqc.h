--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-256/src/hqc.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-256/src/hqc.h
@@ -9,7 +9,7 @@
 #include <stdint.h>
 
 void hqc_pke_keygen(unsigned char* pk, unsigned char* sk);
-void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint64_t *m, unsigned char *theta, const unsigned char *pk);
-void hqc_pke_decrypt(uint64_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk);
+void hqc_pke_encrypt(uint64_t *u, uint64_t *v, uint8_t *m, unsigned char *theta, const unsigned char *pk);
+void hqc_pke_decrypt(uint8_t *m, const uint64_t *u, const uint64_t *v, const unsigned char *sk);
 
 #endif

