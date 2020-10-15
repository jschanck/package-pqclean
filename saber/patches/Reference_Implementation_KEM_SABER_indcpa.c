--- upstream/Reference_Implementation_KEM/SABER_indcpa.c
+++ upstream-patched/Reference_Implementation_KEM/SABER_indcpa.c
@@ -3,7 +3,6 @@
 #include "SABER_indcpa.h"
 #include "poly.h"
 #include "pack_unpack.h"
-#include "poly_mul.c"
 #include "rng.h"
 #include "fips202.h"
 #include "SABER_params.h"
@@ -27,7 +26,7 @@
 
 	GenMatrix(A, seed_A);
 	GenSecret(s, seed_s);
-	MatrixVectorMul(A, s, b, 1);
+	MatrixVectorMul(b, (const uint16_t (*)[SABER_L][SABER_N])A, (const uint16_t (*)[SABER_N])s, 1);
 
 	for (i = 0; i < SABER_L; i++)
 	{
@@ -37,12 +36,12 @@
 		}
 	}
 
-	POLVECq2BS(sk, s);
-	POLVECp2BS(pk, b);
+	POLVECq2BS(sk, (const uint16_t (*)[SABER_N])s);
+	POLVECp2BS(pk, (const uint16_t (*)[SABER_N])b);
 	memcpy(pk + SABER_POLYVECCOMPRESSEDBYTES, seed_A, sizeof(seed_A));
 }
 
-void indcpa_kem_enc(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t ciphertext[SABER_BYTES_CCA_DEC])
+void indcpa_kem_enc(uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES])
 {
 	uint16_t A[SABER_L][SABER_L][SABER_N];
 	uint16_t sp[SABER_L][SABER_N];
@@ -55,7 +54,7 @@
 
 	GenMatrix(A, seed_A);
 	GenSecret(sp, seed_sp);
-	MatrixVectorMul(A, sp, bp, 0);
+	MatrixVectorMul(bp, (const uint16_t (*)[SABER_L][SABER_N])A, (const uint16_t (*)[SABER_N])sp, 0);
 
 	for (i = 0; i < SABER_L; i++)
 	{
@@ -65,11 +64,11 @@
 		}
 	}
 
-	POLVECp2BS(ciphertext, bp);
-	BS2POLVECp(pk, b);
-	InnerProd(b, sp, vp);
+	POLVECp2BS(ciphertext, (const uint16_t (*)[SABER_N])bp);
+	BS2POLVECp(b, pk);
+	InnerProd(vp, (const uint16_t (*)[SABER_N])b, (const uint16_t (*)[SABER_N])sp);
 
-	BS2POLmsg(m, mp);
+	BS2POLmsg(mp, m);
 
 	for (j = 0; j < SABER_N; j++)
 	{
@@ -79,7 +78,7 @@
 	POLT2BS(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, vp);
 }
 
-void indcpa_kem_dec(const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint8_t m[SABER_KEYBYTES])
+void indcpa_kem_dec(uint8_t m[SABER_KEYBYTES], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
 {
 
 	uint16_t s[SABER_L][SABER_N];
@@ -88,10 +87,10 @@
 	uint16_t cm[SABER_N];
 	int i;
 
-	BS2POLVECq(sk, s);
-	BS2POLVECp(ciphertext, b);
-	InnerProd(b, s, v);
-	BS2POLT(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, cm);
+	BS2POLVECq(s, sk);
+	BS2POLVECp(b, ciphertext);
+	InnerProd(v, (const uint16_t (*)[SABER_N])b, (const uint16_t (*)[SABER_N])s);
+	BS2POLT(cm, ciphertext + SABER_POLYVECCOMPRESSEDBYTES);
 
 	for (i = 0; i < SABER_N; i++)
 	{

