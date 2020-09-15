--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-128/src/vector.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-128/src/vector.c
@@ -5,6 +5,7 @@
 
 #include "rng.h"
 #include "parameters.h"
+#include "parsing.h"
 #include "vector.h"
 #include <stdint.h>
 #include <string.h>
@@ -33,72 +34,63 @@
 void vect_set_random_fixed_weight(AES_XOF_struct *ctx, uint64_t *v, uint16_t weight) {
 	size_t random_bytes_size = 3 * weight;
 	uint8_t rand_bytes[3 * PARAM_OMEGA_R] = {0};
-	uint32_t random_data = 0;
 	uint32_t tmp[PARAM_OMEGA_R] = {0};
-	uint8_t exist = 0;
-	size_t j = 0;
-	__m256i * tmp256 = (__m256i *) v;
 	__m256i bit256[PARAM_OMEGA_R];
 	__m256i bloc256[PARAM_OMEGA_R];
-	static __m256i posCmp256 = (__m256i){0UL,1UL,2UL,3UL};
-	#define LOOP_SIZE CEIL_DIVIDE(PARAM_N, 256)
-
-	seedexpander(ctx, rand_bytes, random_bytes_size);
-
-	for (uint32_t i = 0 ; i < weight ; ++i) {
-		exist = 0;
+	__m256i posCmp256 = _mm256_set_epi64x(3,2,1,0);
+	uint64_t bloc, pos, bit64;
+	uint8_t inc;
+	size_t i, j;
+
+	i=0;
+	j=random_bytes_size;
+	while (i<weight) {
 		do {
 			if (j == random_bytes_size) {
 				seedexpander(ctx, rand_bytes, random_bytes_size);
 				j = 0;
 			}
 
-			random_data  = ((uint32_t) rand_bytes[j++]) << 16;
-			random_data |= ((uint32_t) rand_bytes[j++]) << 8;
-			random_data |= rand_bytes[j++];
+			tmp[i] = ((uint32_t) rand_bytes[j++]) << 16;
+			tmp[i] |= ((uint32_t) rand_bytes[j++]) << 8;
+			tmp[i] |= rand_bytes[j++];
 
-		} while (random_data >= UTILS_REJECTION_THRESHOLD);
+		} while (tmp[i] >= UTILS_REJECTION_THRESHOLD);
 
-		random_data = random_data % PARAM_N;
+		tmp[i] = tmp[i] % PARAM_N;
 
+		inc = 1;
 		for (uint32_t k = 0 ; k < i ; k++) {
-			if (tmp[k] == random_data) {
-				exist = 1;
+			if (tmp[k] == tmp[i]) {
+				inc = 0;
 			}
 		}
-
-		if (exist == 1) {
-			i--;
-		} else {
-			tmp[i] = random_data;
-		}
+		i += inc;
 	}
 
-	for (uint32_t i = 0 ; i < weight ; i++) {
+	for (i = 0 ; i < weight ; i++) {
 		// we store the bloc number and bit position of each vb[i]
-		uint64_t bloc = tmp[i] >> 6;
+		bloc = tmp[i] >> 6;
 		bloc256[i] = _mm256_set1_epi64x(bloc >> 2);
-		uint64_t pos = (bloc & 0x3UL);
+		pos = (bloc & 0x3UL);
 		__m256i pos256 = _mm256_set1_epi64x(pos);
 		__m256i mask256 = _mm256_cmpeq_epi64(pos256,posCmp256);
-		uint64_t bit64 = 1ULL << (tmp[i] & 0x3f);
+		bit64 = 1ULL << (tmp[i] & 0x3f);
 		__m256i bloc256 = _mm256_set1_epi64x(bit64);
 		bit256[i] = bloc256&mask256;
 	}
 
-	for (uint32_t i = 0 ; i < LOOP_SIZE ; i++) {
-		__m256i aux = _mm256_setzero_si256();
+	for (i = 0 ; i < CEIL_DIVIDE(PARAM_N, 256); i++) {
+		__m256i aux = _mm256_loadu_si256(((__m256i *)v)+i);
 		__m256i i256 = _mm256_set1_epi64x(i);
 
-		for (uint32_t j = 0 ; j < weight ; j++) {
+		for (j = 0 ; j < weight ; j++) {
 			__m256i mask256 = _mm256_cmpeq_epi64(bloc256[j],i256);
 			aux ^= bit256[j] & mask256;
 		}
-
-		_mm256_storeu_si256(&tmp256[i], _mm256_xor_si256(tmp256[i],aux));
+		_mm256_storeu_si256(((__m256i *)v)+i, aux);
 	}
 
-	#undef LOOP_SIZE
 }
 
 
@@ -117,24 +109,8 @@
 
 	seedexpander(ctx, rand_bytes, VEC_N_SIZE_BYTES);
 
-	memcpy(v, rand_bytes, VEC_N_SIZE_BYTES);
-	v[VEC_N_SIZE_64 - 1] &= BITMASK(PARAM_N, 64);
-}
-
-
-
-/**
- * @brief Generates a random vector
- *
- * This function generates a random binary vector. It uses the the randombytes function.
- *
- * @param[in] v Pointer to an array
- */
-void vect_set_random_from_randombytes(uint64_t *v) {
-	uint8_t rand_bytes [VEC_K_SIZE_BYTES] = {0};
-
-	randombytes(rand_bytes, VEC_K_SIZE_BYTES);
-	memcpy(v, rand_bytes, VEC_K_SIZE_BYTES);
+	load8_arr(v, VEC_N_SIZE_64, rand_bytes, VEC_N_SIZE_BYTES);
+	v[VEC_N_SIZE_64 - 1] &= RED_MASK;
 }
 
 
@@ -163,17 +139,18 @@
  * @param[in] size Integer that is the size of the vectors
  * @returns 0 if the vectors are equals and a negative/psotive value otherwise
  */
-int vect_compare(const uint64_t *v1, const uint64_t *v2, uint32_t size) {
-	unsigned char diff = 0;
-
-	for(uint32_t i=0 ; i < size ; i++) {
-		diff |= ((uint8_t *) v1)[i] ^ ((uint8_t *) v2)[i];
+uint8_t vect_compare(const uint8_t *v1, const uint8_t *v2, uint32_t size) {
+	uint64_t r = 0;
+	for(size_t i=0; i<size; i++) {
+		r |= v1[i] ^ v2[i];
 	}
-	return diff != 0;
+	r = (~r+1) >> 63;
+	return (uint8_t) r;
 }
 
 
 
+
 /**
  * @brief Resize a vector so that it contains <b>size_o</b> bits
  *
@@ -183,10 +160,9 @@
  * @param[in] size_v Integer that is the size of the input vector in bits
  */
 void vect_resize(uint64_t *o, uint32_t size_o, const uint64_t *v, uint32_t size_v) {
+	uint64_t mask = 0x7FFFFFFFFFFFFFFF;
+	int8_t val = 0;
 	if (size_o < size_v) {
-		uint64_t mask = 0x7FFFFFFFFFFFFFFF;
-		int8_t val = 0;
-
 		if (size_o % 64) {
 			val = 64 - (size_o % 64);
 		}
@@ -200,54 +176,3 @@
 		memcpy(o, v, CEIL_DIVIDE(size_v, 8));
 	}
 }
-
-
-
-/**
- * @brief Prints a given number of bytes
- *
- * @param[in] v Pointer to an array of bytes
- * @param[in] size Integer that is number of bytes to be displayed
- */
-void vect_print(const uint64_t *v, const uint32_t size) {
-	if(size == VEC_K_SIZE_BYTES) {
-		uint8_t tmp [VEC_K_SIZE_BYTES] = {0};
-		memcpy(tmp, v, VEC_K_SIZE_BYTES);
-		for (uint32_t i = 0; i < VEC_K_SIZE_BYTES; ++i) {
-			printf("%02x", tmp[i]);
-		}
-	} else if (size == VEC_N_SIZE_BYTES) {
-		uint8_t tmp [VEC_N_SIZE_BYTES] = {0};
-		memcpy(tmp, v, VEC_N_SIZE_BYTES);
-		for (uint32_t i = 0; i < VEC_N_SIZE_BYTES; ++i) {
-			printf("%02x", tmp[i]);
-		}
-	} else if (size == VEC_N1N2_SIZE_BYTES) {
-		uint8_t tmp [VEC_N1N2_SIZE_BYTES] = {0};
-		memcpy(tmp, v, VEC_N1N2_SIZE_BYTES);
-		for (uint32_t i = 0; i < VEC_N1N2_SIZE_BYTES; ++i) {
-			printf("%02x", tmp[i]);
-		}
-	}  else if (size == VEC_N1_SIZE_BYTES) {
-		uint8_t tmp [VEC_N1_SIZE_BYTES] = {0};
-		memcpy(tmp, v, VEC_N1_SIZE_BYTES);
-		for (uint32_t i = 0; i < VEC_N1_SIZE_BYTES; ++i) {
-			printf("%02x", tmp[i]);
-		}
-	}
-}
-
-
-
-/**
- * @brief Prints a vector stored by positions
- *
- * @param[in] v Pointer to an array of integers
- * @param[in] weight Integer that is number positions to be displayed
- */
-void vect_print_sparse(const uint32_t *v, const uint16_t weight) {
-	for (uint16_t i = 0; i < weight-1; ++i) {
-		printf("%d ,", v[i]);
-	}
-	printf("%d", v[weight - 1]);
-}

