--- upstream/avx2/kem.c
+++ upstream-patched/avx2/kem.c
@@ -1,5 +1,6 @@
 #include <stddef.h>
 #include <stdint.h>
+#include "align.h"
 #include "kem.h"
 #include "params.h"
 #include "randombytes.h"
@@ -51,27 +52,25 @@
                    unsigned char *ss,
                    const unsigned char *pk)
 {
-  __attribute__((aligned(32)))
-  uint8_t buf[2*KYBER_SYMBYTES];
+  ALIGN32_ARRAY(uint8_t, 2 * KYBER_SYMBYTES) buf;
   /* Will contain key, coins */
-  __attribute__((aligned(32)))
-  uint8_t kr[2*KYBER_SYMBYTES];
+  ALIGN32_ARRAY(uint8_t, 2 * KYBER_SYMBYTES) kr;
 
-  randombytes(buf, KYBER_SYMBYTES);
+  randombytes(buf.arr, KYBER_SYMBYTES);
   /* Don't release system RNG output */
-  hash_h(buf, buf, KYBER_SYMBYTES);
+  hash_h(buf.arr, buf.arr, KYBER_SYMBYTES);
 
   /* Multitarget countermeasure for coins + contributory KEM */
-  hash_h(buf+KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
-  hash_g(kr, buf, 2*KYBER_SYMBYTES);
+  hash_h(buf.arr+KYBER_SYMBYTES, pk, KYBER_PUBLICKEYBYTES);
+  hash_g(kr.arr, buf.arr, 2*KYBER_SYMBYTES);
 
   /* coins are in kr+KYBER_SYMBYTES */
-  indcpa_enc(ct, buf, pk, kr+KYBER_SYMBYTES);
+  indcpa_enc(ct, buf.arr, pk, kr.arr+KYBER_SYMBYTES);
 
   /* overwrite coins in kr with H(c) */
-  hash_h(kr+KYBER_SYMBYTES, ct, KYBER_CIPHERTEXTBYTES);
+  hash_h(kr.arr+KYBER_SYMBYTES, ct, KYBER_CIPHERTEXTBYTES);
   /* hash concatenation of pre-k and H(c) to k */
-  kdf(ss, kr, 2*KYBER_SYMBYTES);
+  kdf(ss, kr.arr, 2*KYBER_SYMBYTES);
   return 0;
 }
 
@@ -98,33 +97,32 @@
 {
   size_t i;
   int fail;
-  __attribute__((aligned(32)))
-  uint8_t buf[2*KYBER_SYMBYTES];
+  ALIGN32_ARRAY(uint8_t, 2 * KYBER_SYMBYTES) buf;
   /* Will contain key, coins */
-  __attribute__((aligned(32)))
-  uint8_t kr[2*KYBER_SYMBYTES];
+  ALIGN32_ARRAY(uint8_t, 2 * KYBER_SYMBYTES) kr;
   uint8_t cmp[KYBER_CIPHERTEXTBYTES];
   const uint8_t *pk = sk+KYBER_INDCPA_SECRETKEYBYTES;
 
-  indcpa_dec(buf, ct, sk);
+  indcpa_dec(buf.arr, ct, sk);
 
   /* Multitarget countermeasure for coins + contributory KEM */
-  for(i=0;i<KYBER_SYMBYTES;i++)
-    buf[KYBER_SYMBYTES+i] = sk[KYBER_SECRETKEYBYTES-2*KYBER_SYMBYTES+i];
-  hash_g(kr, buf, 2*KYBER_SYMBYTES);
+  for(i=0;i<KYBER_SYMBYTES;i++) {
+    buf.arr[KYBER_SYMBYTES+i] = sk[KYBER_SECRETKEYBYTES-2*KYBER_SYMBYTES+i];
+  }
+  hash_g(kr.arr, buf.arr, 2*KYBER_SYMBYTES);
 
   /* coins are in kr+KYBER_SYMBYTES */
-  indcpa_enc(cmp, buf, pk, kr+KYBER_SYMBYTES);
+  indcpa_enc(cmp, buf.arr, pk, kr.arr+KYBER_SYMBYTES);
 
   fail = verify(ct, cmp, KYBER_CIPHERTEXTBYTES);
 
   /* overwrite coins in kr with H(c) */
-  hash_h(kr+KYBER_SYMBYTES, ct, KYBER_CIPHERTEXTBYTES);
+  hash_h(kr.arr+KYBER_SYMBYTES, ct, KYBER_CIPHERTEXTBYTES);
 
   /* Overwrite pre-k with z on re-encryption failure */
-  cmov(kr, sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES, KYBER_SYMBYTES, fail);
+  cmov(kr.arr, sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES, KYBER_SYMBYTES, (uint8_t)fail);
 
   /* hash concatenation of pre-k and H(c) to k */
-  kdf(ss, kr, 2*KYBER_SYMBYTES);
+  kdf(ss, kr.arr, 2*KYBER_SYMBYTES);
   return 0;
 }

