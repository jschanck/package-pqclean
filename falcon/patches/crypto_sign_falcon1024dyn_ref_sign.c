--- upstream/crypto_sign/falcon1024dyn/ref/sign.c
+++ upstream-patched/crypto_sign/falcon1024dyn/ref/sign.c
@@ -1099,8 +1099,8 @@
 falcon1024dyn_ref_sampler(void *ctx, fpr mu, fpr isigma)
 {
 	sampler_context *spc;
-	int s;
-	fpr r, dss, ccs;
+	int s, z0, z, b;
+	fpr r, dss, ccs, x;
 
 	spc = ctx;
 
@@ -1125,9 +1125,6 @@
 	 * We now need to sample on center r.
 	 */
 	for (;;) {
-		int z0, z, b;
-		fpr x;
-
 		/*
 		 * Sample z for a Gaussian distribution. Then get a
 		 * random bit b to turn the sampling into a bimodal
@@ -1140,7 +1137,7 @@
 		 *    centered on 0.
 		 */
 		z0 = falcon1024dyn_ref_gaussian0_sampler(&spc->p);
-		b = prng_get_u8(&spc->p) & 1;
+		b = (int)prng_get_u8(&spc->p) & 1;
 		z = b + ((b << 1) - 1) * z0;
 
 		/*
@@ -1208,9 +1205,11 @@
 		 * Normal sampling. We use a fast PRNG seeded from our
 		 * SHAKE context ('rng').
 		 */
-		spc.sigma_min = (logn == 10)
-			? fpr_sigma_min_10
-			: fpr_sigma_min_9;
+		if (logn == 10) {
+			spc.sigma_min = fpr_sigma_min_10;
+		} else {
+			spc.sigma_min = fpr_sigma_min_9;
+		}
 		falcon1024dyn_ref_prng_init(&spc.p, rng);
 		samp = falcon1024dyn_ref_sampler;
 		samp_ctx = &spc;
@@ -1255,9 +1254,11 @@
 		 * Normal sampling. We use a fast PRNG seeded from our
 		 * SHAKE context ('rng').
 		 */
-		spc.sigma_min = (logn == 10)
-			? fpr_sigma_min_10
-			: fpr_sigma_min_9;
+		if (logn == 10) {
+			spc.sigma_min = fpr_sigma_min_10;
+		} else {
+			spc.sigma_min = fpr_sigma_min_9;
+		}
 		falcon1024dyn_ref_prng_init(&spc.p, rng);
 		samp = falcon1024dyn_ref_sampler;
 		samp_ctx = &spc;

