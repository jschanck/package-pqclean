--- upstream/Reference_Implementation/hqc-rmrs-192/src/reed_solomon.c
+++ upstream-patched/Reference_Implementation/hqc-rmrs-192/src/reed_solomon.c
@@ -7,6 +7,7 @@
 #include "gf.h"
 #include "reed_solomon.h"
 #include "parameters.h"
+#include "parsing.h"
 #include <stdint.h>
 #include <string.h>
 #include <stdio.h>
@@ -15,69 +16,13 @@
 #include <stdio.h>
 #endif
 
-static uint16_t mod(uint16_t i, uint16_t modulus);
 static void compute_syndromes(uint16_t* syndromes, uint8_t* cdw);
-static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
+static uint16_t compute_elp(uint16_t *sigma, const uint16_t *syndromes);
 static void compute_roots(uint8_t* error, uint16_t* sigma);
-static void compute_z_poly(uint16_t* z, const uint16_t* sigma, const uint8_t degree, const uint16_t* syndromes);
+static void compute_z_poly(uint16_t* z, const uint16_t* sigma, uint16_t degree, const uint16_t* syndromes);
 static void compute_error_values(uint16_t* error_values, const uint16_t* z, const uint8_t* error);
 static void correct_errors(uint8_t* cdw, const uint16_t* error_values);
 
-static const uint16_t alpha_ij_pow [32][55] = {{2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160},{4, 16, 64, 29, 116, 205, 19, 76, 45, 180, 234, 143, 6, 24, 96, 157, 78, 37, 148, 106, 181, 238, 159, 70, 5, 20, 80, 93, 105, 185, 222, 95, 97, 153, 94, 101, 137, 30, 120, 253, 211, 107, 177, 254, 223, 91, 113, 217, 67, 17, 68, 13, 52, 208, 103},{8, 64, 58, 205, 38, 45, 117, 143, 12, 96, 39, 37, 53, 181, 193, 70, 10, 80, 186, 185, 161, 97, 47, 101, 15, 120, 231, 107, 127, 223, 182, 217, 134, 68, 26, 208, 206, 62, 237, 59, 197, 102, 23, 184, 169, 33, 21, 168, 41, 85, 146, 228, 115, 191, 145},{16, 29, 205, 76, 180, 143, 24, 157, 37, 106, 238, 70, 20, 93, 185, 95, 153, 101, 30, 253, 107, 254, 91, 217, 17, 13, 208, 129, 248, 59, 151, 133, 184, 79, 132, 168, 82, 73, 228, 230, 198, 252, 123, 227, 150, 149, 165, 130, 200, 28, 221, 81, 121, 195, 172},{32, 116, 38, 180, 3, 96, 156, 106, 193, 5, 160, 185, 190, 94, 15, 253, 214, 223, 226, 17, 26, 103, 124, 59, 51, 46, 169, 132, 77, 85, 114, 230, 145, 215, 255, 150, 55, 174, 100, 28, 167, 89, 239, 172, 36, 244, 235, 44, 233, 108, 1, 32, 116, 38, 180},{64, 205, 45, 143, 96, 37, 181, 70, 80, 185, 97, 101, 120, 107, 223, 217, 68, 208, 62, 59, 102, 184, 33, 168, 85, 228, 191, 252, 241, 150, 110, 130, 7, 221, 89, 195, 138, 61, 251, 44, 207, 173, 8, 58, 38, 117, 12, 39, 53, 193, 10, 186, 161, 47, 15},{128, 19, 117, 24, 156, 181, 140, 93, 161, 94, 60, 107, 163, 67, 26, 129, 147, 102, 109, 132, 41, 57, 209, 252, 255, 98, 87, 200, 224, 89, 155, 18, 245, 11, 233, 173, 16, 232, 45, 3, 157, 53, 159, 40, 185, 194, 137, 231, 254, 226, 68, 189, 248, 197, 46},{29, 76, 143, 157, 106, 70, 93, 95, 101, 253, 254, 217, 13, 129, 59, 133, 79, 168, 73, 230, 252, 227, 149, 130, 28, 81, 195, 18, 247, 44, 27, 2, 58, 152, 3, 39, 212, 140, 186, 190, 202, 231, 225, 175, 26, 31, 118, 23, 158, 77, 146, 209, 229, 219, 55},{58, 45, 12, 37, 193, 80, 161, 101, 231, 223, 134, 208, 237, 102, 169, 168, 146, 191, 179, 150, 87, 7, 166, 195, 36, 251, 125, 173, 64, 38, 143, 39, 181, 10, 185, 47, 120, 127, 217, 26, 62, 197, 184, 21, 85, 115, 252, 219, 110, 100, 221, 242, 138, 245, 44},{116, 180, 96, 106, 5, 185, 94, 253, 223, 17, 103, 59, 46, 132, 85, 230, 215, 150, 174, 28, 89, 172, 244, 44, 108, 32, 38, 3, 156, 193, 160, 190, 15, 214, 226, 26, 124, 51, 169, 77, 114, 145, 255, 55, 100, 167, 239, 36, 235, 233, 1, 116, 180, 96, 106},{232, 234, 39, 238, 160, 97, 60, 254, 134, 103, 118, 184, 84, 57, 145, 227, 220, 7, 162, 172, 245, 176, 71, 58, 180, 192, 181, 40, 95, 15, 177, 175, 208, 147, 46, 21, 73, 99, 241, 55, 200, 166, 43, 122, 44, 216, 128, 45, 48, 106, 10, 222, 202, 107, 226},{205, 143, 37, 70, 185, 101, 107, 217, 208, 59, 184, 168, 228, 252, 150, 130, 221, 195, 61, 44, 173, 58, 117, 39, 193, 186, 47, 231, 182, 26, 237, 23, 21, 146, 145, 219, 87, 56, 242, 36, 139, 54, 64, 45, 96, 181, 80, 97, 120, 223, 68, 62, 102, 33, 85},{135, 6, 53, 20, 190, 120, 163, 13, 237, 46, 84, 228, 229, 98, 100, 81, 69, 251, 131, 32, 45, 192, 238, 186, 94, 187, 217, 189, 236, 169, 82, 209, 241, 220, 28, 242, 72, 22, 173, 116, 201, 37, 140, 222, 15, 254, 34, 62, 204, 132, 146, 63, 75, 130, 167},{19, 24, 181, 93, 94, 107, 67, 129, 102, 132, 57, 252, 98, 200, 89, 18, 11, 173, 232, 3, 53, 40, 194, 231, 226, 189, 197, 158, 170, 145, 75, 25, 166, 69, 235, 54, 29, 234, 37, 5, 95, 120, 91, 52, 59, 218, 82, 191, 227, 174, 221, 43, 247, 207, 32},{38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145, 150, 100, 89, 36, 44, 1, 38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145, 150, 100, 89, 36, 44, 1, 38, 96, 193, 185, 15, 223, 26, 59, 169, 85, 145, 150, 100, 89, 36, 44, 1, 38, 96, 193, 185},{76, 157, 70, 95, 253, 217, 129, 133, 168, 230, 227, 130, 81, 18, 44, 2, 152, 39, 140, 190, 231, 175, 31, 23, 77, 209, 219, 25, 162, 36, 88, 4, 45, 78, 5, 97, 211, 67, 62, 46, 154, 191, 171, 50, 89, 72, 176, 8, 90, 156, 10, 194, 187, 134, 124},{152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1, 152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1, 152, 78, 10, 153, 214, 68, 147, 79, 146, 215, 220, 221, 69, 11, 1, 152, 78, 10, 153, 214, 68, 147, 79, 146, 215},{45, 37, 80, 101, 223, 208, 102, 168, 191, 150, 7, 195, 251, 173, 38, 39, 10, 47, 127, 26, 197, 21, 115, 219, 100, 242, 245, 54, 205, 96, 70, 97, 107, 68, 59, 33, 228, 241, 130, 89, 61, 207, 58, 12, 193, 161, 231, 134, 237, 169, 146, 179, 87, 166, 36},{90, 148, 186, 30, 226, 62, 109, 73, 179, 174, 162, 61, 131, 232, 96, 140, 153, 127, 52, 51, 168, 99, 98, 56, 172, 22, 8, 234, 212, 185, 240, 67, 237, 79, 114, 241, 25, 121, 245, 108, 19, 39, 20, 188, 223, 189, 133, 41, 63, 55, 221, 9, 176, 64, 3},{180, 106, 185, 253, 17, 59, 132, 230, 150, 28, 172, 44, 32, 3, 193, 190, 214, 26, 51, 77, 145, 55, 167, 36, 233, 116, 96, 5, 94, 223, 103, 46, 85, 215, 174, 89, 244, 108, 38, 156, 160, 15, 226, 124, 169, 114, 255, 100, 239, 235, 1, 180, 106, 185, 253},{117, 181, 161, 107, 26, 102, 41, 252, 87, 89, 245, 173, 45, 53, 185, 231, 68, 197, 168, 145, 110, 166, 61, 54, 38, 37, 186, 120, 134, 59, 21, 191, 196, 221, 36, 207, 205, 39, 80, 15, 217, 237, 33, 115, 150, 56, 138, 125, 58, 96, 10, 101, 182, 62, 169},{234, 238, 97, 254, 103, 184, 57, 227, 7, 172, 176, 58, 192, 40, 15, 175, 147, 21, 99, 55, 166, 122, 216, 45, 106, 222, 107, 52, 133, 85, 123, 50, 195, 11, 32, 12, 140, 188, 182, 124, 158, 115, 49, 224, 36, 131, 19, 37, 105, 253, 68, 151, 154, 252, 174},{201, 159, 47, 91, 124, 33, 209, 149, 166, 244, 71, 117, 238, 194, 223, 31, 79, 115, 98, 167, 61, 216, 90, 181, 190, 254, 206, 218, 213, 150, 224, 72, 54, 152, 106, 161, 177, 189, 184, 114, 171, 56, 18, 131, 38, 148, 111, 107, 104, 46, 146, 227, 14, 138, 233},{143, 70, 101, 217, 59, 168, 252, 130, 195, 44, 58, 39, 186, 231, 26, 23, 146, 219, 56, 36, 54, 45, 181, 97, 223, 62, 33, 191, 110, 89, 251, 8, 12, 10, 15, 134, 197, 41, 179, 100, 86, 125, 205, 37, 185, 107, 208, 184, 228, 150, 221, 61, 173, 117, 193},{3, 5, 15, 17, 51, 85, 255, 28, 36, 108, 180, 193, 94, 226, 59, 77, 215, 100, 172, 233, 38, 106, 190, 223, 124, 132, 145, 174, 239, 44, 116, 156, 185, 214, 103, 169, 230, 55, 89, 235, 32, 96, 160, 253, 26, 46, 114, 150, 167, 244, 1, 3, 5, 15, 17},{6, 20, 120, 13, 46, 228, 98, 81, 251, 32, 192, 186, 187, 189, 169, 209, 220, 242, 22, 116, 37, 222, 254, 62, 132, 63, 130, 43, 250, 38, 212, 194, 182, 147, 77, 179, 141, 9, 54, 180, 159, 101, 67, 151, 85, 227, 112, 61, 142, 3, 10, 60, 136, 23, 114},{12, 80, 231, 208, 169, 191, 87, 195, 125, 38, 181, 47, 217, 197, 85, 219, 221, 245, 8, 96, 186, 107, 206, 33, 145, 130, 86, 207, 45, 193, 101, 134, 102, 146, 150, 166, 251, 64, 39, 185, 127, 62, 21, 252, 100, 138, 54, 117, 70, 15, 68, 23, 228, 196, 89},{24, 93, 107, 129, 132, 252, 200, 18, 173, 3, 40, 231, 189, 158, 145, 25, 69, 54, 234, 5, 120, 52, 218, 191, 174, 43, 207, 90, 35, 15, 136, 92, 115, 220, 239, 125, 76, 238, 101, 17, 133, 228, 149, 121, 44, 135, 212, 47, 175, 51, 146, 49, 162, 139, 116},{48, 105, 127, 248, 77, 241, 224, 247, 64, 156, 95, 182, 236, 170, 150, 162, 11, 205, 212, 94, 134, 133, 213, 110, 239, 250, 45, 35, 30, 26, 218, 99, 130, 69, 108, 143, 40, 211, 206, 132, 229, 7, 144, 2, 96, 210, 254, 237, 154, 255, 221, 243, 128, 37, 190},{96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15, 26, 169, 145, 100, 36, 1, 96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15, 26, 169, 145, 100, 36, 1, 96, 185, 223, 59, 85, 150, 89, 44, 38, 193, 15, 26, 169, 145, 100, 36, 1, 96, 185, 223, 59},{192, 222, 182, 151, 114, 110, 155, 27, 143, 160, 177, 237, 82, 75, 89, 88, 152, 70, 240, 103, 21, 123, 224, 251, 116, 212, 101, 136, 218, 145, 200, 144, 8, 78, 190, 217, 204, 183, 87, 172, 216, 12, 105, 225, 59, 170, 98, 242, 250, 180, 10, 211, 31, 168, 255},{157, 95, 217, 133, 230, 130, 18, 2, 39, 190, 175, 23, 209, 25, 36, 4, 78, 97, 67, 46, 191, 50, 72, 8, 156, 194, 134, 92, 99, 100, 144, 16, 37, 153, 17, 184, 198, 200, 61, 32, 74, 47, 34, 109, 145, 141, 122, 64, 148, 94, 68, 218, 63, 7, 244}};
-
-/**
- * Returns i modulo the given modulus.
- * i must be less than 2*modulus.
- * Therefore, the return value is either i or i-modulus.
- * @returns i mod (modulus)
- * @param[in] i The integer whose modulo is taken
- * @param[in] modulus The modulus
- */
-static uint16_t mod(uint16_t i, uint16_t modulus) {
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
- * @brief Computes the generator polynomial of the primitive Reed-Solomon code with given parameters.
- *
- * Code length is 2^m-1. <br>
- * PARAM_DELTA is the targeted correction capacity of the code
- * and receives the real correction capacity (which is at least equal to the target). <br>
- * exp and log are arrays giving antilog and log of GF(2^m) elements.
- *
- * @param[out] poly Array of size (2*PARAM_DELTA + 1) receiving the coefficients of the generator polynomial
- */
-void compute_generator_poly(uint16_t* poly) {
-	poly[0] = 1;
-	int tmp_degree = 0;
-
-	for (uint16_t i = 1 ; i < (2 * PARAM_DELTA + 1) ; ++i) {
-
-		for(size_t j = tmp_degree ; j ; --j) {
-			poly[j] = exp[mod(log[poly[j]] + i, PARAM_GF_MUL_ORDER)] ^ poly[j - 1];
-		}
-
-		poly[0] = exp[mod(log[poly[0]] + i, PARAM_GF_MUL_ORDER)];
-		poly[++tmp_degree] = 1;
-
-	}
-
-	printf("\n");
-	for (int i = 0 ; i < (PARAM_G) ; ++i) {
-		printf("%d, ", poly[i]);
-	}
-	printf("\n");
-}
-
-
-
 /**
  * @brief Encodes a message message of PARAM_K bits to a Reed-Solomon codeword codeword of PARAM_N1 bytes
  *
@@ -88,33 +33,34 @@
  * @param[out] cdw Array of size VEC_N1_SIZE_64 receiving the encoded message
  * @param[in] msg Array of size VEC_K_SIZE_64 storing the message
  */
-void reed_solomon_encode(uint64_t* cdw, const uint64_t* msg) {
+void reed_solomon_encode(uint8_t* cdw, const uint8_t* msg) {
+	size_t i, j, k;
 	uint8_t gate_value = 0;
 
 	uint16_t tmp[PARAM_G] = {0};
 	uint16_t PARAM_RS_POLY [] = {RS_POLY_COEFS};
+	uint8_t prev, x;
 
-	uint8_t msg_bytes[PARAM_K] = {0};
-	uint8_t cdw_bytes[PARAM_N1] = {0};
-
-	memcpy(msg_bytes, msg, PARAM_K);
+	for (i = 0; i < PARAM_N1; ++i) {
+		cdw[i] = 0;
+	}
 
-	for (int i = PARAM_K-1 ; i >= 0 ; --i) {
-		gate_value = msg_bytes[i] ^ cdw_bytes[PARAM_N1 - PARAM_K - 1];
+	for (i = 0 ; i < PARAM_K ; ++i) {
+		gate_value = (uint8_t) (msg[PARAM_K-1-i] ^ cdw[PARAM_N1 - PARAM_K - 1]);
 
-		for (size_t j = 0 ; j < PARAM_G ; ++j) {
+		for (j = 0 ; j < PARAM_G ; ++j) {
 			tmp[j] = gf_mul(gate_value, PARAM_RS_POLY[j]);
 		}
 
-		for(size_t k = PARAM_N1 - PARAM_K - 1 ; k ; --k) {
-			cdw_bytes[k] = cdw_bytes[k - 1] ^ tmp[k];
+		prev = 0;
+		for(k = 0 ; k < PARAM_N1-PARAM_K; k++) {
+			x = cdw[k];
+			cdw[k] = (uint8_t) (prev ^ tmp[k]);
+			prev = x;
 		}
-
-		cdw_bytes[0] = tmp[0];
 	}
 
-	memcpy(cdw_bytes + PARAM_N1 - PARAM_K, msg_bytes, PARAM_K);
-	memcpy(cdw, cdw_bytes, PARAM_N1);
+	memcpy(cdw + PARAM_N1 - PARAM_K, msg, PARAM_K);
 }
 
 
@@ -152,55 +98,62 @@
  * @param[out] sigma Array of size (at least) PARAM_DELTA receiving the ELP
  * @param[in] syndromes Array of size (at least) 2*PARAM_DELTA storing the syndromes
  */
-static size_t compute_elp(uint16_t *sigma, const uint16_t *syndromes) {
-	sigma[0] = 1;
-	size_t deg_sigma = 0;
-	size_t deg_sigma_p = 0;
+static uint16_t compute_elp(uint16_t *sigma, const uint16_t *syndromes) {
+	uint16_t deg_sigma = 0;
+	uint16_t deg_sigma_p = 0;
+	uint16_t deg_sigma_copy = 0;
 	uint16_t sigma_copy[PARAM_DELTA + 1] = {0};
-	size_t deg_sigma_copy = 0;
 	uint16_t X_sigma_p[PARAM_DELTA + 1] = {0,1};
-	int32_t pp = -1; // 2*rho
+	uint16_t pp = (uint16_t) -1; // 2*rho
 	uint16_t d_p = 1;
 	uint16_t d = syndromes[0];
 
-	for (size_t mu = 0 ; (mu < (2 * PARAM_DELTA)) ; ++mu) {
+	uint16_t mask1, mask2, mask12;
+	uint16_t deg_X, deg_X_sigma_p;
+	uint16_t dd;
+	uint16_t mu;
+
+	uint16_t i;
+
+	sigma[0] = 1;
+	for (mu = 0 ; (mu < (2 * PARAM_DELTA)) ; ++mu) {
 		// Save sigma in case we need it to update X_sigma_p
 		memcpy(sigma_copy, sigma, 2 * (PARAM_DELTA));
 		deg_sigma_copy = deg_sigma;
 
-		uint16_t dd = gf_mul(d, gf_inverse(d_p));
+		dd = gf_mul(d, gf_inverse(d_p));
 
-		for (size_t i = 1 ; (i <= mu + 1) && (i <= PARAM_DELTA) ; ++i) {
+		for (i = 1 ; (i <= mu + 1) && (i <= PARAM_DELTA) ; ++i) {
 			sigma[i] ^= gf_mul(dd, X_sigma_p[i]);
 		}
 
-		size_t deg_X = mu - pp;
-		size_t deg_X_sigma_p = deg_X + deg_sigma_p;
+		deg_X = mu - pp;
+		deg_X_sigma_p = deg_X + deg_sigma_p;
 
 		// mask1 = 0xffff if(d != 0) and 0 otherwise
-		int16_t mask1 = -((uint16_t) - d >> 15);
+		mask1 = -((uint16_t) - d >> 15);
 
 		// mask2 = 0xffff if(deg_X_sigma_p > deg_sigma) and 0 otherwise
-		int16_t mask2 = -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
+		mask2 = -((uint16_t) (deg_sigma - deg_X_sigma_p) >> 15);
 
 		// mask12 = 0xffff if the deg_sigma increased and 0 otherwise
-		int16_t mask12 = mask1 & mask2;
-		deg_sigma = (mask12 & deg_X_sigma_p) ^ (~mask12 & deg_sigma);
+		mask12 = mask1 & mask2;
+		deg_sigma ^= mask12 & (deg_X_sigma_p^deg_sigma);
 
 		if (mu == (2 * PARAM_DELTA - 1)) {
 			break;
 		}
 
-		pp = (mask12 & mu) ^ (~mask12 & pp);
-		d_p = (mask12 & d) ^ (~mask12 & d_p);
-		for (size_t i = PARAM_DELTA ; i ; --i) {
+		pp ^= mask12 & (mu^pp);
+		d_p ^= mask12 & (d^d_p);
+		for (i = PARAM_DELTA ; i ; --i) {
 			X_sigma_p[i] = (mask12 & sigma_copy[i - 1]) ^ (~mask12 & X_sigma_p[i - 1]);
 		}
 
-		deg_sigma_p = (mask12 & deg_sigma_copy) ^ (~mask12 & deg_sigma_p);
+		deg_sigma_p ^= mask12 & (deg_sigma_copy^deg_sigma_p);
 		d = syndromes[mu + 1];
 
-		for (size_t i = 1 ; (i <= mu+1) && (i <= PARAM_DELTA) ; ++i) {
+		for (i = 1 ; (i <= mu+1) && (i <= PARAM_DELTA) ; ++i) {
 			d ^= gf_mul(sigma[i], syndromes[mu + 1 - i]);
 		}
 	}
@@ -238,22 +191,25 @@
  * @param[in] degree Integer that is the degree of polynomial sigma
  * @param[in] syndromes Array of 2 * PARAM_DELTA storing the syndromes
  */
-static void compute_z_poly(uint16_t* z, const uint16_t* sigma, const uint8_t degree, const uint16_t* syndromes) {
+static void compute_z_poly(uint16_t* z, const uint16_t* sigma, uint16_t degree, const uint16_t* syndromes) {
+	size_t i, j;
+	uint16_t mask;
+
 	z[0] = 1;
 
-	for (size_t i = 1 ; i < PARAM_DELTA + 1 ; ++i) {
-		int16_t mask2 = -((uint16_t) (i - degree - 1) >> 15);
-		z[i] = ((uint16_t)mask2) & sigma[i];
+	for (i = 1 ; i < PARAM_DELTA + 1 ; ++i) {
+		mask = -((uint16_t) (i - degree - 1) >> 15);
+		z[i] = mask & sigma[i];
 	}
 
 	z[1] ^= syndromes[0];
 
-	for (size_t i = 2 ; i <= PARAM_DELTA ; ++i) {
-		int16_t mask2 = -((uint16_t) (i - degree - 1) >> 15);
-		z[i] ^= ((uint16_t)mask2 & syndromes[i-1]);
+	for (i = 2 ; i <= PARAM_DELTA ; ++i) {
+		mask = -((uint16_t) (i - degree - 1) >> 15);
+		z[i] ^= mask & syndromes[i-1];
 
-		for (size_t j = 1 ; j < i ; ++j) {
-			z[i] ^= ((uint16_t)mask2) & gf_mul(sigma[j], syndromes[i - j - 1]);
+		for (j = 1 ; j < i ; ++j) {
+			z[i] ^= mask & gf_mul(sigma[j], syndromes[i - j - 1]);
 		}
 	}
 }
@@ -274,17 +230,25 @@
 	uint16_t beta_j[PARAM_DELTA] = {0};
 	uint16_t e_j[PARAM_DELTA] = {0};
 
-	uint16_t delta_counter = 0;
+	uint16_t delta_counter;
 	uint16_t delta_real_value;
+	uint16_t found;
+	uint16_t mask1;
+	uint16_t mask2;
+	uint16_t tmp1;
+	uint16_t tmp2;
+	uint16_t inverse;
+	uint16_t inverse_power_j;
 
 	// Compute the beta_{j_i} page 31 of the documentation
+	delta_counter = 0;
 	for (size_t i = 0 ; i < PARAM_N1 ; i++) {
-		uint16_t found = 0;
-		int16_t valuemask = ((int16_t) -(error[i] != 0)) >> 15;
+		found = 0;
+		mask1 = (uint16_t) (-((int32_t)error[i])>>31); // error[i] != 0
 		for (size_t j = 0 ; j < PARAM_DELTA ; j++) {
-			int16_t indexmask = ((int16_t) -(j == delta_counter)) >> 15;
-			beta_j[j] += indexmask & valuemask & exp[i];
-			found += indexmask & valuemask & 1;
+			mask2 = ~((uint16_t) (-((int32_t) j^delta_counter) >> 31)); // j == delta_counter
+			beta_j[j] += mask1 & mask2 & gf_exp[i];
+			found += mask1 & mask2 & 1;
 		}
 		delta_counter += found;
 	}
@@ -292,10 +256,10 @@
 
 	// Compute the e_{j_i} page 31 of the documentation
 	for (size_t i = 0 ; i < PARAM_DELTA ; ++i) {
-		uint16_t tmp1 = 1;
-		uint16_t tmp2 = 1;
-		uint16_t inverse = gf_inverse(beta_j[i]);
-		uint16_t inverse_power_j = 1;
+		tmp1 = 1;
+		tmp2 = 1;
+		inverse = gf_inverse(beta_j[i]);
+		inverse_power_j = 1;
 
 		for (size_t j = 1 ; j <= PARAM_DELTA ; ++j) {
 			inverse_power_j = gf_mul(inverse_power_j, inverse);
@@ -304,19 +268,19 @@
 		for (size_t k = 1 ; k < PARAM_DELTA ; ++k) {
 			tmp2 = gf_mul(tmp2, (1 ^ gf_mul(inverse, beta_j[(i+k) % PARAM_DELTA])));
 		}
-		int16_t mask = ((int16_t) -(i<delta_real_value))>>15;
-		e_j[i] = mask & gf_mul(tmp1,gf_inverse(tmp2));
+		mask1 = (uint16_t) (((int16_t) i-delta_real_value)>>15); // i < delta_real_value
+		e_j[i] = mask1 & gf_mul(tmp1,gf_inverse(tmp2));
 	}
 
 	// Place the delta e_{j_i} values at the right coordinates of the output vector
 	delta_counter = 0;
 	for (size_t i = 0 ; i < PARAM_N1 ; ++i) {
-		uint16_t found = 0;
-		int16_t valuemask = ((int16_t) -(error[i] !=0)) >> 15;
+		found = 0;
+		mask1 = (uint16_t) (-((int32_t)error[i])>>31); // error[i] != 0
 		for (size_t j = 0 ; j < PARAM_DELTA ; j++) {
-			int16_t indexmask = ((int16_t) -(j == delta_counter)) >> 15;
-			error_values[i] += indexmask & valuemask & e_j[j];
-			found += indexmask & valuemask & 1;
+			mask2 = ~((uint16_t) (-((int32_t) j^delta_counter) >> 31)); // j == delta_counter
+			error_values[i] += mask1 & mask2 & e_j[j];
+			found += mask1 & mask2 & 1;
 		}
 		delta_counter += found;
 	}
@@ -356,23 +320,20 @@
  * @param[out] msg Array of size VEC_K_SIZE_64 receiving the decoded message
  * @param[in] cdw Array of size VEC_N1_SIZE_64 storing the received word
  */
-void reed_solomon_decode(uint64_t* msg, uint64_t* cdw) {
-	uint8_t cdw_bytes[PARAM_N1] = {0};
+void reed_solomon_decode(uint8_t* msg, uint8_t* cdw) {
 	uint16_t syndromes[2 * PARAM_DELTA] = {0};
 	uint16_t sigma[1 << PARAM_FFT] = {0};
 	uint8_t error[1 << PARAM_M] = {0};
 	uint16_t z[PARAM_N1] = {0};
 	uint16_t error_values[PARAM_N1] = {0};
-
-	// Copy the vector in an array of bytes
-	memcpy(cdw_bytes, cdw, PARAM_N1);
+	uint16_t deg;
 
 	// Calculate the 2*PARAM_DELTA syndromes
-	compute_syndromes(syndromes, cdw_bytes);
+	compute_syndromes(syndromes, cdw);
 
 	// Compute the error locator polynomial sigma
 	// Sigma's degree is at most PARAM_DELTA but the FFT requires the extra room
-	size_t deg = compute_elp(sigma, syndromes);
+	deg = compute_elp(sigma, syndromes);
 
 	// Compute the error polynomial error
 	compute_roots(error, sigma);
@@ -384,10 +345,10 @@
 	compute_error_values(error_values, z, error);
 
 	// Correct the errors
-	correct_errors(cdw_bytes, error_values);
+	correct_errors(cdw, error_values);
 
 	// Retrieve the message from the decoded codeword
-	memcpy(msg, cdw_bytes + (PARAM_G - 1) , PARAM_K);
+	memcpy(msg, cdw + (PARAM_G - 1) , PARAM_K);
 
 #ifdef VERBOSE
 	printf("\n\nThe syndromes: ");
@@ -448,4 +409,4 @@
 	}
 	printf("\n");
 #endif
-}
\ No newline at end of file
+}

