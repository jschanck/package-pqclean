--- hqc-2020-05-29/Reference_Implementation/hqc-128/src/repetition.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-128/src/repetition.c
@@ -8,7 +8,7 @@
 #include <stdint.h>
 #include <stdio.h>
 
-#define MASK_N2                              ((1UL << PARAM_N2) - 1)
+#define MASK_N2 ((((uint64_t) 1) << PARAM_N2) - 1)
 
 static inline int32_t popcount(uint64_t n);
 
@@ -20,27 +20,26 @@
  * @param[in] m Pointer to an array that is the message
  */
 void repetition_code_encode(uint64_t *em, const uint64_t *m) {
-	static const uint64_t mask[2][2] = {{0x0UL,0x0UL}, {0x7FFFFFFFUL,0x3FFFFFFFUL}};
-	for (size_t i = 0 ; i < VEC_N1_SIZE_64 - 1 ; i++) {
-		for (size_t j = 0 ; j < 64 ; j++) {
-			uint8_t bit = (m[i] >> j) & 0x1;
-			uint32_t pos_r = PARAM_N2 * ((i << 6) + j);
-			uint16_t idx_r = (pos_r & 0x3f);
-			uint64_t *p64 = em;
-			p64 += pos_r >> 6;
-			*p64 ^= mask[bit][0] << idx_r;
-			*(p64 + 1) ^= mask[bit][1] >> ((63 - idx_r));
+	uint16_t i, j, bit, idx_r;
+	uint32_t pos_r;
+	uint64_t *p64 = em;
+	const uint64_t mask[2][2] = {{0x0UL,0x0UL}, {0x7FFFFFFFUL,0x3FFFFFFFUL}};
+	for (i = 0 ; i < VEC_N1_SIZE_64 - 1 ; i++) {
+		for (j = 0 ; j < 64 ; j++) {
+			bit = (m[i] >> j) & 0x1;
+			pos_r = PARAM_N2 * ((i << 6) + j);
+			idx_r = (pos_r & 0x3f);
+			p64[pos_r >> 6] ^= mask[bit][0] << idx_r;
+			p64[(pos_r >> 6) + 1] ^= mask[bit][1] >> ((63 - idx_r));
 		}
 	}
 
-	for (size_t j = 0 ; j < (PARAM_N1 & 0x3f) ; j++) {
-		uint8_t bit = (m[VEC_N1_SIZE_64 - 1] >> j) & 0x1;
-		uint32_t pos_r = PARAM_N2 * (((VEC_N1_SIZE_64 - 1) << 6) + j);
-		uint16_t idx_r = (pos_r & 0x3f);
-		uint64_t *p64 = em;
-		p64 += pos_r >> 6;
-		*p64 ^= mask[bit][0] << idx_r;
-		*(p64 + 1) ^= mask[bit][1] >> ((63 - idx_r));
+	for (j = 0 ; j < (PARAM_N1 & 0x3f) ; j++) {
+		bit = (m[VEC_N1_SIZE_64 - 1] >> j) & 0x1;
+		pos_r = PARAM_N2 * (((VEC_N1_SIZE_64 - 1) << 6) + j);
+		idx_r = (pos_r & 0x3f);
+		p64[pos_r >> 6] ^= mask[bit][0] << idx_r;
+		p64[(pos_r >> 6)+1] ^= mask[bit][1] >> ((63 - idx_r));
 	}
 }
 
@@ -74,8 +73,10 @@
  * @param[in] em Pointer to an array that is the code word
  */
 void repetition_code_decode(uint64_t *m, const uint64_t *em) {
-	size_t t = 0, b, bn, bi, c, cn, ci;
+	size_t t = 0;
+	uint32_t b, bn, bi, c, cn, ci;
 	uint64_t cx, ones;
+  uint64_t mask;
 
 	for (b = 0 ; b < PARAM_N1N2 - PARAM_N2 + 1 ; b += PARAM_N2) {
 		bn = b >> 6;
@@ -84,9 +85,9 @@
 		cn = c >> 6;
 		ci = c & 63;
 		cx = em[cn] << (63 - ci);
-		int64_t verif = (cn == (bn + 1));
-		ones = popcount(((em[bn] >> bi) & MASK_N2) | (cx * verif));
-		m[t >> 6] |= ((uint64_t) (ones > PARAM_T)) << (t & 63);
+		mask = (uint64_t) (-((int64_t) (cn ^ (bn+1))) >> 63); // cn != bn+1
+		ones = popcount(((em[bn] >> bi) & MASK_N2) | (cx & ~mask));
+		m[t >> 6] |= (uint64_t) ((((PARAM_T - ones) >> 31) & 1) << (t & 63));
 		t++;
 	}
 }

