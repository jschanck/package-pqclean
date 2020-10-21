--- upstream/crypto_sign/falcon1024dyn/ref/keygen.c
+++ upstream-patched/crypto_sign/falcon1024dyn/ref/keygen.c
@@ -1929,7 +1929,11 @@
 		 * Get the next word of y (scaled).
 		 */
 		v = u - sch;
-		wy = v < ylen ? y[v] : ysign;
+		if (v < ylen) {
+			wy = y[v];
+		} else {
+			wy = ysign;
+		}
 		wys = ((wy << scl) & 0x7FFFFFFF) | tw;
 		tw = wy >> (31 - scl);
 
@@ -1988,7 +1992,11 @@
 		 * Get the next word of y (scaled).
 		 */
 		v = u - sch;
-		wy = v < ylen ? y[v] : ysign;
+		if (v < ylen) {
+			wy = y[v];
+		} else {
+			wy = ysign;
+		}
 		wys = ((wy << scl) & 0x7FFFFFFF) | tw;
 		tw = wy >> (31 - scl);
 
@@ -2206,9 +2214,32 @@
 /* ==================================================================== */
 
 
-#define RNG_CONTEXT   prng
-#define get_rng_u64   prng_get_u64
+#define RNG_CONTEXT   inner_shake256_context
 
+/*
+ * Get a random 8-byte integer from a SHAKE-based RNG. This function
+ * ensures consistent interpretation of the SHAKE output so that
+ * the same values will be obtained over different platforms, in case
+ * a known seed is used.
+ */
+static inline uint64_t
+get_rng_u64(inner_shake256_context *rng) {
+    /*
+     * We enforce little-endian representation.
+     */
+
+    uint8_t tmp[8];
+
+    inner_shake256_extract(rng, tmp, sizeof tmp);
+    return (uint64_t)tmp[0]
+           | ((uint64_t)tmp[1] << 8)
+           | ((uint64_t)tmp[2] << 16)
+           | ((uint64_t)tmp[3] << 24)
+           | ((uint64_t)tmp[4] << 32)
+           | ((uint64_t)tmp[5] << 40)
+           | ((uint64_t)tmp[6] << 48)
+           | ((uint64_t)tmp[7] << 56);
+}
 
 /*
  * Table below incarnates a discrete Gaussian distribution:
@@ -2286,8 +2317,8 @@
 		v = 0;
 		r = get_rng_u64(rng);
 		r &= ~((uint64_t)1 << 63);
-		for (k = 1; k < (sizeof gauss_1024_12289)
-			/ (sizeof gauss_1024_12289[0]); k ++)
+		for (k = 1; k < (uint32_t)((sizeof gauss_1024_12289)
+		                           / (sizeof gauss_1024_12289[0])); k ++)
 		{
 			uint32_t t;
 
@@ -2666,10 +2697,18 @@
 		return;
 	}
 
-	for (d = 0; d < depth; d ++) {
-		make_fg_step(data, logn - d, d,
-			d != 0, (d + 1) < depth || out_ntt);
+	if (depth == 0) {
+		return;
+	}
+	if (depth == 1) {
+		make_fg_step(data, logn, 0, 0, out_ntt);
+		return;
 	}
+	make_fg_step(data, logn, 0, 0, 1);
+	for (d = 1; d + 1 < depth; d ++) {
+		make_fg_step(data, logn - d, d, 1, 1);
+	}
+	make_fg_step(data, logn - depth + 1, depth - 1, 1, out_ntt);
 }
 
 /*
@@ -3054,7 +3093,10 @@
 	 * computed so that average maximum length will fall in the
 	 * middle or the upper half of these top 10 words.
 	 */
-	rlen = (slen > 10) ? 10 : slen;
+	rlen = slen;
+	if (rlen > 10) {
+		rlen = 10;
+	}
 	poly_big_to_fp(rt3, ft + slen - rlen, rlen, slen, logn);
 	poly_big_to_fp(rt4, gt + slen - rlen, rlen, slen, logn);
 
@@ -3128,7 +3170,10 @@
 		 * Convert current F and G into floating-point. We apply
 		 * scaling if the current length is more than 10 words.
 		 */
-		rlen = (FGlen > 10) ? 10 : FGlen;
+		rlen = FGlen;
+		if (rlen > 10) {
+			rlen = 10;
+		}
 		scale_FG = 31 * (int)(FGlen - rlen);
 		poly_big_to_fp(rt1, Ft + FGlen - rlen, rlen, llen, logn);
 		poly_big_to_fp(rt2, Gt + FGlen - rlen, rlen, llen, logn);
@@ -4114,11 +4159,9 @@
 	size_t n, u;
 	uint16_t *h2, *tmp2;
 	RNG_CONTEXT *rc;
-	prng p;
 
 	n = MKN(logn);
-	falcon1024dyn_ref_prng_init(&p, rng);
-	rc = &p;
+	rc = rng;
 
 	/*
 	 * We need to generate f and g randomly, until we find values

