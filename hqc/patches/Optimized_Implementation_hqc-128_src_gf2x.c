--- hqc-2020-05-29/Optimized_Implementation/hqc-128/src/gf2x.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-128/src/gf2x.c
@@ -17,14 +17,14 @@
 #define VEC_N_ARRAY_SIZE_VEC CEIL_DIVIDE(PARAM_N, 256) /*!< The number of needed vectors to store PARAM_N bits*/
 #define WORD 64
 #define LAST64 (PARAM_N >> 6)
-uint64_t a1_times_a2[VEC_N_256_SIZE_64 << 1];
+uint64_t a1_times_a2[2 * VEC_N_256_SIZE_64 + 1];
 uint64_t tmp_reduce[VEC_N_ARRAY_SIZE_VEC << 2];
 __m256i *o256 = (__m256i *) tmp_reduce;
 uint64_t bloc64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
 uint64_t bit64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
 
 
-static inline void reduce(uint64_t *o, uint64_t *a);
+static inline void reduce(uint64_t *o, const uint64_t *a);
 inline static void karat_mult_1(__m128i *C, __m128i *A, __m128i *B);
 inline static void karat_mult_2(__m256i *C, __m256i *A, __m256i *B);
 inline static void karat_mult_4(__m256i *C, __m256i *A, __m256i *B);
@@ -32,7 +32,7 @@
 inline static void karat_mult_16(__m256i *C, __m256i *A, __m256i *B);
 inline static void karat_mult_32(__m256i *C, __m256i *A, __m256i *B);
 static inline void divByXplus1(__m256i *out,__m256i *in,int size);
-void TOOM3Mult(uint64_t* Out, const uint64_t *A, const uint64_t *B);
+static void TOOM3Mult(uint64_t* Out, const uint64_t *A, const uint64_t *B);
 
 
 
@@ -44,7 +44,7 @@
  * @param[out] o Pointer to the result
  * @param[in] a Pointer to the polynomial a(x)
  */
-static inline void reduce(uint64_t *o, uint64_t *a) {
+static inline void reduce(uint64_t *o, const uint64_t *a) {
 	__m256i r256, carry256;
 	__m256i *a256 = (__m256i *) a;
 	static const int32_t dec64 = PARAM_N & 0x3f;
@@ -342,7 +342,7 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-void TOOM3Mult(uint64_t* Out, const uint64_t* A, const uint64_t* B) {
+static void TOOM3Mult(uint64_t* Out, const uint64_t* A, const uint64_t* B) {
 	static __m256i U0[T_TM3_3W_256], V0[T_TM3_3W_256], U1[T_TM3_3W_256], V1[T_TM3_3W_256], U2[T_TM3_3W_256], V2[T_TM3_3W_256];
 	static __m256i W0[2 * (T_TM3_3W_256)], W1[2 * (T_TM3_3W_256)], W2[2 * (T_TM3_3W_256)], W3[2 * (T_TM3_3W_256)], W4[2 * (T_TM3_3W_256)];
 	static __m256i tmp[2 * (T_TM3_3W_256)];
@@ -385,28 +385,28 @@
 	karat_mult_32( W1, W2, W3);
 
 	//W0 =(U1 + U2*x)*x ; W4 =(V1 + V2*x)*x (SIZE = T_TM3_3W_256 !)
-	uint64_t *U1_64 = ((uint64_t *) U1);
-	uint64_t *U2_64 = ((uint64_t *) U2);
+	int64_t *U1_64 = ((int64_t *) U1);
+	int64_t *U2_64 = ((int64_t *) U2);
 
-	uint64_t *V1_64 = ((uint64_t *) V1);
-	uint64_t *V2_64 = ((uint64_t *) V2);
+	int64_t *V1_64 = ((int64_t *) V1);
+	int64_t *V2_64 = ((int64_t *) V2);
 
-	W0[0] = (__m256i){0ul,U1_64[0],U1_64[1] ^ U2_64[0],U1_64[2] ^ U2_64[1]};
-	W4[0] = (__m256i){0ul,V1_64[0],V1_64[1] ^ V2_64[0],V1_64[2] ^ V2_64[1]};
+	W0[0] = _mm256_set_epi64x(U1_64[2]^U2_64[1], U1_64[1]^U2_64[0], U1_64[0], 0);
+	W4[0] = _mm256_set_epi64x(V1_64[2]^V2_64[1], V1_64[1]^V2_64[0], V1_64[0], 0);
 
-	U1_64 = ((uint64_t *) U1) - 1;
-	U2_64 = ((uint64_t *) U2) - 2;
+	U1_64 = ((int64_t *) U1);
+	U2_64 = ((int64_t *) U2);
 
-	V1_64 = ((uint64_t *) V1) - 1;
-	V2_64 = ((uint64_t *) V2) - 2;
+	V1_64 = ((int64_t *) V1);
+	V2_64 = ((int64_t *) V2);
 
 	for (int32_t i = 1 ; i < T_TM3_3W_256 ; i++) {
 		int i4 = i << 2;
-		W0[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4]));
-		W0[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4]));
+		W0[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4-1]));
+		W0[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4-2]));
 
-		W4[i] = _mm256_lddqu_si256((__m256i const *)(& V1_64[i4]));
-		W4[i] ^= _mm256_lddqu_si256((__m256i const *)(& V2_64[i4]));
+		W4[i] = _mm256_lddqu_si256((__m256i const *)(& V1_64[i4-1]));
+		W4[i] ^= _mm256_lddqu_si256((__m256i const *)(& V2_64[i4-2]));
 	}
 
 	//W3 = W3 + W0      ; W2 = W2 + W4
@@ -446,35 +446,35 @@
 	}
 
 	//W2 =(W2 + W0)/x -> x = X^64
-	U1_64 = ((uint64_t *) W2) + 1;
-	U2_64 = ((uint64_t *) W0) + 1;
+	U1_64 = ((int64_t *) W2);
+	U2_64 = ((int64_t *) W0);
 	for (int32_t i = 0 ; i < (T_TM3_3W_256 << 1) ; i++) {
 			int32_t i4 = i << 2;
-			W2[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4]));
-			W2[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4]));
+			W2[i] = _mm256_lddqu_si256((__m256i const *)(& U1_64[i4+1]));
+			W2[i] ^= _mm256_lddqu_si256((__m256i const *)(& U2_64[i4+1]));
 	}
 
 	//W2 =(W2 + W3 + W4*(x^3+1))/(x+1)
-	U1_64 = ((uint64_t *) W4);
+	U1_64 = ((int64_t *) W4);
 	__m256i *U1_256 = (__m256i *) (U1_64+1);
 	tmp[0] = W2[0]^W3[0]^W4[0]^(__m256i){0x0ul,0x0ul,0x0ul,U1_64[0]};
 
 	for (int32_t i = 1 ; i < (T_TM3_3W_256 << 1) - 1 ;i++) {
-        	tmp[i] = W2[i] ^ W3[i] ^ W4[i] ^ U1_256[i - 1];
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
 
 	for (int32_t i = 0 ; i < 2 * (T_TM3_3W_256) - 1 ; i++) {
-		tmp[i] = U1_256[i] ^ U2_256[i];
+		tmp[i] = _mm256_lddqu_si256(&U1_256[i]) ^ _mm256_lddqu_si256(&U2_256[i]);
 	}
 
 	divByXplus1(W3,tmp,T_TM3_3W_256);
@@ -503,15 +503,15 @@
 	ro256[(T_TM3_3W_256 << 2) - 2] = W2[(T_TM3_3W_256 << 1) - 1] ^ W4[0];
 	ro256[(T_TM3_3W_256 * 6) - 3] = W4[(T_TM3_3W_256 << 1) - 1];
 
-	U1_64 = ((uint64_t *) &ro256[T_TM3_3W_256]);
+	U1_64 = ((int64_t *) &ro256[T_TM3_3W_256]);
 	U1_256 = (__m256i *) (U1_64 - 2);
 
-	U2_64 = ((uint64_t *) &ro256[3 * T_TM3_3W_256 - 1]);
+	U2_64 = ((int64_t *) &ro256[3 * T_TM3_3W_256 - 1]);
 	U2_256 = (__m256i *) (U2_64 - 2);
 
 	for (int32_t i = 0 ; i < T_TM3_3W_256 << 1 ; i++) {
-		U1_256[i] ^= W1[i];
-		U2_256[i] ^= W3[i];
+		_mm256_storeu_si256(&U1_256[i], W1[i] ^ _mm256_lddqu_si256(&U1_256[i]));
+		_mm256_storeu_si256(&U2_256[i], W3[i] ^ _mm256_loadu_si256(&U2_256[i]));
 	}
 
 	for (int32_t i = 0 ; i < 6 * T_TM3_3W_256 - 2 ; i++) {

