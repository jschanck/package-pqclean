--- hqc-2020-05-29/Reference_Implementation/hqc-256/src/repetition.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-256/src/repetition.c
@@ -18,35 +18,21 @@
  * @param[in] m Pointer to an array that is the message
  */
 void repetition_code_encode(uint64_t *em, const uint64_t *m) {
-	static const uint64_t mask[2][3] = {{0x0UL,0x0UL,0x0UL}, {0xFFFFFFFFFFFFFFFFUL,0xFFFFFFFFFFFFFFFFUL,0x3FFFFFUL}};
-	for (size_t i = 0 ; i < VEC_N1_SIZE_64 - 1 ; i++) {
-		for (size_t j = 0 ; j < 64 ; j++) {
-			uint8_t bit = (m[i] >> j) & 0x1;
-			uint32_t pos_r = PARAM_N2 * ((i << 6) + j);
-			uint16_t idx_r = (pos_r & 0x3f);
-			uint64_t *p64 = em;
-			p64 += pos_r >> 6;
-			*p64 ^= mask[bit][0] << idx_r;
-			int64_t aux = (41 - idx_r);
-			uint64_t aux2 = (aux > 0);
-			uint64_t idx2 = aux * aux2;
-			*(p64 + 1) ^= mask[bit][1] >> idx2;
-			*(p64 + 2) ^= mask[bit][2] >> ((63 - idx_r));
-		}
-	}
+	uint64_t bit, idx_r, idx2;
+	size_t pos_r;
 
-	for (size_t j = 0 ; j < (PARAM_N1 & 0x3f) ; j++) {
-		uint8_t bit = (m[VEC_N1_SIZE_64 - 1] >> j) & 0x1;
-		uint32_t pos_r = PARAM_N2 * (((VEC_N1_SIZE_64 - 1) << 6) + j);
-		uint16_t idx_r = (pos_r & 0x3f);
-		uint64_t *p64 = em;
-		p64 += pos_r >> 6;
-		*p64 ^= mask[bit][0] << idx_r;
-		int64_t aux = (41 - idx_r);
-		uint64_t aux2 = (aux > 0);
-		uint64_t idx2 = aux * aux2;
-		*(p64 + 1) ^= mask[bit][1] >> idx2;
-		*(p64 + 2) ^= mask[bit][2] >> ((63 - idx_r));
+	pos_r = 0;
+	for (size_t i = 0 ; i < VEC_N1_SIZE_64 ; i++) {
+		for (size_t j = 0 ; j < 64 && pos_r < PARAM_N1N2; j++) {
+			bit = -((m[i] >> j) & 1);
+			idx_r = (pos_r & 0x3f);
+			idx2 = 41 - idx_r;
+			idx2 &= (uint64_t) (-((int64_t)idx2) >> 63);
+			em[(pos_r>>6)+0] ^= (bit&0xFFFFFFFFFFFFFFFFUL) << idx_r;
+			em[(pos_r>>6)+1] ^= (bit&0xFFFFFFFFFFFFFFFFUL) >> idx2;
+			em[(pos_r>>6)+2] ^= (bit&0x3FFFFFUL) >> ((63 - idx_r));
+			pos_r += PARAM_N2;
+		}
 	}
 }
 
@@ -80,9 +66,11 @@
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
@@ -91,10 +79,10 @@
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

