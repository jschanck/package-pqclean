--- upstream/Reference_Implementation/hqc-rmrs-192/src/reed_muller.c
+++ upstream-patched/Reference_Implementation/hqc-rmrs-192/src/reed_muller.c
@@ -3,9 +3,6 @@
  * Constant time implementation of Reed-Muller code RM(1,7)
  */
 
-// setting this will help the compiler with auto vectorization
-#undef ALIGNVECTORS
-
 #include "reed_muller.h"
 #include "parameters.h"
 #include <stdint.h>
@@ -15,31 +12,14 @@
 // number of repeated code words
 #define MULTIPLICITY                   CEIL_DIVIDE(PARAM_N2, 128)
 
-// codeword is 128 bits, seen multiple ways
-typedef union {
-	uint8_t u8[16];
-	uint32_t u32[4];
-} codeword
-#ifdef ALIGNVECTORS
-__attribute__ ((aligned (16)))
-#endif
-	;
-
-// Expanded codeword has a short for every bit, for internal calculations
-typedef int16_t expandedCodeword[128]
-#ifdef ALIGNVECTORS
-__attribute__ ((aligned (64)))
-#endif
-	;
-
 // copy bit 0 into all bits of a 32 bit value
-#define BIT0MASK(x) (int32_t)(-((x) & 1))
+#define BIT0MASK(x) (-((x) & 1))
 
 
-void encode(codeword *word, int32_t message);
-void hadamard(expandedCodeword *src, expandedCodeword *dst);
-void expand_and_sum(expandedCodeword *dest, codeword src[]);
-int32_t find_peaks(expandedCodeword *transform);
+static void encode(uint8_t *word, uint8_t message);
+static void hadamard(uint16_t src[128], uint16_t dst[128]);
+static void expand_and_sum(uint16_t dest[128], const uint8_t src[16*MULTIPLICITY]);
+static uint8_t find_peaks(const uint16_t transform[128]);
 
 
 
@@ -60,29 +40,38 @@
  * @param[out] word An RM(1,7) codeword
  * @param[in] message A message
  */
-void encode(codeword *word, int32_t message) {
-	// the four parts of the word are identical
-	// except for encoding bits 5 and 6
-	int32_t first_word;
+static void encode(uint8_t *word, uint8_t message) {
+	uint32_t e;
 	// bit 7 flips all the bits, do that first to save work
-	first_word = BIT0MASK(message >> 7);
+	e = BIT0MASK(message >> 7);
 	// bits 0, 1, 2, 3, 4 are the same for all four longs
 	// (Warning: in the bit matrix above, low bits are at the left!)
-	first_word ^= BIT0MASK(message >> 0) & 0xaaaaaaaa;
-	first_word ^= BIT0MASK(message >> 1) & 0xcccccccc;
-	first_word ^= BIT0MASK(message >> 2) & 0xf0f0f0f0;
-	first_word ^= BIT0MASK(message >> 3) & 0xff00ff00;
-	first_word ^= BIT0MASK(message >> 4) & 0xffff0000;
+	e ^= BIT0MASK(message >> 0) & 0xaaaaaaaa;
+	e ^= BIT0MASK(message >> 1) & 0xcccccccc;
+	e ^= BIT0MASK(message >> 2) & 0xf0f0f0f0;
+	e ^= BIT0MASK(message >> 3) & 0xff00ff00;
+	e ^= BIT0MASK(message >> 4) & 0xffff0000;
 	// we can store this in the first quarter
-	word->u32[0] = first_word;
+	word[0+0] = (e >> 0x00) & 0xff;
+	word[0+1] = (e >> 0x08) & 0xff;
+	word[0+2] = (e >> 0x10) & 0xff;
+	word[0+3] = (e >> 0x18) & 0xff;
 	// bit 5 flips entries 1 and 3; bit 6 flips 2 and 3
-	first_word ^= BIT0MASK(message >> 5);
-	word->u32[1] = first_word;
-	first_word ^= BIT0MASK(message >> 6);
-	word->u32[3] = first_word;
-	first_word ^= BIT0MASK(message >> 5);
-	word->u32[2] = first_word;
-	return;
+	e ^= BIT0MASK(message >> 5);
+	word[4+0] = (e >> 0x00) & 0xff;
+	word[4+1] = (e >> 0x08) & 0xff;
+	word[4+2] = (e >> 0x10) & 0xff;
+	word[4+3] = (e >> 0x18) & 0xff;
+	e ^= BIT0MASK(message >> 6);
+	word[12+0] = (e >> 0x00) & 0xff;
+	word[12+1] = (e >> 0x08) & 0xff;
+	word[12+2] = (e >> 0x10) & 0xff;
+	word[12+3] = (e >> 0x18) & 0xff;
+	e ^= BIT0MASK(message >> 5);
+	word[8+0] = (e >> 0x00) & 0xff;
+	word[8+1] = (e >> 0x08) & 0xff;
+	word[8+2] = (e >> 0x10) & 0xff;
+	word[8+3] = (e >> 0x18) & 0xff;
 }
 
 
@@ -118,19 +107,20 @@
  * @param[out] src Structure that contain the expanded codeword
  * @param[out] dst Structure that contain the expanded codeword
  */
-void hadamard(expandedCodeword *src, expandedCodeword *dst) {
+static void hadamard(uint16_t src[128], uint16_t dst[128]) {
 	// the passes move data:
 	// src -> dst -> src -> dst -> src -> dst -> src -> dst
 	// using p1 and p2 alternately
-	expandedCodeword *p1 = src;
-	expandedCodeword *p2 = dst;
-	for (int32_t pass = 0 ; pass < 7 ; pass++) {
-		for (int32_t i = 0 ; i < 64 ; i++) {
-			(*p2)[i] = (*p1)[2 * i] + (*p1)[2 * i + 1];
-			(*p2)[i + 64] = (*p1)[2 * i] - (*p1)[2 * i + 1];
+	uint16_t *p1 = src;
+	uint16_t *p2 = dst;
+	uint16_t *p3;
+	for (uint32_t pass = 0 ; pass < 7 ; pass++) {
+		for (uint32_t i = 0 ; i < 64 ; i++) {
+			p2[i] = p1[2 * i] + p1[2 * i + 1];
+			p2[i + 64] = p1[2 * i] - p1[2 * i + 1];
 		}
 		// swap p1, p2 for next round
-		expandedCodeword *p3 = p1;
+		p3 = p1;
 		p1 = p2;
 		p2 = p3;
 	}
@@ -151,18 +141,19 @@
  * @param[out] dest Structure that contain the expanded codeword
  * @param[in] src Structure that contain the codeword
  */
-void expand_and_sum(expandedCodeword *dest, codeword src[]) {
+static void expand_and_sum(uint16_t dest[128], const uint8_t src[16*MULTIPLICITY]) {
+	size_t part, bit, copy;
 	// start with the first copy
-	for (int32_t part = 0 ; part < 4 ; part++) {
-		for (int32_t bit = 0 ; bit < 32 ; bit++) {
-			(*dest)[part * 32 + bit] = src[0].u32[part] >> bit & 1;
+	for (part = 0 ; part < 16 ; part++) {
+		for (bit = 0 ; bit < 8 ; bit++) {
+			dest[part * 8 + bit] = (uint16_t) ((src[part] >> bit) & 1);
 		}
 	}
 	// sum the rest of the copies
-	for (int32_t copy = 1 ; copy < MULTIPLICITY ; copy++) {
-		for (int32_t part = 0 ; part < 4 ; part++) {
-			for (int32_t bit = 0 ; bit < 32 ; bit++) {
-				(*dest)[part * 32 + bit] += src[copy].u32[part] >> bit & 1;
+	for (copy = 1 ; copy < MULTIPLICITY ; copy++) {
+		for (part = 0 ; part < 16 ; part++) {
+			for (bit = 0 ; bit < 8 ; bit++) {
+				dest[part * 8 + bit] += (uint16_t) ((src[16*copy+part] >> bit) & 1);
 			}
 		}
 	}
@@ -179,27 +170,26 @@
  * in the lowest 7 bits it taken
  * @param[in] transform Structure that contain the expanded codeword
  */
-int32_t find_peaks(expandedCodeword *transform) {
-	int32_t peak_abs_value = 0;
-	int32_t peak_value = 0;
-	int32_t peak_pos = 0;
-	for (int32_t i = 0 ; i < 128 ; i++) {
-		// get absolute value
-		int32_t t = (*transform)[i];
-		int32_t pos_mask = -(t > 0);
-		int32_t absolute = (pos_mask & t) | (~pos_mask & -t);
-		// all compilers nowadays compile with a conditional move
-		peak_value = absolute > peak_abs_value ? t : peak_value;
-		peak_pos = absolute > peak_abs_value ? i : peak_pos;
-		peak_abs_value = absolute > peak_abs_value ? absolute : peak_abs_value;
-	}
-	// set bit 7
-	peak_pos |= 128 * (peak_value > 0);
-	return peak_pos;
+static uint8_t find_peaks(const uint16_t transform[128]) {
+	uint16_t peak_abs = 0;
+	uint16_t peak = 0;
+	uint16_t pos = 0;
+	uint16_t t, abs, mask;
+	for (uint16_t i = 0 ; i < 128 ; i++) {
+		t = transform[i];
+		abs = t^((-(t>>15)) & (t^-t)); // t = abs(t)
+		mask = -(((uint16_t)(peak_abs - abs))>>15);
+		peak ^= mask&(peak^t);
+		pos ^= mask&(pos^i);
+		peak_abs ^= mask&(peak_abs^abs);
+	}
+	pos |= 128 & ((peak >> 15) - 1);
+	return (uint8_t) pos;
 }
 
 
 
+
 /**
  * @brief Encodes the received word
  *
@@ -209,20 +199,15 @@
  * @param[out] cdw Array of size VEC_N1N2_SIZE_64 receiving the encoded message
  * @param[in] msg Array of size VEC_N1_SIZE_64 storing the message
  */
-void reed_muller_encode(uint64_t *cdw, const uint64_t *msg) {
-	uint8_t *message_array = (uint8_t *) msg;
-	codeword *codeArray = (codeword *) cdw;
+void reed_muller_encode(uint8_t *cdw, const uint8_t *msg) {
 	for (size_t i = 0 ; i < VEC_N1_SIZE_BYTES ; i++) {
-		// fill entries i * MULTIPLICITY to (i+1) * MULTIPLICITY
-		int32_t pos = i * MULTIPLICITY;
 		// encode first word
-		encode(&codeArray[pos], message_array[i]);
+		encode(&cdw[16 * i * MULTIPLICITY], msg[i]);
 		// copy to other identical codewords
 		for (size_t copy = 1 ; copy < MULTIPLICITY ; copy++) {
-			memcpy(&codeArray[pos + copy], &codeArray[pos], sizeof(codeword));
+			memcpy(&cdw[16 * i * MULTIPLICITY + 16 * copy], &cdw[16*i*MULTIPLICITY], 16);
 		}
 	}
-	return;
 }
 
 
@@ -236,19 +221,17 @@
  * @param[out] msg Array of size VEC_N1_SIZE_64 receiving the decoded message
  * @param[in] cdw Array of size VEC_N1N2_SIZE_64 storing the received word
  */
-void reed_muller_decode(uint64_t *msg, const uint64_t *cdw) {
-	uint8_t *message_array = (uint8_t *) msg;
-	codeword *codeArray = (codeword *) cdw;
-	expandedCodeword expanded;
+void reed_muller_decode(uint8_t *msg, const uint8_t *cdw) {
+	uint16_t expanded[128];
+	uint16_t transform[128];
 	for (size_t i = 0 ; i < VEC_N1_SIZE_BYTES ; i++) {
 		// collect the codewords
-		expand_and_sum(&expanded, &codeArray[i * MULTIPLICITY]);
+		expand_and_sum(expanded, &cdw[16 * i * MULTIPLICITY]);
 		// apply hadamard transform
-		expandedCodeword transform;
-		hadamard(&expanded, &transform);
+		hadamard(expanded, transform);
 		// fix the first entry to get the half Hadamard transform
 		transform[0] -= 64 * MULTIPLICITY;
 		// finish the decoding
-		message_array[i] = find_peaks(&transform);
+		msg[i] = find_peaks(transform);
 	}
 }

