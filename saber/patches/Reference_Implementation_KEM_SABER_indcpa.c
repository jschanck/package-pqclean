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
@@ -13,90 +12,105 @@
 
 void indcpa_kem_keypair(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES])
 {
-	uint16_t A[SABER_L][SABER_L][SABER_N];
-	uint16_t s[SABER_L][SABER_N];
-	uint16_t b[SABER_L][SABER_N] = {0};
-
-	uint8_t seed_A[SABER_SEEDBYTES];
-	uint8_t seed_s[SABER_NOISE_SEEDBYTES];
-	int i, j;
+	size_t i, j;
+
+	poly A[SABER_L][SABER_L];
+	poly s[SABER_L];
+	poly res[SABER_L];
+
+	uint8_t rand[SABER_NOISESEEDBYTES];
+	uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES;
 
 	randombytes(seed_A, SABER_SEEDBYTES);
 	shake128(seed_A, SABER_SEEDBYTES, seed_A, SABER_SEEDBYTES); // for not revealing system RNG state
-	randombytes(seed_s, SABER_NOISE_SEEDBYTES);
 
-	GenMatrix(A, seed_A);
-	GenSecret(s, seed_s);
-	MatrixVectorMul(A, s, b, 1);
+	randombytes(rand, SABER_NOISESEEDBYTES);
+	GenSecret(s, rand);
+	POLVECq2BS(sk, s);
 
-	for (i = 0; i < SABER_L; i++)
-	{
-		for (j = 0; j < SABER_N; j++)
-		{
-			b[i][j] = (b[i][j] + h1) >> (SABER_EQ - SABER_EP);
+	GenMatrix(A, seed_A); // sample matrix A
+	MatrixVectorMul(res, (const poly (*)[SABER_L])A, (const poly *)s, 1); // Matrix in transposed order
+
+
+	// rounding
+	for(i=0;i<SABER_L;i++) {
+		for(j=0;j<SABER_N;j++) {
+			res[i].coeffs[j] += h1;
+			res[i].coeffs[j] >>= SABER_EQ-SABER_EP;
 		}
 	}
 
-	POLVECq2BS(sk, s);
-	POLVECp2BS(pk, b);
-	memcpy(pk + SABER_POLYVECCOMPRESSEDBYTES, seed_A, sizeof(seed_A));
+	POLVECp2BS(pk, res); // pack public key
 }
 
-void indcpa_kem_enc(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t ciphertext[SABER_BYTES_CCA_DEC])
+
+void indcpa_kem_enc(uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t m[SABER_KEYBYTES], const uint8_t noiseseed[SABER_NOISESEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES])
 {
-	uint16_t A[SABER_L][SABER_L][SABER_N];
-	uint16_t sp[SABER_L][SABER_N];
-	uint16_t bp[SABER_L][SABER_N] = {0};
-	uint16_t vp[SABER_N] = {0};
-	uint16_t mp[SABER_N];
-	uint16_t b[SABER_L][SABER_N];
-	int i, j;
+	size_t i, j;
+
+	poly A[SABER_L][SABER_L];
+	poly res[SABER_L];
+	poly s[SABER_L];
+	poly *temp = A[0]; // re-use stack space
+	poly *vprime = &A[0][0];
+	poly *message = &A[0][1];
+
 	const uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES;
+	uint8_t *msk_c = ciphertext + SABER_POLYVECCOMPRESSEDBYTES;
 
+	GenSecret(s, noiseseed);
 	GenMatrix(A, seed_A);
-	GenSecret(sp, seed_sp);
-	MatrixVectorMul(A, sp, bp, 0);
+	MatrixVectorMul(res, (const poly (*)[SABER_L])A, (const poly *)s, 0); // 0 => not transposed
 
-	for (i = 0; i < SABER_L; i++)
-	{
-		for (j = 0; j < SABER_N; j++)
-		{
-			bp[i][j] = (bp[i][j] + h1) >> (SABER_EQ - SABER_EP);
+
+	// rounding
+	for(i=0;i<SABER_L;i++){ //shift right EQ-EP bits
+		for(j=0;j<SABER_N;j++){
+			res[i].coeffs[j] += h1;
+			res[i].coeffs[j] >>= SABER_EQ-SABER_EP;
 		}
 	}
+	POLVECp2BS(ciphertext, res);
 
-	POLVECp2BS(ciphertext, bp);
-	BS2POLVECp(pk, b);
-	InnerProd(b, sp, vp);
+	// vector-vector scalar multiplication with mod p
+	BS2POLVECp(temp, pk);
+	InnerProd(vprime, temp, s);
+	BS2POLmsg(message, m);
 
-	BS2POLmsg(m, mp);
-
-	for (j = 0; j < SABER_N; j++)
+	for(i=0;i<SABER_N;i++)
 	{
-		vp[j] = (vp[j] - (mp[j] << (SABER_EP - 1)) + h1) >> (SABER_EP - SABER_ET);
+		vprime->coeffs[i] += h1 - (message->coeffs[i] << (SABER_EP-1));
+		vprime->coeffs[i] &= SABER_P-1;
+		vprime->coeffs[i] >>= SABER_EP-SABER_ET;
 	}
 
-	POLT2BS(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, vp);
+	POLT2BS(msk_c, vprime);
 }
 
-void indcpa_kem_dec(const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint8_t m[SABER_KEYBYTES])
+
+void indcpa_kem_dec(uint8_t m[SABER_KEYBYTES], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
 {
+	size_t i;
 
-	uint16_t s[SABER_L][SABER_N];
-	uint16_t b[SABER_L][SABER_N];
-	uint16_t v[SABER_N] = {0};
-	uint16_t cm[SABER_N];
-	int i;
-
-	BS2POLVECq(sk, s);
-	BS2POLVECp(ciphertext, b);
-	InnerProd(b, s, v);
-	BS2POLT(ciphertext + SABER_POLYVECCOMPRESSEDBYTES, cm);
+	poly temp[SABER_L];
+	poly s[SABER_L];
 
-	for (i = 0; i < SABER_N; i++)
-	{
-		v[i] = (v[i] + h2 - (cm[i] << (SABER_EP - SABER_ET))) >> (SABER_EP - 1);
+	const uint8_t *packed_cm = ciphertext+SABER_POLYVECCOMPRESSEDBYTES;
+	poly *v = &temp[0];
+	poly *cm = &temp[1];
+
+	BS2POLVECq(s, sk);
+	BS2POLVECp(temp, ciphertext);
+	InnerProd(&temp[0], temp, s);
+
+	BS2POLT(cm, packed_cm);
+
+	for(i=0;i<SABER_N;i++){
+		v->coeffs[i] += h2 - (cm->coeffs[i]<<(SABER_EP-SABER_ET));
+		v->coeffs[i] &= SABER_P-1;
+		v->coeffs[i] >>= SABER_EP-1;
 	}
 
 	POLmsg2BS(m, v);
 }
+

