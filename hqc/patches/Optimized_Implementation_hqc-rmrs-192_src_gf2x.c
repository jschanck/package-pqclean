--- upstream/Optimized_Implementation/hqc-rmrs-192/src/gf2x.c
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-192/src/gf2x.c
@@ -10,32 +10,18 @@
 #include <stdio.h>
 #include <immintrin.h>
 
-#define VEC_N_ARRAY_SIZE_VEC CEIL_DIVIDE(PARAM_N_MULT, 256) /*!< The number of needed vectors to store PARAM_N bits*/
-#define WORD 64
-#define LAST64 (PARAM_N >> 6)
-
-#define T_3W 4096
-#define T_3W_256 (T_3W>>8)
-#define T2_3W_256 (2*T_3W_256)
-
-#define TREC_3W 12288
-#define TREC_3W_256 (TREC_3W>>8)
-#define T2REC_3W_256 (2*TREC_3W_256)
-
-uint64_t a1_times_a2[VEC_N_256_SIZE_64 << 1];
-uint64_t tmp_reduce[VEC_N_ARRAY_SIZE_VEC << 2];
-__m256i *o256 = (__m256i *) tmp_reduce;
-uint64_t bloc64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
-uint64_t bit64[PARAM_OMEGA_R]; // Allocation with the biggest possible weight
-
-static inline void reduce(uint64_t *o, uint64_t *a);
-inline static void karat_mult_1(__m128i *C, __m128i *A, __m128i *B);
-inline static void karat_mult_2(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_4(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_8(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult_16(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_three_way_mult(__m256i *C, __m256i *A, __m256i *B);
-inline static void karat_mult9(uint64_t *C, const uint64_t *A, const uint64_t *B);
+
+#define VEC_N_SPLIT_3x3 CEIL_DIVIDE(PARAM_N/9, 256)
+#define VEC_N_SPLIT_3 (3*VEC_N_SPLIT_3x3)
+
+static inline void reduce(uint64_t *o, const __m256i *a);
+static inline void karat_mult_1(__m128i *C, const __m128i *A, const __m128i *B);
+static inline void karat_mult_2(__m256i *C, const __m256i *A, const __m256i *B);
+static inline void karat_mult_4(__m256i *C, const __m256i *A, const __m256i *B);
+static inline void karat_mult_8(__m256i *C, const __m256i *A, const __m256i *B);
+static inline void karat_mult_16(__m256i *C, const __m256i *A, const __m256i *B);
+static inline void karat_three_way_mult(__m256i *C, const __m256i *A, const __m256i *B);
+static inline void karat_mult9(__m256i *C, const aligned_vec_t *A, const aligned_vec_t *B);
 
 
 /**
@@ -46,34 +32,33 @@
  * @param[out] o Pointer to the result
  * @param[in] a Pointer to the polynomial a(x)
  */
-static inline void reduce(uint64_t *o, uint64_t *a) {
+static inline void reduce(uint64_t *o, const __m256i *a256) {
+	size_t i, i2;
 	__m256i r256, carry256;
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
+	__m256i *o256 = (__m256i *)o;
+	const uint64_t *a64 = (const uint64_t *)a256;
+	uint64_t r, carry;
+
+  i2 = 0;
+	for (i = (PARAM_N >> 6); i < (PARAM_N >> 5) - 4 ; i += 4) {
+		r256 = _mm256_lddqu_si256((const __m256i *) (& a64[i]));
+		r256 = _mm256_srli_epi64(r256, PARAM_N&63);
+		carry256 = _mm256_lddqu_si256((const __m256i *) (& a64[i + 1]));
+		carry256 = _mm256_slli_epi64(carry256, (-PARAM_N)&63);
 		r256 ^= carry256;
-		i2 = (i - LAST64) >> 2;
-		o256[i2] = a256[i2] ^ r256;
+		_mm256_storeu_si256(&o256[i2], a256[i2] ^ r256);
+		i2 += 1;
 	}
 
-	i = i - LAST64;
-
-	for (; i < LAST64 + 1 ; i++) {
-		uint64_t r = a[i + LAST64] >> dec64;
-		uint64_t carry = a[i + LAST64 + 1] << d0;
+	i = i - (PARAM_N >> 6);
+	for (; i < (PARAM_N >> 6) + 1 ; i++) {
+		r = a64[i + (PARAM_N >> 6)] >> (PARAM_N&63);
+		carry = a64[i + (PARAM_N >> 6) + 1] << ((-PARAM_N)&63);
 		r ^= carry;
-		tmp_reduce[i] = a[i] ^ r;
+		o[i] = a64[i] ^ r;
 	}
 
-	tmp_reduce[LAST64] &= RED_MASK;
-	memcpy(o, tmp_reduce, VEC_N_SIZE_BYTES);
+	o[PARAM_N >> 6] &= RED_MASK;
 }
 
 
@@ -87,7 +72,7 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_1(__m128i *C, __m128i *A, __m128i *B) {
+static inline void karat_mult_1(__m128i *C, const __m128i *A, const __m128i *B) {
 	__m128i D1[2];
 	__m128i D0[2], D2[2];
 	__m128i Al = _mm_loadu_si128(A);
@@ -144,18 +129,19 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_2(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_2(__m256i *C, const __m256i *A, const __m256i *B) {
 	__m256i D0[2], D1[2], D2[2], SAA, SBB;
-	__m128i *A128 = (__m128i *)A, *B128 = (__m128i *)B;
-	
+	const __m128i *A128 = (const __m128i *)A;
+	const __m128i *B128 = (const __m128i *)B;
+	__m256i middle;
+
 	karat_mult_1((__m128i *) D0, A128, B128);
 	karat_mult_1((__m128i *) D2, A128 + 2, B128 + 2);
 
-	SAA = _mm256_xor_si256(A[0], A[1]);
-	SBB = _mm256_xor_si256(B[0], B[1]);
-
+	SAA = A[0] ^ A[1];
+	SBB = B[0] ^ B[1];
 	karat_mult_1((__m128i *) D1,(__m128i *) &SAA,(__m128i *) &SBB);
-	__m256i middle = _mm256_xor_si256(D0[1], D2[0]);
+	middle = _mm256_xor_si256(D0[1], D2[0]);
 
 	C[0] = D0[0];
 	C[1] = middle ^ D0[0] ^ D1[0];
@@ -164,7 +150,6 @@
 }
 
 
-
 /**
  * @brief Compute C(x) = A(x)*B(x)
  *
@@ -174,8 +159,10 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_4(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_4(__m256i *C, const __m256i *A, const __m256i *B) {
 	__m256i D0[4], D1[4], D2[4], SAA[2], SBB[2];
+	__m256i middle0;
+	__m256i middle1;
 
 	karat_mult_2(D0, A, B);
 	karat_mult_2(D2, A + 2, B + 2);
@@ -185,10 +172,10 @@
 	SAA[1] = A[1] ^ A[3];
 	SBB[1] = B[1] ^ B[3];
 
-	karat_mult_2( D1, SAA, SBB);
+	karat_mult_2(D1, SAA, SBB);
 
-	__m256i middle0 = _mm256_xor_si256(D0[2], D2[0]);
-	__m256i middle1 = _mm256_xor_si256(D0[3], D2[1]);
+	middle0 = _mm256_xor_si256(D0[2], D2[0]);
+	middle1 = _mm256_xor_si256(D0[3], D2[1]);
 
 	C[0] = D0[0];
 	C[1] = D0[1];
@@ -211,26 +198,28 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_8(__m256i *C, __m256i *A, __m256i *B) {
+static inline void karat_mult_8(__m256i *C, const __m256i *A, const __m256i *B) {
+	size_t i, is, is2, is3;
 	__m256i D0[8], D1[8], D2[8], SAA[4], SBB[4];
+	__m256i middle;
 
 	karat_mult_4(D0, A, B);
 	karat_mult_4(D2, A + 4, B + 4);
 
-	for (int32_t i = 0 ; i < 4 ; i++) {
-		int32_t is = i + 4;
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
 
-		__m256i middle = _mm256_xor_si256(D0[is], D2[i]);
+		middle = _mm256_xor_si256(D0[is], D2[i]);
 
 		C[i]   = D0[i];
 		C[is]  = middle ^ D0[i] ^ D1[i];
@@ -250,26 +239,28 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_mult_16(__m256i *C, __m256i *A, __m256i *B) {
+inline static void karat_mult_16(__m256i *C, const __m256i *A, const __m256i *B) {
+	size_t i, is, is2, is3;
+	__m256i middle;
 	__m256i D0[16], D1[16], D2[16], SAA[8], SBB[8];
 
 	karat_mult_8(D0, A, B);
 	karat_mult_8(D2, A + 8, B + 8);
 
-	for (int32_t i = 0 ; i < 8 ; i++) {
-		int32_t is = i + 8;
+	for (i = 0 ; i < 8 ; i++) {
+		is = i + 8;
 		SAA[i] = A[i] ^ A[is];
 		SBB[i] = B[i] ^ B[is];
 	}
 
 	karat_mult_8(D1, SAA, SBB);
 
-	for (int32_t i = 0 ; i < 8 ; i++) {
-		int32_t is = i + 8;
-		int32_t is2 = is + 8;
-		int32_t is3 = is2 + 8;
+	for (i = 0 ; i < 8 ; i++) {
+		is = i + 8;
+		is2 = is + 8;
+		is3 = is2 + 8;
 
-		__m256i middle = _mm256_xor_si256(D0[is], D2[i]);
+		middle = D0[is] ^ D2[i];
 
 		C[i]   = D0[i];
 		C[is]  = middle ^ D0[i] ^ D1[i];
@@ -279,7 +270,6 @@
 }
 
 
-
 /**
  * @brief Compute C(x) = A(x)*B(x)
  *
@@ -289,27 +279,29 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-inline static void karat_three_way_mult(__m256i *Out, __m256i *A, __m256i *B) {
-	__m256i *a0, *b0, *a1, *b1, *a2, *b2;
-	__m256i aa01[T_3W_256], bb01[T_3W_256], aa02[T_3W_256], bb02[T_3W_256], aa12[T_3W_256], bb12[T_3W_256];
-	__m256i D0[T2_3W_256], D1[T2_3W_256], D2[T2_3W_256], D3[T2_3W_256], D4[T2_3W_256], D5[T2_3W_256];
-	__m256i ro256[3 * T2_3W_256];
+static inline void karat_three_way_mult(__m256i *C, const __m256i *A, const __m256i *B) {
+	size_t i, j;
+	const __m256i *a0, *b0, *a1, *b1, *a2, *b2;
+	__m256i aa01[VEC_N_SPLIT_3x3], bb01[VEC_N_SPLIT_3x3], aa02[VEC_N_SPLIT_3x3], bb02[VEC_N_SPLIT_3x3], aa12[VEC_N_SPLIT_3x3], bb12[VEC_N_SPLIT_3x3];
+	__m256i D0[2*VEC_N_SPLIT_3x3], D1[2*VEC_N_SPLIT_3x3], D2[2*VEC_N_SPLIT_3x3], D3[2*VEC_N_SPLIT_3x3], D4[2*VEC_N_SPLIT_3x3], D5[2*VEC_N_SPLIT_3x3];
+	__m256i ro256[6*VEC_N_SPLIT_3x3];
+	__m256i middle0;
 
 	a0 = A;
-	a1 = A + T_3W_256;
-	a2 = A + (T_3W_256 << 1);
+	a1 = A + VEC_N_SPLIT_3x3;
+	a2 = A + (VEC_N_SPLIT_3x3 << 1);
 
 	b0 = B;
-	b1 = B + T_3W_256;
-	b2 = B + (T_3W_256 << 1);
+	b1 = B + VEC_N_SPLIT_3x3;
+	b2 = B + (VEC_N_SPLIT_3x3 << 1);
 
-	for (int32_t i = 0 ; i < T_3W_256 ; i++) {
+	for (i = 0 ; i < VEC_N_SPLIT_3x3 ; i++) {
 		aa01[i] = a0[i] ^ a1[i];
 		bb01[i] = b0[i] ^ b1[i];
-		
+
 		aa12[i] = a2[i] ^ a1[i];
 		bb12[i] = b2[i] ^ b1[i];
-		
+
 		aa02[i] = a0[i] ^ a2[i];
 		bb02[i] = b0[i] ^ b2[i];
 	}
@@ -317,25 +309,25 @@
 	karat_mult_16(D0, a0, b0);
 	karat_mult_16(D1, a1, b1);
 	karat_mult_16(D2, a2, b2);
-	
+
 	karat_mult_16(D3, aa01, bb01);
 	karat_mult_16(D4, aa02, bb02);
 	karat_mult_16(D5, aa12, bb12);
 
-	for (int32_t i = 0 ; i < T_3W_256 ; i++) {
-		int32_t j = i + T_3W_256;
-		__m256i middle0 = D0[i] ^ D1[i] ^ D0[j];
+	for (i = 0 ; i < VEC_N_SPLIT_3x3 ; i++) {
+		j = i + VEC_N_SPLIT_3x3;
+		middle0 = D0[i] ^ D1[i] ^ D0[j];
 		ro256[i] = D0[i];
 		ro256[j]  = D3[i] ^ middle0;
-		ro256[j + T_3W_256] = D4[i] ^ D2[i] ^ D3[j] ^ D1[j] ^ middle0;
+		ro256[j + VEC_N_SPLIT_3x3] = D4[i] ^ D2[i] ^ D3[j] ^ D1[j] ^ middle0;
 		middle0 = D1[j] ^ D2[i] ^ D2[j];
-		ro256[j + (T_3W_256 << 1)] = D5[i] ^ D4[j] ^ D0[j] ^ D1[i] ^ middle0;
-		ro256[i + (T_3W_256 << 2)] = D5[j] ^ middle0;
-		ro256[j + (T_3W_256 << 2)] = D2[j];
+		ro256[j + (VEC_N_SPLIT_3x3 << 1)] = D5[i] ^ D4[j] ^ D0[j] ^ D1[i] ^ middle0;
+		ro256[i + (VEC_N_SPLIT_3x3 << 2)] = D5[j] ^ middle0;
+		ro256[j + (VEC_N_SPLIT_3x3 << 2)] = D2[j];
 	}
 
-	for (int32_t i = 0 ; i < T2REC_3W_256 ; i++) {
-		Out[i] = ro256[i];
+	for (i = 0 ; i < 2*VEC_N_SPLIT_3 ; i++) {
+		C[i] = ro256[i];
 	}
 }
 
@@ -350,21 +342,22 @@
  * @param[in] A Pointer to the polynomial A(x)
  * @param[in] B Pointer to the polynomial B(x)
  */
-static inline void karat_mult9(uint64_t *Out, const uint64_t *A, const uint64_t *B) {
-	__m256i *A256 = (__m256i *)A, *B256 = (__m256i *)B,*C = (__m256i *)Out;
-	__m256i * a0, * b0, *a1, *b1, *a2, *b2;
-	__m256i aa01[TREC_3W_256], bb01[TREC_3W_256], aa02[TREC_3W_256], bb02[TREC_3W_256], aa12[TREC_3W_256], bb12[TREC_3W_256];
-	__m256i D0[T2REC_3W_256], D1[T2REC_3W_256], D2[T2REC_3W_256], D3[T2REC_3W_256], D4[T2REC_3W_256], D5[T2REC_3W_256];
-
-	a0 = A256;
-	a1 = A256 + TREC_3W_256;
-	a2 = A256 + T2REC_3W_256;
-	
-	b0 = B256;
-	b1 = B256 + TREC_3W_256;
-	b2 = B256 + T2REC_3W_256;
+static inline void karat_mult9(__m256i *C, const aligned_vec_t *A, const aligned_vec_t *B) {
+	size_t i,j;
+	const __m256i *a0, *b0, *a1, *b1, *a2, *b2;
+	__m256i aa01[VEC_N_SPLIT_3], bb01[VEC_N_SPLIT_3], aa02[VEC_N_SPLIT_3], bb02[VEC_N_SPLIT_3], aa12[VEC_N_SPLIT_3], bb12[VEC_N_SPLIT_3];
+	__m256i D0[2*VEC_N_SPLIT_3], D1[2*VEC_N_SPLIT_3], D2[2*VEC_N_SPLIT_3], D3[2*VEC_N_SPLIT_3], D4[2*VEC_N_SPLIT_3], D5[2*VEC_N_SPLIT_3];
+	__m256i middle0;
+
+	a0 = (__m256i *)(A->arr64);
+	a1 = a0+VEC_N_SPLIT_3;
+	a2 = a0+(2*VEC_N_SPLIT_3);
+
+	b0 = (__m256i *)(B->arr64);
+	b1 = b0+VEC_N_SPLIT_3;
+	b2 = b0+(2*VEC_N_SPLIT_3);
 
-	for (int32_t i = 0 ; i < TREC_3W_256 ; i++) {
+	for (i = 0 ; i < VEC_N_SPLIT_3 ; i++) {
 		aa01[i] = a0[i] ^ a1[i];
 		bb01[i] = b0[i] ^ b1[i];
 
@@ -383,16 +376,16 @@
 	karat_three_way_mult(D4, aa02, bb02);
 	karat_three_way_mult(D5, aa12, bb12);
 
-	for (int32_t i = 0 ; i < TREC_3W_256 ; i++) {
-		int32_t j = i + TREC_3W_256;
-		__m256i middle0 = D0[i] ^ D1[i] ^ D0[j];
+	for (i = 0 ; i < VEC_N_SPLIT_3 ; i++) {
+		j = i + VEC_N_SPLIT_3;
+		middle0 = D0[i] ^ D1[i] ^ D0[j];
 		C[i] = D0[i];
-		C[j] = D3[i] ^ middle0;
-		C[j + TREC_3W_256] = D4[i] ^ D2[i] ^ D3[j] ^ D1[j] ^ middle0;
+		C[j]  = D3[i] ^ middle0;
+		C[j + VEC_N_SPLIT_3] = D4[i] ^ D2[i] ^ D3[j] ^ D1[j] ^ middle0;
 		middle0 = D1[j] ^ D2[i] ^ D2[j];
-		C[j + (TREC_3W_256 << 1)] = D5[i] ^ D4[j] ^ D0[j] ^ D1[i] ^ middle0;
-		C[i + (TREC_3W_256 << 2)] = D5[j] ^ middle0;
-		C[j + (TREC_3W_256 << 2)] = D2[j];
+		C[j + (VEC_N_SPLIT_3 << 1)] = D5[i] ^ D4[j] ^ D0[j] ^ D1[i] ^ middle0;
+		C[i + (VEC_N_SPLIT_3 << 2)] = D5[j] ^ middle0;
+		C[j + (VEC_N_SPLIT_3 << 2)] = D2[j];
 	}
 }
 
@@ -408,14 +401,8 @@
  * @param[in] a1 Pointer to a polynomial
  * @param[in] a2 Pointer to a polynomial
  */
-void vect_mul(uint64_t *o, const uint64_t *a1, const uint64_t *a2) {
+void vect_mul(uint64_t *o, const aligned_vec_t *a1, const aligned_vec_t *a2) {
+	__m256i a1_times_a2[CEIL_DIVIDE(2 * PARAM_N_MULT + 1, 256)] = {0};
 	karat_mult9(a1_times_a2, a1, a2);
 	reduce(o, a1_times_a2);
-
-	// clear all
-	#ifdef __STDC_LIB_EXT1__
-		memset_s(a1_times_a2, 0, (VEC_N_SIZE_64 << 1) * sizeof(uint64_t));
-	#else
-		memset(a1_times_a2, 0, (VEC_N_SIZE_64 << 1) * sizeof(uint64_t));
-	#endif
 }

