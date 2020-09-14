--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/reed_muller.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/reed_muller.c
@@ -7,46 +7,18 @@
 #include "parameters.h"
 #include <stdint.h>
 #include <string.h>
-#include <x86intrin.h>
+#include <immintrin.h>
 
 // number of repeated code words
 #define MULTIPLICITY                   CEIL_DIVIDE(PARAM_N2, 128)
 
-// codeword is 128 bits, seen multiple ways
-typedef union {
-	__mmask16 mask[8];
-	uint16_t u16[8];
-	uint32_t u32[4];
-} codeword __attribute__ ((aligned (16)));
-
-// a 256 bit vector of 16 ints of 16 bits
-typedef int16_t i16x16 __attribute__ ((vector_size (32)));
-typedef uint16_t u16x16 __attribute__ ((vector_size (32)));
-
-typedef union {
-	__m256i mm;
-	u16x16 v;
-} vector __attribute__ ((aligned (32)));
-
-// Expanded codeword is 16*128 bits, seen multiple ways
-typedef union {
-	__m256i mm[8];     // four intel vectors
-	i16x16 v[8];       // four vectors of 32 ints
-	int16_t i16[128];
-} expandedCodeword __attribute__ ((aligned (32)));
-
-const i16x16  count_vector = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
-const vector bit_vector = {.v = {
-	1<<0, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7,
-	1<<8, 1<<9, 1<<10, 1<<11, 1<<12, 1<<13, 1<<14, 1<<15}};
-
 // copy bit 0 into all bits of a 64 bit value
 #define BIT0MASK(x) (int64_t)(-((x) & 1))
 
-void encode(codeword *word, int32_t message);
-void expand_and_sum(expandedCodeword *dst, codeword src[]);
-void hadamard(expandedCodeword *src, expandedCodeword *dst);
-int32_t find_peaks(expandedCodeword *transform);
+static void encode(uint8_t *word, uint8_t message);
+static void expand_and_sum(__m256i *dst, const uint64_t *src);
+static void hadamard(__m256i *src, __m256i *dst);
+static uint32_t find_peaks(__m256i *transform);
 
 
 
@@ -67,29 +39,38 @@
  * @param[out] word An RM(1,7) codeword
  * @param[in] message A message to encode
  */
-inline void encode(codeword *word, int32_t message) {
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
 
 
@@ -106,15 +87,18 @@
  * @param[out] dst Structure that contain the expanded codeword
  * @param[in] src Structure that contain the codeword
  */
-inline void expand_and_sum(expandedCodeword *dst, codeword src[]) {
-	// start converting the first copy
+inline void expand_and_sum(__m256i *dst, const uint64_t *src) {
+	uint16_t v[16];
 	for (size_t part = 0 ; part < 8 ; part++) {
-		dst->v[part] = src->u16[part] >> count_vector & 1;
+		dst[part] = _mm256_setzero_si256();
 	}
-	// sum the rest of the copies
-	for (size_t copy = 1 ; copy < MULTIPLICITY ; copy++) {
-		for (size_t part = 0 ; part < 8 ; part++) {
-			dst->v[part] += src[copy].u16[part] >> count_vector & 1;
+	for (size_t copy = 0 ; copy < MULTIPLICITY ; copy++) {
+		for (size_t part = 0; part < 8; part++) {
+			for (size_t bit = 0; bit < 16; bit++) {
+				v[bit] = (((uint16_t *)(&src[2*copy]))[part] >> bit) & 1;
+			}
+			dst[part] += _mm256_set_epi16(v[15],v[14],v[13],v[12],v[11],v[10],v[9],v[8],
+				                            v[7],v[6],v[5],v[4],v[3],v[2],v[1],v[0]);
 		}
 	}
 }
@@ -152,21 +136,22 @@
  * @param[out] src Structure that contain the expanded codeword
  * @param[out] dst Structure that contain the expanded codeword
  */
-inline void hadamard(expandedCodeword *src, expandedCodeword *dst) {
+inline void hadamard(__m256i *src, __m256i *dst) {
 	// the passes move data:
 	// src -> dst -> src -> dst -> src -> dst -> src -> dst
 	// using p1 and p2 alternately
-	expandedCodeword *p1 = src;
-	expandedCodeword *p2 = dst;
+	__m256i *p1 = src;
+	__m256i *p2 = dst;
+	__m256i *p3;
 	for (size_t pass = 0 ; pass < 7 ; pass++) {
 		// warning: hadd works "within lanes" as Intel call it
 		// so you have to swap the middle 64 bit blocks of the result
 		for (size_t part = 0 ; part < 4 ; part++) {
-			p2->mm[part] = _mm256_permute4x64_epi64(_mm256_hadd_epi16(p1->mm[2 * part], p1->mm[2 * part + 1]), 0xd8);
-			p2->mm[part + 4] = _mm256_permute4x64_epi64(_mm256_hsub_epi16(p1->mm[2 * part], p1->mm[2 * part + 1]), 0xd8);
+			p2[part] = _mm256_permute4x64_epi64(_mm256_hadd_epi16(p1[2 * part], p1[2 * part + 1]), 0xd8);
+			p2[part + 4] = _mm256_permute4x64_epi64(_mm256_hsub_epi16(p1[2 * part], p1[2 * part + 1]), 0xd8);
 		}
 		// swap p1, p2 for next round
-		expandedCodeword *p3 = p1;
+		p3 = p1;
 		p1 = p2;
 		p2 = p3;
 	}
@@ -243,13 +228,13 @@
  *
  * @param[in] transform Structure that contain the expanded codeword
  */
-inline int32_t find_peaks(expandedCodeword *transform) {
+inline uint32_t find_peaks(__m256i *transform) {
 	// a whole lot of vector variables
 	__m256i bitmap, abs_rows[8], bound, active_row, max_abs_rows;
-	vector peak_mask;
+	__m256i peak_mask;
 	// compute absolute value of transform
 	for (size_t i = 0 ; i < 8 ; i++) {
-		abs_rows[i] = _mm256_abs_epi16(transform->mm[i]);
+		abs_rows[i] = _mm256_abs_epi16(transform[i]);
 	}
 	// compute a vector of 16 elements which contains the maximum somewhere
 	// (later used to compute bits 0 through 3 of message)
@@ -316,13 +301,13 @@
 	// get the column number of the vector element
 	// by setting the bits corresponding to the columns
 	// and then adding elements within two groups of 8
-	peak_mask.mm = _mm256_cmpgt_epi16(active_row, bound);
-	peak_mask.v &= bit_vector.v;
+	peak_mask = _mm256_cmpgt_epi16(active_row, bound);
+	peak_mask &= _mm256_set_epi16(-32768,16384,8192,4096,2048,1024,512,256,128,64,32,16,8,4,2,1);
 	for (int32_t i = 0 ; i < 3 ; i++) {
-		peak_mask.mm = _mm256_hadd_epi16(peak_mask.mm, peak_mask.mm);
+		peak_mask = _mm256_hadd_epi16(peak_mask, peak_mask);
 	}
 	// add low 4 bits of message
-	message |= _bit_scan_forward(peak_mask.v[0] + peak_mask.v[8]);
+	message |= __tzcnt_u16(_mm256_extract_epi16(peak_mask, 0) + _mm256_extract_epi16(peak_mask, 8));
 
 	// set bit 7 if sign of biggest value is positive
 	// make sure a jump isn't generated by the compiler
@@ -330,7 +315,7 @@
 	for (uint32_t i = 0; i < 8; i++){
 		int64_t message_mask = (-(int64_t)(i == message/16))>>63;
 		__m256i vect_mask = (__m256i) {message_mask, message_mask, message_mask, message_mask};
-		tmp = _mm256_or_si256(tmp, _mm256_and_si256(vect_mask, transform->mm[i]));
+		tmp = _mm256_or_si256(tmp, _mm256_and_si256(vect_mask, transform[i]));
 	}
 	uint16_t result = 0;
 	for (uint32_t i = 0; i < 16; i++) {
@@ -339,7 +324,7 @@
 		result |= message_mask & ptr[i];
 	}
 	message |= (0x8000 & ~result) >> 8;
-	return message;
+	return (uint32_t) message;
 }
 
 
@@ -353,20 +338,15 @@
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
 
 
@@ -380,19 +360,18 @@
  * @param[out] msg Array of size VEC_N1_SIZE_64 receiving the decoded message
  * @param[in] cdw Array of size VEC_N1N2_SIZE_64 storing the received word
  */
-void reed_muller_decode(uint64_t *msg, const uint64_t *cdw) {
-	uint8_t *message_array = (uint8_t *) msg;
-	codeword *codeArray = (codeword *) cdw;
-	expandedCodeword expanded;
+void reed_muller_decode(uint8_t *msg, const uint8_t *cdw) {
+	__m256i expanded[8];
+	__m256i transform[8];
 	for (size_t i = 0 ; i < VEC_N1_SIZE_BYTES ; i++) {
 		// collect the codewords
-		expand_and_sum(&expanded, &codeArray[i * MULTIPLICITY]);
+		expand_and_sum(expanded, (uint64_t *)&cdw[16*i*MULTIPLICITY]);
 		// apply hadamard transform
-		expandedCodeword transform;
-		hadamard(&expanded, &transform);
+		hadamard(expanded, transform);
 		// fix the first entry to get the half Hadamard transform
-		transform.i16[0] -= 64 * MULTIPLICITY;
+		transform[0] -= _mm256_set_epi16(0,0,0,0, 0,0,0,0,
+				                             0,0,0,0, 0,0,0,64 * MULTIPLICITY);
 		// finish the decoding
-		message_array[i] = find_peaks(&transform);
+		msg[i] = find_peaks(transform);
 	}
 }

