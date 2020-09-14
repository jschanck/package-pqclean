--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/repetition.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/repetition.c
@@ -10,7 +10,7 @@
 #include <stdio.h>
 #include <nmmintrin.h>
 
-#define MASK_N2                              ((1UL << PARAM_N2) - 1)
+#define MASK_N2 ((((uint64_t) 1) << PARAM_N2) - 1)
 
 /**
  * @brief Decoding the code words to a message using the repetition code
@@ -23,8 +23,10 @@
  * @param[in] em Pointer to an array that is the code word
  */
 void repetition_code_decode(uint64_t *m, const uint64_t *em) {
-	size_t t = 0, b, bn, bi, c, cn, ci;
+	size_t t = 0;
+	uint32_t b, bn, bi, c, cn, ci;
 	uint64_t cx, ones;
+	uint64_t mask;
 
 	for (b = 0 ; b < PARAM_N1N2 - PARAM_N2 + 1 ; b += PARAM_N2) {
 		bn = b >> 6;
@@ -33,9 +35,9 @@
 		cn = c >> 6;
 		ci = c & 63;
 		cx = em[cn] << (63 - ci);
-		int64_t verif = (cn == (bn + 1));
-		ones = _mm_popcnt_u64(((em[bn] >> bi) & MASK_N2) | (cx * verif));
-		m[t >> 6] |= ((uint64_t)(ones > PARAM_T)) << (t & 63);
+		mask = (uint64_t) (-((int64_t) (cn ^ (bn+1))) >> 63); // cn != bn+1
+		ones = _mm_popcnt_u64(((em[bn] >> bi) & MASK_N2) | (cx & ~mask));
+		m[t >> 6] |= (uint64_t) ((((PARAM_T - ones) >> 31) & 1) << (t & 63));
 		t++;
 	}
 }

