--- upstream/crypto_sign/falcon1024dyn/avx2/sign.c
+++ upstream-patched/crypto_sign/falcon1024dyn/avx2/sign.c
@@ -1024,7 +1024,7 @@
 	 * values. We need both a "greater than" and an "equal"
 	 * comparisons.
 	 */
-	xhi = _mm256_broadcastw_epi16(_mm_cvtsi32_si128(hi));
+	xhi = _mm256_broadcastw_epi16(_mm_cvtsi32_si128((int32_t)hi));
 	rhi = _mm256_loadu_si256(&rhi15.ymm[0]);
 	gthi = _mm256_cmpgt_epi16(rhi, xhi);
 	eqhi = _mm256_cmpeq_epi16(rhi, xhi);
@@ -1175,8 +1175,8 @@
 falcon1024dyn_avx2_sampler(void *ctx, fpr mu, fpr isigma)
 {
 	sampler_context *spc;
-	int s;
-	fpr r, dss, ccs;
+	int s, z0, z, b;
+	fpr r, dss, ccs, x;
 
 	spc = ctx;
 
@@ -1201,9 +1201,6 @@
 	 * We now need to sample on center r.
 	 */
 	for (;;) {
-		int z0, z, b;
-		fpr x;
-
 		/*
 		 * Sample z for a Gaussian distribution. Then get a
 		 * random bit b to turn the sampling into a bimodal
@@ -1216,7 +1213,7 @@
 		 *    centered on 0.
 		 */
 		z0 = falcon1024dyn_avx2_gaussian0_sampler(&spc->p);
-		b = prng_get_u8(&spc->p) & 1;
+		b = (int)prng_get_u8(&spc->p) & 1;
 		z = b + ((b << 1) - 1) * z0;
 
 		/*
@@ -1284,11 +1281,13 @@
 		 * Normal sampling. We use a fast PRNG seeded from our
 		 * SHAKE context ('rng').
 		 */
-		spc.sigma_min = (logn == 10)
-			? fpr_sigma_min_10
-			: fpr_sigma_min_9;
-		falcon1024dyn_avx2_prng_init(&spc.p, rng);
-		samp = falcon1024dyn_avx2_sampler;
+		if (logn == 10) {
+			spc.sigma_min = fpr_sigma_min_10;
+		} else {
+			spc.sigma_min = fpr_sigma_min_9;
+		}
+		falcon1024dyn_ref_prng_init(&spc.p, rng);
+		samp = falcon1024dyn_ref_sampler;
 		samp_ctx = &spc;
 
 		/*
@@ -1331,11 +1330,13 @@
 		 * Normal sampling. We use a fast PRNG seeded from our
 		 * SHAKE context ('rng').
 		 */
-		spc.sigma_min = (logn == 10)
-			? fpr_sigma_min_10
-			: fpr_sigma_min_9;
-		falcon1024dyn_avx2_prng_init(&spc.p, rng);
-		samp = falcon1024dyn_avx2_sampler;
+		if (logn == 10) {
+			spc.sigma_min = fpr_sigma_min_10;
+		} else {
+			spc.sigma_min = fpr_sigma_min_9;
+		}
+		falcon1024dyn_ref_prng_init(&spc.p, rng);
+		samp = falcon1024dyn_ref_sampler;
 		samp_ctx = &spc;
 
 		/*

