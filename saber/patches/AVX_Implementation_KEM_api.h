--- upstream/AVX_Implementation_KEM/api.h
+++ upstream-patched/AVX_Implementation_KEM/api.h
@@ -1,53 +1,30 @@
-//
-//  api.h
-//
-//  Created by Bassham, Lawrence E (Fed) on 9/6/17.
-//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
-//
+#ifndef API_H
+#define API_H
 
-
-//   This is a sample 'api.h' for use 'sign.c'
-
-#ifndef api_h
-#define api_h
-
-
-// Available algorithms for different security levels
-#define LightSaber 1
-#define Saber 2
-#define FireSaber 3
-
-// Change the algorithm name 
-//#define SABER_TYPE LightSaber
-#define SABER_TYPE Saber
-// #define SABER_TYPE FireSaber
-
-//  Set these three values apropriately for your algorithm
-#if SABER_TYPE == LightSaber
+#if LightSaber
 	#define CRYPTO_ALGNAME "LightSaber"
-	#define CRYPTO_SECRETKEYBYTES 1568
-	#define CRYPTO_PUBLICKEYBYTES (2*320+32)
 	#define CRYPTO_BYTES 32
 	#define CRYPTO_CIPHERTEXTBYTES 736
-	#define Saber_type 1
-#elif SABER_TYPE == Saber
+	#define CRYPTO_PUBLICKEYBYTES 672
+	#define CRYPTO_SECRETKEYBYTES 1568
+#elif Saber
 	#define CRYPTO_ALGNAME "Saber"
-	#define CRYPTO_SECRETKEYBYTES 2304
-	#define CRYPTO_PUBLICKEYBYTES (3*320+32)
 	#define CRYPTO_BYTES 32
 	#define CRYPTO_CIPHERTEXTBYTES 1088
-	#define Saber_type 2
-#elif SABER_TYPE == FireSaber
+	#define CRYPTO_PUBLICKEYBYTES 992
+	#define CRYPTO_SECRETKEYBYTES 2304
+#elif FireSaber
 	#define CRYPTO_ALGNAME "FireSaber"
-	#define CRYPTO_SECRETKEYBYTES 3040
-	#define CRYPTO_PUBLICKEYBYTES (4*320+32)
 	#define CRYPTO_BYTES 32
 	#define CRYPTO_CIPHERTEXTBYTES 1472
-	#define Saber_type 3
+	#define CRYPTO_PUBLICKEYBYTES 1312
+	#define CRYPTO_SECRETKEYBYTES 3040
+#else
+	#error "Unsupported SABER parameter."
 #endif
 
 int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
-int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
-int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);
+int crypto_kem_enc(unsigned char *ct, unsigned char *k, const unsigned char *pk);
+int crypto_kem_dec(unsigned char *k, const unsigned char *ct, const unsigned char *sk);
 
-#endif /* api_h */
+#endif /* API_H */

