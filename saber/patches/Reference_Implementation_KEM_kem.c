--- upstream/Reference_Implementation_KEM/kem.c
+++ upstream-patched/Reference_Implementation_KEM/kem.c
@@ -1,7 +1,6 @@
 #include "SABER_params.h"
-#include <string.h>
+#include <stddef.h>
 #include <stdint.h>
-#include <stdio.h>
 #include "SABER_indcpa.h"
 #include "api.h"
 #include "verify.h"
@@ -9,9 +8,9 @@
 #include "fips202.h"
 
 
-int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
+int crypto_kem_keypair(uint8_t *pk, uint8_t *sk)
 {
-  int i;
+  size_t i;
 
   indcpa_kem_keypair(pk, sk); // sk[0:SABER_INDCPA_SECRETKEYBYTES-1] <-- sk
   for (i = 0; i < SABER_INDCPA_PUBLICKEYBYTES; i++)
@@ -24,11 +23,11 @@
   return (0);
 }
 
-int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
+int crypto_kem_enc(uint8_t *c, uint8_t *k, const uint8_t *pk)
 {
 
-  unsigned char kr[64]; // Will contain key, coins
-  unsigned char buf[64];
+  uint8_t kr[64]; // Will contain key, coins
+  uint8_t buf[64];
 
   randombytes(buf, 32);
 
@@ -39,7 +38,7 @@
   sha3_512(kr, buf, 64);               // kr[0:63] <-- Hash(buf[0:63]);
                                        // K^ <-- kr[0:31]
                                        // noiseseed (r) <-- kr[32:63];
-  indcpa_kem_enc(buf, kr + 32, pk, c); // buf[0:31] contains message; kr[32:63] contains randomness r;
+  indcpa_kem_enc(c, buf, kr + 32, pk); // buf[0:31] contains message; kr[32:63] contains randomness r;
 
   sha3_256(kr + 32, c, SABER_BYTES_CCA_DEC);
 
@@ -48,15 +47,16 @@
   return (0);
 }
 
-int crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
+int crypto_kem_dec(uint8_t *k, const uint8_t *c, const uint8_t *sk)
 {
-  int i, fail;
-  unsigned char cmp[SABER_BYTES_CCA_DEC];
-  unsigned char buf[64];
-  unsigned char kr[64]; // Will contain key, coins
-  const unsigned char *pk = sk + SABER_INDCPA_SECRETKEYBYTES;
+  size_t i;
+  uint8_t fail;
+  uint8_t cmp[SABER_BYTES_CCA_DEC];
+  uint8_t buf[64];
+  uint8_t kr[64]; // Will contain key, coins
+  const uint8_t *pk = sk + SABER_INDCPA_SECRETKEYBYTES;
 
-  indcpa_kem_dec(sk, c, buf); // buf[0:31] <-- message
+  indcpa_kem_dec(buf, sk, c); // buf[0:31] <-- message
 
   // Multitarget countermeasure for coins + contributory KEM
   for (i = 0; i < 32; i++) // Save hash by storing h(pk) in sk
@@ -64,7 +64,7 @@
 
   sha3_512(kr, buf, 64);
 
-  indcpa_kem_enc(buf, kr + 32, pk, cmp);
+  indcpa_kem_enc(cmp, buf, kr + 32, pk);
 
   fail = verify(c, cmp, SABER_BYTES_CCA_DEC);
 

