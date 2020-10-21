--- upstream/crypto_sign/falcon1024dyn/avx2/rng.c
+++ upstream-patched/crypto_sign/falcon1024dyn/avx2/rng.c
@@ -171,17 +171,17 @@
 	 */
 	for (u = 0; u < 4; u ++) {
 		state[u] = init[u] =
-			_mm256_broadcastd_epi32(_mm_cvtsi32_si128(CW[u]));
+			_mm256_broadcastd_epi32(_mm_cvtsi32_si128((int32_t)CW[u]));
 	}
 	for (u = 0; u < 10; u ++) {
 		state[u + 4] = init[u + 4] =
-			_mm256_broadcastd_epi32(_mm_cvtsi32_si128(sw[u]));
+			_mm256_broadcastd_epi32(_mm_cvtsi32_si128((int32_t)sw[u]));
 	}
 	state[14] = init[14] = _mm256_xor_si256(
-		_mm256_broadcastd_epi32(_mm_cvtsi32_si128(sw[10])),
+		_mm256_broadcastd_epi32(_mm_cvtsi32_si128((int32_t)sw[10])),
 		_mm256_loadu_si256((__m256i *)&t.w[0]));
 	state[15] = init[15] = _mm256_xor_si256(
-		_mm256_broadcastd_epi32(_mm_cvtsi32_si128(sw[11])),
+		_mm256_broadcastd_epi32(_mm_cvtsi32_si128((int32_t)sw[11])),
 		_mm256_loadu_si256((__m256i *)&t.w[8]));
 
 	/*

