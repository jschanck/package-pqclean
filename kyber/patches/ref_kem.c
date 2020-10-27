--- upstream/ref/kem.c
+++ upstream-patched/ref/kem.c
@@ -118,7 +118,7 @@
   hash_h(kr+KYBER_SYMBYTES, ct, KYBER_CIPHERTEXTBYTES);
 
   /* Overwrite pre-k with z on re-encryption failure */
-  cmov(kr, sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES, KYBER_SYMBYTES, fail);
+  cmov(kr, sk+KYBER_SECRETKEYBYTES-KYBER_SYMBYTES, KYBER_SYMBYTES, (uint8_t)fail);
 
   /* hash concatenation of pre-k and H(c) to k */
   kdf(ss, kr, 2*KYBER_SYMBYTES);

