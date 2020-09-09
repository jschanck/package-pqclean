--- hqc-2020-05-29/Optimized_Implementation/hqc-128/src/vector.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-128/src/vector.c
@@ -37,7 +37,6 @@
 	uint32_t tmp[PARAM_OMEGA_R] = {0};
 	uint8_t exist = 0;
 	size_t j = 0;
-	__m256i * tmp256 = (__m256i *) v;
 	__m256i bit256[PARAM_OMEGA_R];
 	__m256i bloc256[PARAM_OMEGA_R];
 	static __m256i posCmp256 = (__m256i){0UL,1UL,2UL,3UL};
@@ -87,15 +86,14 @@
 	}
 
 	for (uint32_t i = 0 ; i < LOOP_SIZE ; i++) {
-		__m256i aux = _mm256_setzero_si256();
+		__m256i aux = _mm256_loadu_si256(((__m256i *)v)+i);
 		__m256i i256 = _mm256_set1_epi64x(i);
 
 		for (uint32_t j = 0 ; j < weight ; j++) {
 			__m256i mask256 = _mm256_cmpeq_epi64(bloc256[j],i256);
 			aux ^= bit256[j] & mask256;
 		}
-
-		_mm256_storeu_si256(&tmp256[i], _mm256_xor_si256(tmp256[i],aux));
+		_mm256_storeu_si256(((__m256i *)v)+i, aux);
 	}
 
 	#undef LOOP_SIZE
@@ -118,7 +116,7 @@
 	seedexpander(ctx, rand_bytes, VEC_N_SIZE_BYTES);
 
 	memcpy(v, rand_bytes, VEC_N_SIZE_BYTES);
-	v[VEC_N_SIZE_64 - 1] &= BITMASK(PARAM_N, 64);
+	v[VEC_N_SIZE_64 - 1] &= RED_MASK;
 }
 
 
@@ -200,54 +198,3 @@
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

