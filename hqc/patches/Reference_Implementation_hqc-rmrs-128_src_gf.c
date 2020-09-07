--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-128/src/gf.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-128/src/gf.c
@@ -17,7 +17,7 @@
  * @param[out] log Array of size 2^PARAM_M receiving the logarithms of the elements of GF(2^m)
  * @param[in] m Parameter of Galois field GF(2^m)
  */
-void gf_generate(uint16_t *exp, uint16_t *log, const int16_t m) {
+void gf_generate(uint16_t *exp, uint16_t *log, int16_t m) {
 	uint16_t elt = 1;
 	uint16_t alpha = 2; // primitive element of GF(2^PARAM_M)
 	uint16_t gf_poly = PARAM_GF_POLY;
@@ -107,10 +107,10 @@
  * @param[in] i The integer whose modulo is taken
  */
 uint16_t gf_mod(uint16_t i) {
-	uint16_t tmp = i - PARAM_GF_MUL_ORDER;
+	uint16_t tmp = (uint16_t) (i - PARAM_GF_MUL_ORDER);
 
 	// mask = 0xffff if(i < PARAM_GF_MUL_ORDER)
-	int16_t mask = -(tmp >> 15);
+	uint16_t mask = ~(tmp >> 15)+1;
 
 	return tmp + (mask & PARAM_GF_MUL_ORDER);
 }

