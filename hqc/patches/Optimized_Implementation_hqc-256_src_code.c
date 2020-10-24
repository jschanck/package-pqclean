--- upstream/Optimized_Implementation/hqc-256/src/code.c
+++ upstream-patched/Optimized_Implementation/hqc-256/src/code.c
@@ -11,7 +11,6 @@
 #include <stdint.h>
 #include <string.h>
 #include <immintrin.h>
-#include <x86intrin.h>
 #ifdef VERBOSE
 #include <stdio.h>
 #include "vector.h"
@@ -39,9 +38,12 @@
  * @param[in] m Pointer to an array that is the message
  */
 void code_encode(uint64_t *em, const uint64_t *m) {
-	uint64_t res;
-	uint32_t i;
-	static const uint64_t mask[2][3] = {{0x0UL,0x0UL,0x0UL}, {0xFFFFFFFFFFFFFFFFUL,0xFFFFFFFFFFFFFFFFUL,0x3FFFFFUL}};
+	const uint64_t mask[2][3] = {{0x0UL,0x0UL,0x0UL}, {0xFFFFFFFFFFFFFFFFUL,0xFFFFFFFFFFFFFFFFUL,0x3FFFFFUL}};
+	size_t i, j, pos_r;
+	uint64_t bit;
+	uint16_t idx_r;
+	uint16_t idx_2;
+	uint64_t select;
 
 	#ifdef VERBOSE
 		uint64_t tmp[VEC_N1_SIZE_64] = {0};
@@ -52,6 +54,7 @@
 	__m256i msg = _mm256_lddqu_si256((const __m256i*) m);
 	colonne = ((__m256i*) gen_matrix);
 
+	pos_r = 0;
 	for (i = 0 ; i < PARAM_N1 - PARAM_K ; i++) {
 		// y is the and operation between m and ith column of G
 		y = _mm256_and_si256(colonne[i], msg);
@@ -63,52 +66,48 @@
 		aux0 = _mm256_shuffle_epi32(y, 0x4e);
 		// y = (y0^y1^y2^y3 repeated 4 times)
 		y = _mm256_xor_si256(aux0, y);
-		res = _popcnt64(_mm256_extract_epi64(y, 0)) & 1;
+		bit = _mm_popcnt_u64(_mm256_extract_epi64(y, 0)) & 1;
 
 		#ifdef VERBOSE
-			tmp[i / 64] |= (res << (cpt_blocs % 64));
+			tmp[i / 64] |= (bit << (cpt_blocs % 64));
 			cpt_blocs = cpt_blocs + 1;
 		#endif
 
-		uint16_t pos_r = PARAM_N2 * i;
-		uint16_t idx_r = (pos_r & 0x3f);
-		uint64_t *p64 = em;
-		p64 += pos_r >> 6;
-		uint64_t select = mux(mask[0][0],mask[1][0],res);
-		*p64 ^= select << idx_r;
-		int64_t aux = (41 - idx_r);
-		uint64_t aux2 = (aux > 0);
-		uint64_t idx2 = aux * aux2;
-		select = mux(mask[0][1],mask[1][1],res);
-		*(p64 + 1) ^= select >> idx2;
-		select = mux(mask[0][2],mask[1][2],res);
-		*(p64 + 2) ^= select >> ((63 - idx_r));
+		idx_r = (pos_r & 0x3f);
+		idx_2 = 41 - idx_r;
+		idx_2 &= (uint64_t) (-((int64_t)idx_2) >> 63);
+		select = mux(mask[0][0],mask[1][0],bit);
+		em[(pos_r>>6)+0] ^= select << idx_r;
+		select = mux(mask[0][1],mask[1][1],bit);
+		em[(pos_r>>6)+1] ^= select >> idx_2;
+		select = mux(mask[0][2],mask[1][2],bit);
+		em[(pos_r>>6)+2] ^= select >> ((63 - idx_r));
+		pos_r += PARAM_N2;
 	}
 
 	/* now we add the message m */
 	/* systematic encoding */
-	for (int32_t i = 0 ; i < 4 ; i++) {
-		for (int32_t j = 0 ; j < 64 ; j++) {
-			uint8_t bit = (m[i] >> j) & 0x1;
-			uint32_t pos_r = PARAM_N2 * ((PARAM_N1 - PARAM_K) + ((i << 6) + j));
-			uint16_t idx_r = (pos_r & 0x3f);
-			uint64_t *p64 = em;
+  pos_r = PARAM_N2 * (PARAM_N1 - PARAM_K);
+	for (i = 0 ; i < 4 ; i++) {
+		for (j = 0 ; j < 64 ; j++) {
+			bit = (m[i] >> j) & 0x1;
 
 			#ifdef VERBOSE
 				tmp[cpt_blocs / 64] |= (((uint64_t) bit) << (cpt_blocs % 64));
 				cpt_blocs = cpt_blocs + 1;
 			#endif
 
-			p64 += pos_r >> 6;
-			uint64_t select = mux(mask[0][0],mask[1][0],bit);
-			*p64 ^= select << idx_r;
-			int64_t aux = (41 - idx_r);
-			uint64_t aux2 = (aux > 0);
-			uint64_t idx2 = aux * aux2;
+			idx_r = (pos_r & 0x3f);
+			idx_2 = 41 - idx_r;
+			idx_2 &= (uint64_t) (-((int64_t)idx_2) >> 63);
+			select = mux(mask[0][0],mask[1][0],bit);
+			em[(pos_r>>6)+0] ^= select << idx_r;
 			select = mux(mask[0][1],mask[1][1],bit);
-			*(p64 + 1) ^= select >> idx2;
+			em[(pos_r>>6)+1] ^= select >> idx_2;
 			select = mux(mask[0][2],mask[1][2],bit);
-			*(p64 + 2) ^= select >> ((63 - idx_r));
+			em[(pos_r>>6)+2] ^= select >> ((63 - idx_r));
+
+			pos_r += PARAM_N2;
 		}
 	}
 

