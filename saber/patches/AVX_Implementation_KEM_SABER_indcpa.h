--- upstream/AVX_Implementation_KEM/SABER_indcpa.h
+++ upstream-patched/AVX_Implementation_KEM/SABER_indcpa.h
@@ -1,29 +1,11 @@
 #ifndef INDCPA_H
 #define INDCPA_H
 
-#include <immintrin.h>
-#include"cpucycles.h"
-#include"poly.h"
+#include "SABER_params.h"
+#include <stdint.h>
 
-void indcpa_keypair(unsigned char *pk, unsigned char *sk);
-
-void GenMatrix(polyvec *a, const unsigned char *seed);
-
-void indcpa_client(unsigned char *pk, unsigned char *b_prime, unsigned char *c, unsigned char *key);
-
-void indcpa_server(unsigned char *pk, unsigned char *b_prime, unsigned char *c, unsigned char *key);
-
-void indcpa_kem_keypair(unsigned char *pk, unsigned char *sk);
-void indcpa_kem_enc(unsigned char *message, unsigned char *noiseseed, const unsigned char *pk, unsigned char *ciphertext);
-void indcpa_kem_dec(const unsigned char *sk, const unsigned char *ciphertext, unsigned char *message_dec);
-
-//uint64_t clock1,clock2;
-
-uint64_t clock_kp_kex, clock_enc_kex, clock_dec_kex;
-
-uint64_t clock_kp_temp;
-
-__m256i mask,inv3_avx,inv9_avx,inv15_avx,int45_avx,int30_avx,int0_avx;
+void indcpa_kem_keypair(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES]);
+void indcpa_kem_enc(uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t m[SABER_KEYBYTES], const uint8_t noiseseed[SABER_NOISESEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES]);
+void indcpa_kem_dec(uint8_t m[SABER_KEYBYTES], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC]);
 
 #endif
-

