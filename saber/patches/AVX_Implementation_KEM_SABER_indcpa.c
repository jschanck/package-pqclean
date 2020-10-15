--- upstream/AVX_Implementation_KEM/SABER_indcpa.c
+++ upstream-patched/AVX_Implementation_KEM/SABER_indcpa.c
@@ -17,101 +17,37 @@
 #define h2 ( (1<<(SABER_EP-2)) - (1<<(SABER_EP-SABER_ET-1)) + (1<<(SABER_EQ-SABER_EP-1)) )
 
 
+static void POL2MSG(uint8_t *message_dec, const uint16_t *message_dec_unpacked){
+	int32_t i,j;
 
-uint64_t mask_ar[4]={~(0UL)};
-__m256i mask_load;
-__m256i floor_round;
-__m256i H1_avx;	
-__m256i H2_avx;
-
-void POL2MSG(uint16_t *message_dec_unpacked, unsigned char *message_dec);
-
-/*--------------------------------------------------------------------------------------
-	This routine loads the constant values for Toom-Cook multiplication 
-----------------------------------------------------------------------------------------*/
-void load_values(){
-
-	int64_t i;
-
-	int64_t inv3=43691;
-	int64_t inv9=36409;
-	int64_t inv15=61167;
-
-	int64_t int45=45;
-	int64_t int30=30;
-	int64_t int0=0;
-
-
-	int16_t inv3_avx_load[16],inv9_avx_load[16],inv15_avx_load[16],int45_avx_load[16],int30_avx_load[16],int0_avx_load[16];
-
-	for(i=0;i<16;i++){
-		inv3_avx_load[i]=inv3;
-		inv9_avx_load[i]=inv9;
-		inv15_avx_load[i]=inv15;
-		int45_avx_load[i]=int45;
-		int30_avx_load[i]=int30;
-		int0_avx_load[i]=int0;
-	}
-
-	inv3_avx = _mm256_loadu_si256 ((__m256i const *) (&inv3_avx_load));
-	inv9_avx = _mm256_loadu_si256 ((__m256i const *) (&inv9_avx_load));
-	inv15_avx = _mm256_loadu_si256 ((__m256i const *) (&inv15_avx_load));
-	int45_avx = _mm256_loadu_si256 ((__m256i const *) (&int45_avx_load));
-	int30_avx = _mm256_loadu_si256 ((__m256i const *) (&int30_avx_load));
-	int0_avx = _mm256_loadu_si256 ((__m256i const *) (&int0_avx_load));
-	mask = _mm256_loadu_si256 ((__m256i const *)mask_ar);	
+	for(j=0; j<SABER_KEYBYTES; j++)
+	{
+		message_dec[j] = 0;
+		for(i=0; i<8; i++)
+		message_dec[j] = message_dec[j] | (message_dec_unpacked[j*8 + i] <<i);
+	} 
 }
 
-
-
 /*-----------------------------------------------------------------------------------
 	This routine generates a=[Matrix K x K] of 256-coefficient polynomials 
 -------------------------------------------------------------------------------------*/
 
-
-
-void BS2POLq(const unsigned char *bytes, uint16_t data[SABER_N]){
-	
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;	
-	
-	offset_byte=0;
-
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=13*j;
-			offset_data=8*j;
-			data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
-			data[offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
-			data[offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
-			data[offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
-			data[offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
-			data[offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
-			data[offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
-			data[offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
-		}
-
-
-}
-
-
-void GenMatrix(polyvec *a, const unsigned char *seed) 
+static void GenMatrix(polyvec *a, const uint8_t *seed) 
 {
-  unsigned int one_vector=13*SABER_N/8;
-  unsigned int byte_bank_length=SABER_K*SABER_K*one_vector;
-  unsigned char buf[byte_bank_length];
+  uint8_t buf[SABER_K*SABER_K*13*SABER_N/8];
 
   uint16_t temp_ar[SABER_N];
 
   int i,j,k;
   uint16_t mod = (SABER_Q-1);
 
-  shake128(buf,byte_bank_length,seed,SABER_SEEDBYTES);
+  shake128(buf,sizeof(buf),seed,SABER_SEEDBYTES);
   
   for(i=0;i<SABER_K;i++)
   {
     for(j=0;j<SABER_K;j++)
     {
-	BS2POLq(buf+(i*SABER_K+j)*one_vector,temp_ar);
+	BS2POLq(temp_ar, buf+(i*SABER_K+j)*13*SABER_N/8);
 	for(k=0;k<SABER_N;k++){
 		a[i].vec[j].coeffs[k] = (temp_ar[k])& mod ;
 	}
@@ -119,16 +55,13 @@
   }
 }
 
-void GenSecret(uint16_t r[SABER_K][SABER_N],const unsigned char *seed){
-
+static void GenSecret(uint16_t r[SABER_K][SABER_N],const uint8_t *seed){
 
 		uint32_t i;
 
-		int32_t buf_size= SABER_MU*SABER_N*SABER_K/8;
+		uint8_t buf[SABER_MU*SABER_N*SABER_K/8];
 
-		uint8_t buf[buf_size];
-
-		shake128(buf, buf_size, seed,SABER_NOISESEEDBYTES);
+		shake128(buf, sizeof(buf), seed,SABER_NOISESEEDBYTES);
 
 		for(i=0;i<SABER_K;i++)
 		{
@@ -137,12 +70,42 @@
 }
 
 //********************************matrix-vector mul routines*****************************************************
-void matrix_vector_mul(__m256i a1_avx_combined[NUM_POLY][NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[NUM_POLY][AVX_N1], int isTranspose);
-void vector_vector_mul(__m256i a_avx[NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[AVX_N1]);
+static void matrix_vector_mul(__m256i a1_avx_combined[NUM_POLY][NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[NUM_POLY][AVX_N1], int isTranspose){
+	int64_t i,j;
+
+	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time
+
+	for(i=0;i<NUM_POLY;i++){
+		for(j=0;j<NUM_POLY;j++){
+
+			if(isTranspose==0){
+				toom_cook_4way_avx_n1(a1_avx_combined[i][j], b_bucket[j], c_bucket, j);
+			}
+			else{
+				toom_cook_4way_avx_n1(a1_avx_combined[j][i], b_bucket[j], c_bucket, j);
+			}
+		}
+
+		TC_interpol(c_bucket, res_avx[i]);
+	}
+
+}
+
+static void vector_vector_mul(__m256i a_avx[NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[AVX_N1]){
+
+	int64_t i;
+
+	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time
+
+	for(i=0;i<NUM_POLY;i++){
+		toom_cook_4way_avx_n1(a_avx[i], b_bucket[i], c_bucket, i);		
+	}
+	TC_interpol(c_bucket, res_avx);
+}
 
 //********************************matrix-vector mul routines*****************************************************
 
-void indcpa_kem_keypair(unsigned char *pk, unsigned char *sk)
+void indcpa_kem_keypair(uint8_t *pk, uint8_t *sk)
 {
  
   polyvec a[SABER_K];
@@ -151,8 +114,8 @@
 
   
  
-  unsigned char seed[SABER_SEEDBYTES];
-  unsigned char noiseseed[SABER_COINBYTES];
+  uint8_t seed[SABER_SEEDBYTES];
+  uint8_t noiseseed[SABER_COINBYTES];
   int32_t i,j,k;
 
 
@@ -164,22 +127,12 @@
   __m256i a_avx[SABER_K][SABER_K][SABER_N/16];
   //__m256i acc[2*SABER_N/16];
 
-
-  mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
-  mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);
-
   mod=_mm256_set1_epi16(SABER_Q-1);
-  floor_round=_mm256_set1_epi16(4);
-
-  H1_avx=_mm256_set1_epi16(h1);
 
   __m256i b_bucket[NUM_POLY][SCHB_N*4];
 
 //--------------AVX declaration ends------------------
 
-   load_values();
-
-
   randombytes(seed, SABER_SEEDBYTES);
  
   shake128(seed, SABER_SEEDBYTES, seed, SABER_SEEDBYTES); // for not revealing system RNG state
@@ -223,7 +176,7 @@
 		
 	for(i=0;i<SABER_K;i++){ //shift right EQ-EP bits
 		for(j=0;j<SABER_N/16;j++){
-			res_avx[i][j]=_mm256_add_epi16 (res_avx[i][j], H1_avx);
+			res_avx[i][j]=_mm256_add_epi16 (res_avx[i][j], _mm256_set1_epi16(h1));
 			res_avx[i][j]=_mm256_srli_epi16 (res_avx[i][j], (SABER_EQ-SABER_EP) );
 			res_avx[i][j]=_mm256_and_si256 (res_avx[i][j], mod);			
 		}
@@ -231,16 +184,16 @@
 
 	//------------------Pack sk into byte string-------
 		
-	POLVEC2BS(sk,skpv1,SABER_Q);
+	POLVEC2BS(sk, (const uint16_t (*)[SABER_N])skpv1, SABER_Q);
 
 	//------------------Pack pk into byte string-------
 	
 	for(i=0;i<SABER_K;i++){ // reuses skpv1[] for unpacking avx of public-key
 		  for(j=0;j<SABER_N/16;j++){
-		  	_mm256_maskstore_epi32 ((int *) (skpv1[i]+j*16), mask_load, res_avx[i][j]);
+		  	_mm256_maskstore_epi32 ((int *) (skpv1[i]+j*16), _mm256_set1_epi32(-1), res_avx[i][j]);
 		  }
 	  }
-	POLVEC2BS(pk,skpv1,SABER_P); // load the public-key into pk byte string 	
+	POLVEC2BS(pk, (const uint16_t (*)[SABER_N])skpv1, SABER_P); // load the public-key into pk byte string 	
 
 
 	for(i=0;i<SABER_SEEDBYTES;i++){ // now load the seedbytes in PK. Easy since seed bytes are kept in byte format.
@@ -250,13 +203,13 @@
 }
 
 
-void indcpa_kem_enc(unsigned char *message_received, unsigned char *noiseseed, const unsigned char *pk, unsigned char *ciphertext)
+void indcpa_kem_enc(uint8_t ciphertext[SABER_BYTES_CCA_DEC], const uint8_t m[SABER_KEYBYTES], const uint8_t noiseseed[SABER_NOISESEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES])
 { 
 
 
 	uint32_t i,j,k;
 	polyvec a[SABER_K];		// skpv;
-	unsigned char seed[SABER_SEEDBYTES];
+	uint8_t seed[SABER_SEEDBYTES];
 	uint16_t pkcl[SABER_K][SABER_N]; 	//public key of received by the client
 
 
@@ -264,9 +217,8 @@
 	uint16_t temp[SABER_K][SABER_N];
 	uint16_t message[SABER_KEYBYTES*8];
 
-	unsigned char msk_c[SABER_SCALEBYTES_KEM];
+	uint8_t msk_c[SABER_SCALEBYTES_KEM];
 
-	uint64_t CLOCK1, CLOCK2;
 	//--------------AVX declaration------------------
 	
 	  __m256i sk_avx[SABER_K][SABER_N/16];
@@ -280,45 +232,27 @@
 
           __m256i message_avx[SABER_N/16];
 		
-	  mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
-	  mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);
-
 	  mod=_mm256_set1_epi16(SABER_Q-1);
 	  mod_p=_mm256_set1_epi16(SABER_P-1);
 
 	  
 
-	floor_round=_mm256_set1_epi16(4);
-
-	H1_avx=_mm256_set1_epi16(h1);
- 
 	__m256i b_bucket[NUM_POLY][SCHB_N*4];
 
 	//--------------AVX declaration ends------------------
-	load_values();
-      
 	for(i=0;i<SABER_SEEDBYTES;i++){ // Load the seedbytes in the client seed from PK.
 		seed[i]=pk[ SABER_POLYVECCOMPRESSEDBYTES + i]; 
 	}
 
-	count_enc++;
-	CLOCK1=cpucycles();
 	GenMatrix(a, seed);
-	CLOCK2=cpucycles();
-	clock_matrix=clock_matrix+(CLOCK2-CLOCK1);
-				
-	CLOCK1=cpucycles();
 	GenSecret(skpv1,noiseseed);
-	CLOCK2=cpucycles();
-	clock_secret=clock_secret+(CLOCK2-CLOCK1);
-
 
 	// ----------- Load skpv1 into avx vectors ---------- 
 	for(i=0;i<SABER_K;i++){ 
 		for(j=0; j<SABER_N/16; j++){
 		    sk_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1[i][j*16]));
 		}
-  	}
+	}
 
 	// ----------- Load skpv1 into avx vectors ---------- 
 	  for(i=0;i<SABER_K;i++){ 
@@ -330,19 +264,16 @@
  	 }
 	//-----------------matrix-vector multiplication and rounding
 
-	CLOCK1=cpucycles();
 	for(j=0;j<NUM_POLY;j++){
 		TC_eval(sk_avx[j], b_bucket[j]);
 	}
 	matrix_vector_mul(a_avx, b_bucket, res_avx, 0);// Matrix-vector multiplication; Matrix in normal order
-	CLOCK2=cpucycles();
-	clock_mv_vv_mul= clock_mv_vv_mul + (CLOCK2-CLOCK1);
-	
+
 	// Now truncation
 
 	for(i=0;i<SABER_K;i++){ //shift right EQ-EP bits
 		for(j=0;j<SABER_N/16;j++){
-			res_avx[i][j]=_mm256_add_epi16 (res_avx[i][j], H1_avx);
+			res_avx[i][j]=_mm256_add_epi16 (res_avx[i][j], _mm256_set1_epi16(h1));
 			res_avx[i][j]=_mm256_srli_epi16 (res_avx[i][j], (SABER_EQ-SABER_EP) );
 			res_avx[i][j]=_mm256_and_si256 (res_avx[i][j], mod);			
 
@@ -353,18 +284,18 @@
 	//-----this result should be put in b_prime for later use in server.
 	for(i=0;i<SABER_K;i++){ // first store in 16 bit arrays
 		  for(j=0;j<SABER_N/16;j++){
-			_mm256_maskstore_epi32 ((int *)(temp[i]+j*16), mask_load, res_avx[i][j]);
+			_mm256_maskstore_epi32 ((int *)(temp[i]+j*16), _mm256_set1_epi32(-1), res_avx[i][j]);
 		  }
 	  }
 	
-	POLVEC2BS(ciphertext,temp, SABER_P); // Pack b_prime into ciphertext byte string
+	POLVEC2BS(ciphertext, (const uint16_t (*)[SABER_N])temp, SABER_P); // Pack b_prime into ciphertext byte string
 
 //**************client matrix-vector multiplication ends******************//
 
 	//------now calculate the v'
 
 	//-------unpack the public_key
-	BS2POLVEC(pk, pkcl, SABER_P);
+	BS2POLVEC(pkcl, pk, SABER_P);
 
 	for(i=0;i<SABER_K;i++){
 		for(j=0; j<SABER_N/16; j++){
@@ -379,24 +310,19 @@
 
 	// vector-vector scalar multiplication with mod p
 
-	CLOCK1=cpucycles();
 	vector_vector_mul(pkcl_avx, b_bucket, vprime_avx);
-	CLOCK2=cpucycles();
-	clock_mv_vv_mul= clock_mv_vv_mul + (CLOCK2-CLOCK1);
-
-
 
 	// Computation of v'+h1 
 	for(i=0;i<SABER_N/16;i++){//adding h1
- 		vprime_avx[i]=_mm256_add_epi16(vprime_avx[i], H1_avx);
+ 		vprime_avx[i]=_mm256_add_epi16(vprime_avx[i], _mm256_set1_epi16(h1));
 	}
 
-	// unpack message_received;
+	// unpack m;
 	for(j=0; j<SABER_KEYBYTES; j++)
 	{
 		for(i=0; i<8; i++)
 		{
-			message[8*j+i] = ((message_received[j]>>i) & 0x01);
+			message[8*j+i] = ((m[j]>>i) & 0x01);
 		}
 	}
 	// message encoding
@@ -417,7 +343,7 @@
 	// Unpack avx
 	for(j=0;j<SABER_N/16;j++)
 	{
-			_mm256_maskstore_epi32 ((int *) (temp[0]+j*16), mask_load, vprime_avx[j]);
+			_mm256_maskstore_epi32 ((int *) (temp[0]+j*16), _mm256_set1_epi32(-1), vprime_avx[j]);
 	}
 	
 	#if Saber_type == 1
@@ -436,7 +362,7 @@
 }
 
 
-void indcpa_kem_dec(const unsigned char *sk, const unsigned char *ciphertext, unsigned char message_dec[])
+void indcpa_kem_dec(uint8_t m[SABER_KEYBYTES], const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
 {
 
 	uint32_t i,j;
@@ -446,8 +372,6 @@
 	uint8_t scale_ar[SABER_SCALEBYTES_KEM];
 	uint16_t op[SABER_N];
 
-	uint64_t CLOCK1, CLOCK2;
-
 	//--------------AVX declaration------------------
 	
 
@@ -459,23 +383,16 @@
 
 	  __m256i sksv_avx[SABER_K][SABER_N/16];
 	  __m256i pksv_avx[SABER_K][SABER_N/16];
-	  
-	  mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
-	  mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);
 
 	  //mod_p=_mm256_set1_epi16(SABER_P-1);
 
-	  H2_avx=_mm256_set1_epi16(h2);
-
 	  __m256i b_bucket[NUM_POLY][SCHB_N*4];
 	//--------------AVX declaration ends------------------
-	
- 	load_values();
 
 	//-------unpack the public_key
 
-	BS2POLVEC(sk, sksv, SABER_Q); //sksv is the secret-key
-	BS2POLVEC(ciphertext, pksv, SABER_P); //pksv is the ciphertext
+	BS2POLVEC(sksv, sk, SABER_Q); //sksv is the secret-key
+	BS2POLVEC(pksv, ciphertext, SABER_P); //pksv is the ciphertext
 
 	for(i=0;i<SABER_K;i++){
 		for(j=0; j<SABER_N/16; j++){
@@ -490,8 +407,6 @@
 
 
 	// InnerProduct(b', s, mod p)
-	CLOCK1=cpucycles();
-	count_mul++;
 
 	for(j=0;j<NUM_POLY;j++){
 		TC_eval(sksv_avx[j], b_bucket[j]);
@@ -499,12 +414,8 @@
 
 	vector_vector_mul(pksv_avx, b_bucket, v_avx);
 
-	CLOCK2=cpucycles();
-	clock_mul=clock_mul+(CLOCK2-CLOCK1);
-
-
 	for(i=0; i<SABER_N/16; i++){
-		_mm256_maskstore_epi32 ((int *)(message_dec_unpacked+i*16), mask_load, v_avx[i]);
+		_mm256_maskstore_epi32 ((int *)(message_dec_unpacked+i*16), _mm256_set1_epi32(-1), v_avx[i]);
 	}
 
 
@@ -513,11 +424,11 @@
 	}
 
 	#if Saber_type == 1
-		SABER_un_pack3bit(scale_ar, op);
+		SABER_un_pack3bit(op, scale_ar);
 	#elif Saber_type == 2
-		SABER_un_pack4bit(scale_ar, op);
+		SABER_un_pack4bit(op, scale_ar);
 	#elif Saber_type == 3
-		SABER_un_pack6bit(scale_ar, op);
+		SABER_un_pack6bit(op, scale_ar);
 	#endif
 
 
@@ -527,55 +438,6 @@
 	}
 
 
-	POL2MSG(message_dec_unpacked, message_dec);
-}
-
-void POL2MSG(uint16_t *message_dec_unpacked, unsigned char *message_dec){
-
-	int32_t i,j;
-
-	for(j=0; j<SABER_KEYBYTES; j++)
-	{
-		message_dec[j] = 0;
-		for(i=0; i<8; i++)
-		message_dec[j] = message_dec[j] | (message_dec_unpacked[j*8 + i] <<i);
-	} 
-
-}
-
-void matrix_vector_mul(__m256i a1_avx_combined[NUM_POLY][NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[NUM_POLY][AVX_N1], int isTranspose){
-
-
-
-	int64_t i,j;
-
-	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time
-
-	for(i=0;i<NUM_POLY;i++){
-		for(j=0;j<NUM_POLY;j++){
-
-			if(isTranspose==0){
-				toom_cook_4way_avx_n1(a1_avx_combined[i][j], b_bucket[j], c_bucket, j);
-			}
-			else{
-				toom_cook_4way_avx_n1(a1_avx_combined[j][i], b_bucket[j], c_bucket, j);
-			}
-		}
-
-		TC_interpol(c_bucket, res_avx[i]);
-	}
-
-}
-
-void vector_vector_mul(__m256i a_avx[NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[AVX_N1]){
-
-	int64_t i;
-
-	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time
-
-	for(i=0;i<NUM_POLY;i++){
-		toom_cook_4way_avx_n1(a_avx[i], b_bucket[i], c_bucket, i);		
-	}
-	TC_interpol(c_bucket, res_avx);
+	POL2MSG(m, message_dec_unpacked);
 }
 

