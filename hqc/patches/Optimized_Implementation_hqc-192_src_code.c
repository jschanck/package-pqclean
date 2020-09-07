--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/code.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/code.c
@@ -11,7 +11,6 @@
 #include <stdint.h>
 #include <string.h>
 #include <immintrin.h>
-#include <x86intrin.h>
 #ifdef VERBOSE
 #include <stdio.h>
 #include "vector.h"
@@ -63,7 +62,7 @@
 		aux0 = _mm256_shuffle_epi32(y, 0x4e);
 		// y = (y0^y1^y2^y3 repeated 4 times)
 		y = _mm256_xor_si256(aux0, y);
-		res = _popcnt64(_mm256_extract_epi64(y, 0)) & 1;
+		res = _mm_popcnt_u64(_mm256_extract_epi64(y, 0)) & 1;
 
 		#ifdef VERBOSE
 			tmp[i / 64] |= (res << (cpt_blocs % 64));

