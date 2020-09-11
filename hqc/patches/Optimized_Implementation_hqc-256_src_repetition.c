--- hqc-2020-05-29/Optimized_Implementation/hqc-256/src/repetition.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-256/src/repetition.c
@@ -22,21 +22,23 @@
  * @param[in] em Pointer to an array that is the code word
  */
 void repetition_code_decode(uint64_t *m, const uint64_t *em) {
-	size_t t = 0, b, bn, bi, c, cn, ci;
+	uint32_t t = 0;
+	uint32_t b, bn, bi, c, cn, ci;
 	uint64_t cx, ones;
 	uint64_t cy;
+	uint64_t mask;
 
-	for (b = 0 ; b < PARAM_N1N2 - PARAM_N2 + 1 ; b += PARAM_N2) {
+	for (b = 0; b < PARAM_N1N2 - PARAM_N2 + 1; b += PARAM_N2) {
 		bn = b >> 6;
 		bi = b & 63;
 		c = b + PARAM_N2 - 1;
 		cn = c >> 6;
 		ci = c & 63;
 		cx = em[cn] << (63 - ci);
-		int64_t verif = (cn == (bn + 1));
+		mask = (uint64_t) (-((int64_t) (cn ^ (bn+1))) >> 63); // cn != bn+1
 		cy = em[bn + 1];
-		ones = _mm_popcnt_u64((em[bn] >> bi) | (cx*(1 - verif))) + _mm_popcnt_u64((1 - verif) * cy + verif * cx);
-		m[t >> 6] |= ((uint64_t)(ones > PARAM_T)) << (t & 63);
+		ones = _mm_popcnt_u64((em[bn] >> bi) | (cx & mask)) + _mm_popcnt_u64((mask & cy) + (~mask & cx));
+		m[t >> 6] |= (uint64_t) (((((int64_t)PARAM_T-ones)>>63)&1)<<(t&63)); // 1 << (t&63) if ones > PARAM_T else 0
 		t++;
 	}
 }

