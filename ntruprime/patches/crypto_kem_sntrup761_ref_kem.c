--- upstream/crypto_kem/sntrup761/ref/kem.c
+++ upstream-patched/crypto_kem/sntrup761/ref/kem.c
@@ -1,4 +1,3 @@
-#include <stdlib.h> /* for abort() in case of OpenSSL failures */
 #include "params.h"
 
 #include "randombytes.h"
@@ -473,7 +472,7 @@
 static void Expand(uint32 *L,const unsigned char *k)
 {
   int i;
-  if (crypto_stream_aes256ctr((unsigned char *) L,4*p,aes_nonce,k) != 0) abort();
+  crypto_stream_aes256ctr((unsigned char *) L,4*p,aes_nonce,k);
   for (i = 0;i < p;++i) {
     uint32 L0 = ((unsigned char *) L)[4*i];
     uint32 L1 = ((unsigned char *) L)[4*i+1];

