--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-128/src/reed_muller.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-128/src/reed_muller.c
@@ -36,10 +36,10 @@
 #define BIT0MASK(x) (int32_t)(-((x) & 1))
 
 
-void encode(codeword *word, int32_t message);
-void hadamard(expandedCodeword *src, expandedCodeword *dst);
-void expand_and_sum(expandedCodeword *dest, codeword src[]);
-int32_t find_peaks(expandedCodeword *transform);
+static void encode(codeword *word, int32_t message);
+static void hadamard(expandedCodeword *src, expandedCodeword *dst);
+static void expand_and_sum(expandedCodeword *dest, codeword src[]);
+static int32_t find_peaks(expandedCodeword *transform);
 
 
 
@@ -60,7 +60,7 @@
  * @param[out] word An RM(1,7) codeword
  * @param[in] message A message
  */
-void encode(codeword *word, int32_t message) {
+static void encode(codeword *word, int32_t message) {
 	// the four parts of the word are identical
 	// except for encoding bits 5 and 6
 	int32_t first_word;
@@ -82,7 +82,6 @@
 	word->u32[3] = first_word;
 	first_word ^= BIT0MASK(message >> 5);
 	word->u32[2] = first_word;
-	return;
 }
 
 
@@ -118,7 +117,7 @@
  * @param[out] src Structure that contain the expanded codeword
  * @param[out] dst Structure that contain the expanded codeword
  */
-void hadamard(expandedCodeword *src, expandedCodeword *dst) {
+static void hadamard(expandedCodeword *src, expandedCodeword *dst) {
 	// the passes move data:
 	// src -> dst -> src -> dst -> src -> dst -> src -> dst
 	// using p1 and p2 alternately
@@ -151,7 +150,7 @@
  * @param[out] dest Structure that contain the expanded codeword
  * @param[in] src Structure that contain the codeword
  */
-void expand_and_sum(expandedCodeword *dest, codeword src[]) {
+static void expand_and_sum(expandedCodeword *dest, codeword src[]) {
 	// start with the first copy
 	for (int32_t part = 0 ; part < 4 ; part++) {
 		for (int32_t bit = 0 ; bit < 32 ; bit++) {
@@ -179,7 +178,7 @@
  * in the lowest 7 bits it taken
  * @param[in] transform Structure that contain the expanded codeword
  */
-int32_t find_peaks(expandedCodeword *transform) {
+static int32_t find_peaks(expandedCodeword *transform) {
 	int32_t peak_abs_value = 0;
 	int32_t peak_value = 0;
 	int32_t peak_pos = 0;
@@ -222,7 +221,6 @@
 			memcpy(&codeArray[pos + copy], &codeArray[pos], sizeof(codeword));
 		}
 	}
-	return;
 }
 
 

