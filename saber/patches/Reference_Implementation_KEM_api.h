--- upstream/Reference_Implementation_KEM/api.h
+++ upstream-patched/Reference_Implementation_KEM/api.h
@@ -1,25 +1,30 @@
 #ifndef API_H
 #define API_H
 
-#include "SABER_params.h"
-
-#if SABER_L == 2
+#if LightSaber
 	#define CRYPTO_ALGNAME "LightSaber"
-#elif SABER_L == 3
+	#define CRYPTO_BYTES 32
+	#define CRYPTO_CIPHERTEXTBYTES 736
+	#define CRYPTO_PUBLICKEYBYTES 672
+	#define CRYPTO_SECRETKEYBYTES 1568
+#elif Saber
 	#define CRYPTO_ALGNAME "Saber"
-#elif SABER_L == 4
+	#define CRYPTO_BYTES 32
+	#define CRYPTO_CIPHERTEXTBYTES 1088
+	#define CRYPTO_PUBLICKEYBYTES 992
+	#define CRYPTO_SECRETKEYBYTES 2304
+#elif FireSaber
 	#define CRYPTO_ALGNAME "FireSaber"
+	#define CRYPTO_BYTES 32
+	#define CRYPTO_CIPHERTEXTBYTES 1472
+	#define CRYPTO_PUBLICKEYBYTES 1312
+	#define CRYPTO_SECRETKEYBYTES 3040
 #else
 	#error "Unsupported SABER parameter."
 #endif
 
-#define CRYPTO_SECRETKEYBYTES SABER_SECRETKEYBYTES
-#define CRYPTO_PUBLICKEYBYTES SABER_PUBLICKEYBYTES
-#define CRYPTO_BYTES SABER_KEYBYTES
-#define CRYPTO_CIPHERTEXTBYTES SABER_BYTES_CCA_DEC
-
 int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
-int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
-int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);
+int crypto_kem_enc(unsigned char *ct, unsigned char *k, const unsigned char *pk);
+int crypto_kem_dec(unsigned char *k, const unsigned char *ct, const unsigned char *sk);
 
 #endif /* api_h */

