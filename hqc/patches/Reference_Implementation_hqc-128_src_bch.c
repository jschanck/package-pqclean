--- hqc-2020-05-29/Reference_Implementation/hqc-128/src/bch.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-128/src/bch.c
@@ -15,8 +15,6 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(const uint16_t i, const uint16_t modulus);
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound);
 static void unpack_message(uint8_t *message_unpacked, const uint64_t *message);
 static void lfsr_encode(uint8_t *codeword, const uint8_t *message);
 static void pack_codeword(uint64_t *codeword, const uint8_t *codeword_unpacked);
@@ -26,97 +24,6 @@
 static void compute_roots(uint64_t *error, const uint16_t *sigma);
 
 /**
- * @brief Returns i modulo the given modulus.
- *
- * i must be less than 2*modulus.
- * Therefore, the return value is either i or i-modulus.
- * @returns i mod (modulus)
- * @param[in] i The integer whose modulo is taken
- * @param[in] modulus The modulus
- */
-static uint16_t mod(const uint16_t i, const uint16_t modulus) {
-	uint16_t tmp = i - modulus;
-
-	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
-
-	return tmp + (mask & modulus);
-}
-
-
-
-/**
- * @brief Computes the odd binary cyclotomic cosets modulo 2^m-1 for integers less than upper_bound.
- *
- * The array cosets of size 2^m-1 is filled by placing at index i the coset representative of i.
- * @param[out] cosets Array receiving the coset representatives
- * @param[in] upper_bound The upper bound
- */
-static void compute_cyclotomic_cosets(uint16_t *cosets, const uint16_t upper_bound) {
-	// Compute the odd cyclotomic classes
-	for (uint16_t i = 1 ; i < upper_bound ; i += 2) {
-		if (cosets[i] == 0) { // If i does not already belong to a class
-			uint16_t tmp = i;
-			size_t j = PARAM_M;
-			cosets[i] = i;
-			while(--j) { // Complete i's class
-				tmp = mod(2*tmp, PARAM_GF_MUL_ORDER);
-				cosets[tmp] = i;
-			}
-		}
-	}
-}
-
-
-
-/**
- * @brief Computes the generator polynomial of the primitive BCH code with given parameters.
- *
- * Code length is 2^m-1. <br>
- * Parameter t is the targeted correction capacity of the code
- * and receives the real correction capacity (which is at least equal to the target). <br>
- * exp and log are arrays giving antilog and log of GF(2^m) elements.
- * @returns the degree of the generator polynomial
- * @param[out] bch_poly Array of size (m*t + 1) receiving the coefficients of the generator polynomial
- * @param[in,out] t Targeted correction capacity; receives the real correction capacity
- * @param[in] exp Antilog table of GF(2^m)
- * @param[in] log Log table of GF(2^m)
- */
-size_t compute_bch_poly(uint16_t *bch_poly, size_t *t, const uint16_t *exp, const uint16_t *log) {
-	uint16_t cosets[PARAM_GF_MUL_ORDER];
-	size_t deg_bch_poly = 0;
-
-	memset(cosets, 0, 2 * PARAM_GF_MUL_ORDER);
-	compute_cyclotomic_cosets(cosets, 2 * *t);
-
-	// Start with bch_poly(X) = 1
-	bch_poly[0] = 1;
-
-	for (uint16_t i = 1 ; i < PARAM_GF_MUL_ORDER ; ++i) {
-		if(cosets[i] == 0) {
-			continue;
-		}
-
-		// Multiply bch_poly(X) by X-a^i
-		for (size_t j = deg_bch_poly ; j ; --j) {
-			int16_t mask = -((uint16_t)-bch_poly[j] >> 15);
-			bch_poly[j] = (mask & exp[mod(log[bch_poly[j]] + i, PARAM_GF_MUL_ORDER)]) ^ bch_poly[j - 1];
-		}
-		bch_poly[0] = exp[mod(log[bch_poly[0]] + i, PARAM_GF_MUL_ORDER)];
-		bch_poly[++deg_bch_poly] = 1;
-	}
-
-	// Determine the real correction capacity
-	while (cosets[2 * *t + 1] != 0) {
-		++*t;
-	}
-
-	return deg_bch_poly;
-}
-
-
-
-/**
  * @brief Unpacks the message message to the array message_unpacked where each byte stores a bit of the message
  *
  * @param[out] message_unpacked Array of VEC_K_SIZE_BYTES bytes receiving the unpacked message
@@ -125,12 +32,12 @@
 static void unpack_message(uint8_t *message_unpacked, const uint64_t *message) {
 	for (size_t i = 0 ; i < (VEC_K_SIZE_64 - (PARAM_K % 64 != 0)) ; ++i) {
 		for (size_t j = 0 ; j < 64 ; ++j) {
-			message_unpacked[j + 64 * i] = (message[i] >> j) & 0x0000000000000001;
+			message_unpacked[j + 64 * i] = (message[i] >> j) & 1;
 		}
 	}
 
 	for (int8_t j = 0 ; j < PARAM_K % 64 ; ++j) {
-		message_unpacked[j + 64 * (VEC_K_SIZE_64 - 1)] = (message[VEC_K_SIZE_64 - 1] >> j) & 0x0000000000000001;
+		message_unpacked[j + 64 * (VEC_K_SIZE_64 - 1)] = (message[VEC_K_SIZE_64 - 1] >> j) & 1;
 	}
 }
 
@@ -286,27 +193,20 @@
  * @param[in] codeword Array of size VEC_N1_SIZE_BYTES storing the codeword
  */
 static void message_from_codeword(uint64_t *message, const uint64_t *codeword) {
-	int32_t val = PARAM_N1 - PARAM_K;
-
-	uint64_t mask1 = (uint64_t) (0xffffffffffffffff << val % 64);
-	uint64_t mask2 = (uint64_t) (0xffffffffffffffff >> (64 - val % 64));
-	size_t index = val / 64;
+	uint64_t mask1 = (uint64_t) (0xffffffffffffffff << ((PARAM_N1 - PARAM_K)%64));
+	uint64_t mask2 = (uint64_t) (0xffffffffffffffff >> (64 - (PARAM_N1 - PARAM_K)%64));
+	size_t index = (PARAM_N1 - PARAM_K) / 64;
 
 	for (size_t i = 0 ; i < VEC_K_SIZE_64 - 1 ; ++i) {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		uint64_t message2 = (codeword[++index] & mask2) << (64 - val % 64);
-		message[i] = message1 | message2;
+		message[i] = (codeword[index] & mask1) >> ((PARAM_N1 - PARAM_K) % 64);
+		message[i] |= (codeword[++index] & mask2) << (64 - (PARAM_N1 - PARAM_K)%64);
 	}
 
 	// Last byte (8-val % 8 is the number of bits given by message1)
-	if ((PARAM_K % 64 == 0) || (64 - val % 64 < PARAM_K % 64)) {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		uint64_t message2 = (codeword[++index] & mask2) << (64 - val % 64);
-		message[VEC_K_SIZE_64 - 1] = message1 | message2;
-	} else {
-		uint64_t message1 = (codeword[index] & mask1) >> val % 64;
-		message[VEC_K_SIZE_64 - 1] = message1;
-	}
+	message[VEC_K_SIZE_64 - 1] = (codeword[index] & mask1) >> ((PARAM_N1 - PARAM_K) % 64);
+	++index;
+	if (index < VEC_N1_SIZE_64)
+		message[VEC_K_SIZE_64 - 1] |= (codeword[index] & mask2) << (64 - (PARAM_N1 - PARAM_K)%64);
 }
 
 

