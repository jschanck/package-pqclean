--- hqc-2020-05-29/Reference_Implementation/hqc-256/src/repetition.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-256/src/repetition.c
@@ -80,9 +80,11 @@
  * @param[in] em Pointer to an array that is the code word
  */
 void repetition_code_decode(uint64_t *m, const uint64_t *em) {
-	size_t t = 0, b, bn, bi, c, cn, ci;
+	uint32_t t = 0;
+	uint32_t b, bn, bi, c, cn, ci;
 	uint64_t cx, ones;
 	uint64_t cy;
+	uint64_t mask;
 
 	for (b = 0; b < PARAM_N1N2 - PARAM_N2 + 1; b += PARAM_N2) {
 		bn = b >> 6;
@@ -91,10 +93,10 @@
 		cn = c >> 6;
 		ci = c & 63;
 		cx = em[cn] << (63 - ci);
-		int64_t verif = (cn == (bn + 1));
+		mask = (uint64_t) (-((int64_t) (cn ^ (bn+1))) >> 63); // cn != bn+1
 		cy = em[bn + 1];
-		ones = popcount((em[bn] >> bi) | (cx * (1 - verif))) + popcount((1 - verif) * cy + verif * cx);
-		m[t >> 6] |= ((uint64_t) (ones > PARAM_T)) << (t & 63);
+		ones = popcount((em[bn] >> bi) | (cx & mask)) + popcount((mask & cy) + (~mask & cx));
+		m[t >> 6] |= (uint64_t) (((((int64_t)PARAM_T-ones)>>63)&1)<<(t&63)); // 1 << (t&63) if ones > PARAM_T else 0
 		t++;
 	}
 }

