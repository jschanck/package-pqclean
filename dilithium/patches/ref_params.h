--- upstream/ref/params.h
+++ upstream-patched/ref/params.h
@@ -1,8 +1,6 @@
 #ifndef PARAMS_H
 #define PARAMS_H
 
-#include "config.h"
-
 #define SEEDBYTES 32
 #define CRHBYTES 48
 #define N 256
@@ -19,6 +17,15 @@
 #define GAMMA1 (1 << 17)
 #define GAMMA2 ((Q-1)/88)
 #define OMEGA 80
+#ifdef DILITHIUM_USE_AES
+#define CRYPTO_ALGNAME "Dilithium2-AES"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium2aes_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium2aes_ref_##s
+#else
+#define CRYPTO_ALGNAME "Dilithium2"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium2_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium2_ref_##s
+#endif
 
 #elif DILITHIUM_MODE == 3
 #define K 6
@@ -29,6 +36,15 @@
 #define GAMMA1 (1 << 19)
 #define GAMMA2 ((Q-1)/32)
 #define OMEGA 55
+#ifdef DILITHIUM_USE_AES
+#define CRYPTO_ALGNAME "Dilithium3-AES"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium3aes_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium3aes_ref_##s
+#else
+#define CRYPTO_ALGNAME "Dilithium3"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium3_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium3_ref_##s
+#endif
 
 #elif DILITHIUM_MODE == 5
 #define K 8
@@ -39,6 +55,15 @@
 #define GAMMA1 (1 << 19)
 #define GAMMA2 ((Q-1)/32)
 #define OMEGA 75
+#ifdef DILITHIUM_USE_AES
+#define CRYPTO_ALGNAME "Dilithium5-AES"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium5aes_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium5aes_ref_##s
+#else
+#define CRYPTO_ALGNAME "Dilithium5"
+#define DILITHIUM_NAMESPACETOP pqcrystals_dilithium5_ref
+#define DILITHIUM_NAMESPACE(s) pqcrystals_dilithium5_ref_##s
+#endif
 
 #endif
 

