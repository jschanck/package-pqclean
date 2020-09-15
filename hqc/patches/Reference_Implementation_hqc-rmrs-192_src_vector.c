--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-192/src/vector.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-192/src/vector.c
@@ -5,6 +5,7 @@
 
 #include "rng.h"
 #include "parameters.h"
+#include "parsing.h"
 #include "vector.h"
 #include <stdint.h>
 #include <string.h>
@@ -32,39 +33,33 @@
 void vect_set_random_fixed_weight_by_coordinates(AES_XOF_struct *ctx, uint32_t *v, uint16_t weight) {
 	size_t random_bytes_size = 3 * weight;
 	uint8_t rand_bytes[3 * PARAM_OMEGA_R] = {0}; // weight is expected to be <= PARAM_OMEGA_R
-	uint32_t random_data = 0;
-	uint8_t exist = 0;
-	size_t j = 0;
+	uint8_t inc;
+	size_t i, j;
 
-	seedexpander(ctx, rand_bytes, random_bytes_size);
-
-	for (uint32_t i = 0 ; i < weight ; ++i) {
-		exist = 0;
+	i=0;
+	j=random_bytes_size;
+	while(i < weight) {
 		do {
 			if (j == random_bytes_size) {
 				seedexpander(ctx, rand_bytes, random_bytes_size);
 				j = 0;
 			}
 
-			random_data  = ((uint32_t) rand_bytes[j++]) << 16;
-			random_data |= ((uint32_t) rand_bytes[j++]) << 8;
-			random_data |= rand_bytes[j++];
-
-		} while (random_data >= UTILS_REJECTION_THRESHOLD);
-
-		random_data = random_data % PARAM_N;
-
-		for (uint32_t k = 0 ; k < i ; k++) {
-			if (v[k] == random_data) {
-				exist = 1;
+			v[i]  = ((uint32_t) rand_bytes[j++]) << 16;
+			v[i] |= ((uint32_t) rand_bytes[j++]) << 8;
+			v[i] |= rand_bytes[j++];
+
+		} while (v[i] >= UTILS_REJECTION_THRESHOLD);
+
+		v[i] = v[i] % PARAM_N;
+
+		inc = 1;
+		for (size_t k = 0 ; k < i ; k++) {
+			if (v[k] == v[i]) {
+				inc = 0;
 			}
 		}
-
-		if (exist == 1) {
-			i--;
-		} else {
-			v[i] = random_data;
-		}
+		i += inc;
 	}
 }
 
@@ -87,46 +82,11 @@
  * @param[in] ctx Pointer to the context of the seed expander
  */
 void vect_set_random_fixed_weight(AES_XOF_struct *ctx, uint64_t *v, uint16_t weight) {
-
-	size_t random_bytes_size = 3 * weight;
-	uint8_t rand_bytes[3 * PARAM_OMEGA_R] = {0}; // weight is expected to be <= PARAM_OMEGA_R
-	uint32_t random_data = 0;
 	uint32_t tmp[PARAM_OMEGA_R] = {0};
-	uint8_t exist = 0;
-	size_t j = 0;
-
-	seedexpander(ctx, rand_bytes, random_bytes_size);
-
-	for (uint32_t i = 0 ; i < weight ; ++i) {
-		exist = 0;
-		do {
-			if (j == random_bytes_size) {
-				seedexpander(ctx, rand_bytes, random_bytes_size);
-				j = 0;
-			}
-
-			random_data  = ((uint32_t) rand_bytes[j++]) << 16;
-			random_data |= ((uint32_t) rand_bytes[j++]) << 8;
-			random_data |= rand_bytes[j++];
-
-		} while (random_data >= UTILS_REJECTION_THRESHOLD);
-
-		random_data = random_data % PARAM_N;
-
-		for (uint32_t k = 0 ; k < i ; k++) {
-			if (tmp[k] == random_data) {
-				exist = 1;
-			}
-		}
 
-		if (exist == 1) {
-			i--;
-		} else {
-			tmp[i] = random_data;
-		}
-	}
+	vect_set_random_fixed_weight_by_coordinates(ctx, tmp, weight);
 
-	for (uint16_t i = 0 ; i < weight ; ++i) {
+	for (size_t i = 0 ; i < weight ; ++i) {
 		int32_t index = tmp[i] / 64;
 		int32_t pos = tmp[i] % 64;
 		v[index] |= ((uint64_t) 1) << pos;
@@ -149,24 +109,8 @@
 
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
 
 
@@ -186,6 +130,7 @@
 }
 
 
+
 /**
  * @brief Compares two vectors
  *
@@ -194,8 +139,13 @@
  * @param[in] size Integer that is the size of the vectors
  * @returns 0 if the vectors are equals and a negative/psotive value otherwise
  */
-int vect_compare(const uint64_t *v1, const uint64_t *v2, uint32_t size) {
-	return memcmp(v1, v2, size);
+uint8_t vect_compare(const uint8_t *v1, const uint8_t *v2, uint32_t size) {
+	uint64_t r = 0;
+	for(size_t i=0; i<size; i++) {
+		r |= v1[i] ^ v2[i];
+	}
+	r = (~r+1) >> 63;
+	return (uint8_t) r;
 }
 
 
@@ -217,62 +167,12 @@
 			val = 64 - (size_o % 64);
 		}
 		
-		memcpy(o, v, VEC_N1N2_SIZE_BYTES);
+		memcpy(o, v, 8*VEC_N1N2_SIZE_64);
 
 		for (int8_t i = 0 ; i < val ; ++i) {
 			o[VEC_N1N2_SIZE_64 - 1] &= (mask >> i);
 		}
 	} else {
-		memcpy(o, v, CEIL_DIVIDE(size_v, 8));
-	}
-}
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
-/**
- * @brief Prints a vector stored by positions
- *
- * @param[in] v Pointer to an array of integers
- * @param[in] weight Integer that is number positions to be displayed
- */
-void vect_print_sparse(const uint32_t *v, const uint16_t weight) {
-	for (uint16_t i = 0; i < weight-1; ++i) {
-		printf("%d ,", v[i]);
+		memcpy(o, v, 8*CEIL_DIVIDE(size_v, 64));
 	}
-	printf("%d", v[weight - 1]);
 }

