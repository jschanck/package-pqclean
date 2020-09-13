--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/code.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/code.c
@@ -25,8 +25,8 @@
  * @param[out] em Pointer to an array that is the tensor code word
  * @param[in] m Pointer to an array that is the message
  */
-void code_encode(uint64_t *em, const uint64_t *m) {
-	uint64_t tmp[VEC_N1_SIZE_64] = {0};
+void code_encode(uint8_t *em, const uint8_t *m) {
+	uint8_t tmp[8*VEC_N1_SIZE_64] = {0};
 
 	reed_solomon_encode(tmp, m);
 	reed_muller_encode(em, tmp);
@@ -45,8 +45,8 @@
  * @param[out] m Pointer to an array that is the message
  * @param[in] em Pointer to an array that is the code word
  */
-void code_decode(uint64_t *m, const uint64_t *em) {
-	uint64_t tmp[VEC_N1_SIZE_64] = {0};
+void code_decode(uint8_t *m, const uint8_t *em) {
+	uint8_t tmp[8*VEC_N1_SIZE_64] = {0};
 
 	reed_muller_decode(tmp, em);
 	reed_solomon_decode(m, tmp);

