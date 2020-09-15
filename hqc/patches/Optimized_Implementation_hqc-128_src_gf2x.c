--- hqc-2020-05-29/Optimized_Implementation/hqc-128/src/gf2x.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-128/src/gf2x.c
@@ -14,25 +14,21 @@
 #define T_TM3_3W_256 32
 #define T_TM3_3W_64 128
 
-#define VEC_N_ARRAY_SIZE_VEC CEIL_DIVIDE(PARAM_N, 256) /*!< The number of needed vectors to store PARAM_N bits*/
-#define WORD 64
-#define LAST64 (PARAM_N >> 6)
-uint64_t a1_times_a2[VEC_N_256_SIZE_64 << 1];
-uint64_t tmp_reduce[VEC_N_ARRAY_SIZE_VEC << 2];
-__m256i *o256 = (__m256i *) tmp_reduce;
+#define VEC_N_SIZE_256 CEIL_DIVIDE(PARAM_N, 256) /*!< The number of needed vectors to store PARAM_N bits*/
+__m256i a1_times_a2[2 * VEC_N_SIZE_256 + 1];
 uint64_t bloc64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
 uint64_t bit64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
 
 
-static inline void reduce(uint64_t *o, uint64_t *a);
-inline static void karat_mult_1(__m128i *C, __m128i *A, __m128i *B);
-inline static void karat_mult_2(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_4(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_8(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_16(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_32(__m256i *C, __m256i *A, __m256i *B);
-static inline void divByXplus1(__m256i *out,__m256i *in,int size);
-void TOOM3Mult(uint64_t* Out, const uint64_t *A, const uint64_t *B);
+static inline void reduce(uint64_t *o, const uint64_t *a);
+static inline void karat_mult_1(__m128i *C, __m128i *A, __m128i *B);
+static inline void karat_mult_2(__m256i *C, __m256i *A, __m256i *B);
+static inline void karat_mult_4(__m256i *C, __m256i *A, __m256i *B);
+static inline void karat_mult_8(__m256i *C, __m256i *A, __m256i *B);
+static inline void karat_mult_16(__m256i *C, __m256i *A, __m256i *B);
+static inline void karat_mult_32(__m256i *C, __m256i *A, __m256i *B);
+static inline void divByXplus1(__m256i *out, __m256i *in, int size);
+static void TOOM3Mult(__m256i *Out, const uint64_t *A, const uint64_t *B);
 
 
 
@@ -44,32 +40,17 @@
  * @param[out] o Pointer to the result
  * @param[in] a Pointer to the polynomial a(x)
  */
-static inline void reduce(uint64_t *o, uint64_t *a) {
-	__m256i r256, carry256;
-	__m256i *a256 = (__m256i *) a;
-	static const int32_t dec64 = PARAM_N & 0x3f;
-	static const int32_t d0 = WORD - dec64;
-	int32_t i, i2;
-
-	for (i = LAST64 ; i < (PARAM_N >> 5) - 4 ; i += 4) {
-		r256 = _mm256_lddqu_si256((__m256i const *) (& a[i]));
-		r256 = _mm256_srli_epi64(r256, dec64);
-		carry256 = _mm256_lddqu_si256((__m256i const *) (& a[i + 1]));
-		carry256 = _mm256_slli_epi64(carry256, d0);
-		r256 ^= carry256;
-		i2 = (i - LAST64) >> 2;
-		o256[i2] = a256[i2] ^ r256;
-	}
-
-	r256 = (__m256i){a[i], a[i + 1], 0x0UL, 0x0UL};
-	carry256 = _mm256_lddqu_si256((__m256i const *) (& a[i + 1]));
-	r256 = _mm256_srli_epi64(r256, dec64);
-	carry256 = _mm256_slli_epi64(carry256, d0);
-	r256 ^= carry256;
-	i2 = (i - LAST64) >> 2;
-	o256[i2] = (a256[i2] ^ r256);
-	tmp_reduce[LAST64] &= RED_MASK;
-	memcpy(o, tmp_reduce, VEC_N_SIZE_BYTES);
+static inline void reduce(uint64_t *o, const uint64_t *a) {
+	uint64_t r;
+	uint64_t carry;
+
+	for (uint32_t i = 0 ; i < VEC_N_SIZE_64 ; i++) {
+		r = a[i + VEC_N_SIZE_64 - 1] >> (PARAM_N & 63);
+		carry = (uint64_t) (a[i + VEC_N_SIZE_64] << (64 - (PARAM_N & 63)));
+		o[i] = a[i] ^ r ^ carry;
+	}
+
+	o[VEC_N_SIZE_64 - 1] &= RED_MASK;
 }
 
 /**
@@ -81,7 +62,7 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_1(__m128i *C, __m128i *A, __m128i *B) {
+static inline void karat_mult_1(__m128i *C, __m128i *A, __m128i *B) {
 	__m128i D1[2];
 	__m128i D0[2], D2[2];
 	__m128i Al = _mm_loadu_si128(A);
@@ -138,7 +119,7 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_2(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_2(__m256i *C, __m256i *A, __m256i *B) {
 	__m256i D0[2],D1[2],D2[2],SAA,SBB;
 	__m128i *A128 = (__m128i *)A, *B128 = (__m128i *)B;
 
@@ -168,7 +149,7 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_4(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_4(__m256i *C, __m256i *A, __m256i *B) {
 	__m256i D0[4],D1[4],D2[4],SAA[2],SBB[2];
 
 	karat_mult_2( D0, A,B);
@@ -205,24 +186,25 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_8(__m256i * C, __m256i * A, __m256i * B) {
+static inline void karat_mult_8(__m256i * C, __m256i * A, __m256i * B) {
 	__m256i D0[8],D1[8],D2[8],SAA[4],SBB[4];
+	int32_t i, is, is2, is3;
 
 	karat_mult_4( D0, A,B);
 	karat_mult_4(D2, A + 4, B + 4);
 
-	for (int32_t i = 0 ; i < 4 ; i++) {
-		int is = i + 4;
+	for (i = 0 ; i < 4 ; i++) {
+		is = i + 4;
 		SAA[i] = A[i] ^ A[is];
 		SBB[i] = B[i] ^ B[is];
 	}
 
 	karat_mult_4(D1, SAA, SBB);
 
-	for (int32_t i = 0 ; i < 4 ; i++) {
-		int32_t is = i + 4;
-		int32_t is2 = is + 4;
-		int32_t is3 = is2 + 4;
+	for (i = 0 ; i < 4 ; i++) {
+		is = i + 4;
+		is2 = is + 4;
+		is3 = is2 + 4;
 
 		__m256i middle = _mm256_xor_si256(D0[is], D2[i]);
 
@@ -244,24 +226,25 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_16(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_16(__m256i *C, __m256i *A, __m256i *B) {
 	__m256i D0[16],D1[16],D2[16],SAA[8],SBB[8];
+	int32_t i, is, is2, is3;
 
 	karat_mult_8( D0, A,B);
 	karat_mult_8(D2, A + 8, B + 8);
 
-	for (int32_t i = 0 ; i < 8 ; i++) {
-		int32_t is = i + 8;
+	for (i = 0 ; i < 8 ; i++) {
+		is = i + 8;
 		SAA[i] = A[i] ^ A[is];
 		SBB[i] = B[i] ^ B[is];
 	}
 
 	karat_mult_8( D1, SAA, SBB);
 
-	for (int32_t i = 0 ; i < 8 ; i++) {
-		int32_t is = i + 8;
-		int32_t is2 = is + 8;
-		int32_t is3 = is2 + 8;
+	for (i = 0 ; i < 8 ; i++) {
+		is = i + 8;
+		is2 = is + 8;
+		is3 = is2 + 8;
 
 		__m256i middle = _mm256_xor_si256(D0[is], D2[i]);
 
@@ -283,24 +266,25 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_32(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_32(__m256i *C, __m256i *A, __m256i *B) {
 	__m256i D0[32],D1[32],D2[32],SAA[16],SBB[16];
+	int32_t i, is, is2, is3;
 
 	karat_mult_16( D0, A, B);
 	karat_mult_16(D2, A + 16, B + 16);
 
-	for (int32_t i = 0 ; i < 16 ; i++) {
-		int is = i + 16;
+	for (i = 0 ; i < 16 ; i++) {
+		is = i + 16;
 		SAA[i] = A[i] ^ A[is];
 		SBB[i] = B[i] ^ B[is];
 	}
 
 	karat_mult_16( D1, SAA, SBB);
 
-	for (int32_t i = 0 ; i < 16 ; i++) {
-		int32_t is = i + 16;
-		int32_t is2 = is + 16;
-		int32_t is3 = is2 + 16;
+	for (i = 0 ; i < 16 ; i++) {
+		is = i + 16;
+		is2 = is + 16;
+		is3 = is2 + 16;
 
 		__m256i middle = _mm256_xor_si256(D0[is], D2[i]);
 
@@ -328,7 +312,7 @@
 
 	for (int32_t i = 1 ; i < 2 * (size << 2) ;i++) {
 		B[i] = B[i - 1] ^ A[i];
-    	}
+	}
 }
 
 
@@ -342,17 +326,22 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-void TOOM3Mult(uint64_t* Out, const uint64_t* A, const uint64_t* B) {
+static void TOOM3Mult(__m256i * Out, const uint64_t* A, const uint64_t* B) {
 	static __m256i U0[T_TM3_3W_256], V0[T_TM3_3W_256], U1[T_TM3_3W_256], V1[T_TM3_3W_256], U2[T_TM3_3W_256], V2[T_TM3_3W_256];
 	static __m256i W0[2 * (T_TM3_3W_256)], W1[2 * (T_TM3_3W_256)], W2[2 * (T_TM3_3W_256)], W3[2 * (T_TM3_3W_256)], W4[2 * (T_TM3_3W_256)];
 	static __m256i tmp[2 * (T_TM3_3W_256)];
 	static __m256i ro256[6 * (T_TM3_3W_256)];
-	const __m256i zero = (__m256i){0ul,0ul,0ul,0ul};
+	const __m256i zero = _mm256_setzero_si256();
+	int64_t *U1_64;
+	int64_t *U2_64;
+	int64_t *V1_64;
+	int64_t *V2_64;
 	int32_t T2 = T_TM3_3W_64 << 1;
+	int32_t i, i4, i41, i42;
 
-	for (int32_t i = 0 ; i < T_TM3_3W_256 - 1 ; i++) {
-		int32_t i4 = i << 2;
-		int32_t i42 = i4 - 2;
+	for (i = 0 ; i < T_TM3_3W_256 - 1 ; i++) {
+		i4 = i << 2;
+		i42 = i4 - 2;
 		U0[i] = _mm256_lddqu_si256((__m256i const *)(& A[i4]));
 		V0[i] = _mm256_lddqu_si256((__m256i const *)(& B[i4]));
 		U1[i] = _mm256_lddqu_si256((__m256i const *)(& A[i42 + T_TM3_3W_64]));
@@ -361,22 +350,22 @@
 		V2[i] = _mm256_lddqu_si256((__m256i const *)(& B[i4 + T2 - 4]));
 	}
 
-	for (int32_t i = T_TM3_3W_256 - 1 ; i < T_TM3_3W_256 ; i++) {
-		int32_t i4 = i << 2;
-		int32_t i41 = i4 + 1;
-		U0[i]= (__m256i){A[i4],A[i41],0x0ul,0x0ul};
-		V0[i]= (__m256i){B[i4],B[i41],0x0ul,0x0ul};
-		U1[i]= (__m256i){A[i4 + T_TM3_3W_64 - 2],A[i41 + T_TM3_3W_64 - 2],0x0ul,0x0ul};
-		V1[i]= (__m256i){B[i4 + T_TM3_3W_64 - 2],B[i41 + T_TM3_3W_64 - 2],0x0ul,0x0ul};
-		U2[i]= (__m256i){A[i4 - 4 + T2],A[i4 - 3 + T2],0x0ul,0x0ul};
-		V2[i]= (__m256i){B[i4 - 4 + T2],B[i4 - 3 + T2],0x0ul,0x0ul};
+	for (i = T_TM3_3W_256 - 1 ; i < T_TM3_3W_256 ; i++) {
+		i4 = i << 2;
+		i41 = i4 + 1;
+		U0[i]= _mm256_set_epi64x(0,0,A[i41],A[i4]);
+		V0[i]= _mm256_set_epi64x(0,0,B[i41],B[i4]);
+		U1[i]= _mm256_set_epi64x(0,0,A[i41+T_TM3_3W_64-2],A[i4+T_TM3_3W_64-2]);
+		V1[i]= _mm256_set_epi64x(0,0,B[i41+T_TM3_3W_64-2],B[i4+T_TM3_3W_64-2]);
+		U2[i]= _mm256_set_epi64x(0,0,A[i4-3+T2],A[i4-4+T2]);
+		V2[i]= _mm256_set_epi64x(0,0,B[i4-3+T2],B[i4-4+T2]);
 	}
 
 	// Evaluation phase : x= X^64
 	// P(X): P0=(0); P1=(1); P2=(x); P3=(1+x); P4=(\infty)
 	// Evaluation: 5*2 add, 2*2 shift; 5 mul (n)
 	//W3 = U2 + U1 + U0 ; W2 = V2 + V1 + V0
-	for (int32_t i = 0 ; i < T_TM3_3W_256 ; i++) {
+	for (i = 0 ; i < T_TM3_3W_256 ; i++) {
 		W3[i]=U0[i] ^ U1[i] ^ U2[i];
 		W2[i]=V0[i] ^ V1[i] ^ V2[i];
 	}
@@ -385,38 +374,32 @@
 	karat_mult_32( W1, W2, W3);
 
 	//W0 =(U1 + U2*x)*x ; W4 =(V1 + V2*x)*x (SIZE = T_TM3_3W_256 !)
-	uint64_t *U1_64 = ((uint64_t *) U1);
-	uint64_t *U2_64 = ((uint64_t *) U2);
+	U1_64 = ((int64_t *) U1);
+	U2_64 = ((int64_t *) U2);
 
-	uint64_t *V1_64 = ((uint64_t *) V1);
-	uint64_t *V2_64 = ((uint64_t *) V2);
+	V1_64 = ((int64_t *) V1);
+	V2_64 = ((int64_t *) V2);
 
-	W0[0] = (__m256i){0ul,U1_64[0],U1_64[1] ^ U2_64[0],U1_64[2] ^ U2_64[1]};
-	W4[0] = (__m256i){0ul,V1_64[0],V1_64[1] ^ V2_64[0],V1_64[2] ^ V2_64[1]};
+	W0[0] = _mm256_set_epi64x(U1_64[2]^U2_64[1], U1_64[1]^U2_64[0], U1_64[0], 0);
+	W4[0] = _mm256_set_epi64x(V1_64[2]^V2_64[1], V1_64[1]^V2_64[0], V1_64[0], 0);
 
-	U1_64 = ((uint64_t *) U1) - 1;
-	U2_64 = ((uint64_t *) U2) - 2;
+	for (i = 1 ; i < T_TM3_3W_256 ; i++) {
+		i4 = i << 2;
+		W0[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4-1]));
+		W0[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4-2]));
 
-	V1_64 = ((uint64_t *) V1) - 1;
-	V2_64 = ((uint64_t *) V2) - 2;
-
-	for (int32_t i = 1 ; i < T_TM3_3W_256 ; i++) {
-		int i4 = i << 2;
-		W0[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4]));
-		W0[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4]));
-
-		W4[i] = _mm256_lddqu_si256((__m256i const *)(& V1_64[i4]));
-		W4[i] ^= _mm256_lddqu_si256((__m256i const *)(& V2_64[i4]));
+		W4[i] = _mm256_lddqu_si256((__m256i const *)(& V1_64[i4-1]));
+		W4[i] ^= _mm256_lddqu_si256((__m256i const *)(& V2_64[i4-2]));
 	}
 
 	//W3 = W3 + W0      ; W2 = W2 + W4
-	for (int32_t i = 0 ; i < T_TM3_3W_256 ; i++) {
+	for (i = 0 ; i < T_TM3_3W_256 ; i++) {
 		W3[i] ^= W0[i];
 		W2[i] ^= W4[i];
 	}
 
 	//W0 = W0 + U0      ; W4 = W4 + V0
-	for (int32_t i = 0 ; i < T_TM3_3W_256 ; i++) {
+	for (i = 0 ; i < T_TM3_3W_256 ; i++) {
 		W0[i] ^= U0[i];
 		W4[i] ^= V0[i];
 	}
@@ -424,9 +407,9 @@
 	//W3 = W3 * W2      ; W2 = W0 * W4
 	karat_mult_32(tmp, W3, W2);
 
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
 		W3[i] = tmp[i];
-    	}
+	}
 
 	karat_mult_32(W2, W0, W4);
 	//W4 = U2 * V2      ; W0 = U0 * V0
@@ -436,64 +419,64 @@
 	// Interpolation phase
 	// 9 add, 1 shift, 1 Smul, 2 Sdiv (2n)
 	//W3 = W3 + W2
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
 		W3[i] ^= W2[i];
 	}
 
 	//W1 = W1 + W0
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
 		W1[i] ^= W0[i];
 	}
 
 	//W2 =(W2 + W0)/x -> x = X^64
-	U1_64 = ((uint64_t *) W2) + 1;
-	U2_64 = ((uint64_t *) W0) + 1;
-	for (int32_t i = 0 ; i < (T_TM3_3W_256 << 1) ; i++) {
-			int32_t i4 = i << 2;
-			W2[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4]));
-			W2[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4]));
+	U1_64 = ((int64_t *) W2);
+	U2_64 = ((int64_t *) W0);
+	for (i = 0 ; i < (T_TM3_3W_256 << 1) ; i++) {
+			i4 = i << 2;
+			W2[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4+1]));
+			W2[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4+1]));
 	}
 
 	//W2 =(W2 + W3 + W4*(x^3+1))/(x+1)
-	U1_64 = ((uint64_t *) W4);
+	U1_64 = ((int64_t *) W4);
 	__m256i *U1_256 = (__m256i *) (U1_64+1);
-	tmp[0] = W2[0]^W3[0]^W4[0]^(__m256i){0x0ul,0x0ul,0x0ul,U1_64[0]};
+	tmp[0] = W2[0]^W3[0]^W4[0]^_mm256_set_epi64x(U1_64[0],0,0,0);
 
-	for (int32_t i = 1 ; i < (T_TM3_3W_256 << 1) - 1 ;i++) {
-        	tmp[i] = W2[i] ^ W3[i] ^ W4[i] ^ U1_256[i - 1];
+	for (i = 1 ; i < (T_TM3_3W_256 << 1) - 1 ;i++) {
+		tmp[i] = W2[i] ^ W3[i] ^ W4[i] ^ _mm256_lddqu_si256(&U1_256[i - 1]);
 	}
 
 	divByXplus1(W2,tmp,T_TM3_3W_256);
 	W2[2 * (T_TM3_3W_256) - 1] = zero;
 
 	//W3 =(W3 + W1)/(x*(x+1))
-	U1_64 = (uint64_t *) W3;
+	U1_64 = (int64_t *) W3;
 	U1_256 = (__m256i *) (U1_64 + 1);
 
-	U2_64 = (uint64_t *) W1;
+	U2_64 = (int64_t *) W1;
 	__m256i * U2_256 = (__m256i *) (U2_64 + 1);
 
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) - 1 ; i++) {
-		tmp[i] = U1_256[i] ^ U2_256[i];
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) - 1 ; i++) {
+		tmp[i] = _mm256_lddqu_si256(&U1_256[i]) ^ _mm256_lddqu_si256(&U2_256[i]);
 	}
 
 	divByXplus1(W3,tmp,T_TM3_3W_256);
 	W3[2 * (T_TM3_3W_256) - 1] = zero;
 
 	//W1 = W1 + W4 + W2
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
 		W1[i] ^= W2[i] ^ W4[i];
 	}
 
 	//W2 = W2 + W3
-	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
+	for (i = 0 ; i < 2 * (T_TM3_3W_256) ; i++) {
 		W2[i] ^= W3[i];
 	}
 
 	// Recomposition
 	//W  = W0+ W1*x+ W2*x^2+ W3*x^3 + W4*x^4
 	//W0, W1, W4 of size 2*T_TM3_3W_256, W2 and W3 of size 2*(T_TM3_3W_256)
-	for (int32_t i = 0 ; i < (T_TM3_3W_256 << 1) - 1 ; i++) {
+	for (i = 0 ; i < (T_TM3_3W_256 << 1) - 1 ; i++) {
 		ro256[i] = W0[i];
 		ro256[i + 2 * T_TM3_3W_256 - 1] = W2[i];
 		ro256[i + 4 * T_TM3_3W_256 - 2] = W4[i];
@@ -503,20 +486,19 @@
 	ro256[(T_TM3_3W_256 << 2) - 2] = W2[(T_TM3_3W_256 << 1) - 1] ^ W4[0];
 	ro256[(T_TM3_3W_256 * 6) - 3] = W4[(T_TM3_3W_256 << 1) - 1];
 
-	U1_64 = ((uint64_t *) &ro256[T_TM3_3W_256]);
+	U1_64 = ((int64_t *) &ro256[T_TM3_3W_256]);
 	U1_256 = (__m256i *) (U1_64 - 2);
 
-	U2_64 = ((uint64_t *) &ro256[3 * T_TM3_3W_256 - 1]);
+	U2_64 = ((int64_t *) &ro256[3 * T_TM3_3W_256 - 1]);
 	U2_256 = (__m256i *) (U2_64 - 2);
 
-	for (int32_t i = 0 ; i < T_TM3_3W_256 << 1 ; i++) {
-		U1_256[i] ^= W1[i];
-		U2_256[i] ^= W3[i];
+	for (i = 0 ; i < T_TM3_3W_256 << 1 ; i++) {
+		_mm256_storeu_si256(&U1_256[i], W1[i] ^ _mm256_lddqu_si256(&U1_256[i]));
+		_mm256_storeu_si256(&U2_256[i], W3[i] ^ _mm256_loadu_si256(&U2_256[i]));
 	}
 
-	for (int32_t i = 0 ; i < 6 * T_TM3_3W_256 - 2 ; i++) {
-		uint64_t *out64 = Out + (i << 2);
-		_mm256_storeu_si256((__m256i *)out64, ro256[i]);
+	for (i = 0 ; i < 2 * VEC_N_SIZE_256 + 1 ; i++) {
+		_mm256_storeu_si256(&Out[i], ro256[i]);
 	}
 }
 
@@ -533,12 +515,12 @@
  */
 void vect_mul(uint64_t *o, const uint64_t *a1, const uint64_t *a2) {
 	TOOM3Mult(a1_times_a2, a1, a2);
-	reduce(o, a1_times_a2);
+	reduce(o, (uint64_t *)a1_times_a2);
 
 	// clear all
 #ifdef __STDC_LIB_EXT1__
-	memset_s(a1_times_a2, 0, (VEC_N_SIZE_64 << 1) * sizeof(uint64_t));
+	memset_s(a1_times_a2, 0, (2 * VEC_N_SIZE_256 + 1) * sizeof(__m256i));
 #else
-	memset(a1_times_a2, 0, (VEC_N_SIZE_64 << 1) * sizeof(uint64_t));
+	memset(a1_times_a2, 0, (2 * VEC_N_SIZE_256 + 1) * sizeof(__m256i));
 #endif
 }

