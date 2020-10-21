--- upstream/crypto_sign/falcon512dyn/ref/vrfy.c
+++ upstream-patched/crypto_sign/falcon512dyn/ref/vrfy.c
@@ -828,7 +828,7 @@
 	r = 0;
 	for (u = 0; u < n; u ++) {
 		r |= (uint32_t)(tt[u] - 1);
-		h[u] = mq_div_12289(h[u], tt[u]);
+		h[u] = (uint16_t)mq_div_12289(h[u], tt[u]);
 	}
 	mq_iNTT(h, logn);
 
@@ -844,7 +844,7 @@
 
 /* see inner.h */
 int
-falcon512dyn_ref_count_nttzero(int16_t *sig, unsigned logn, uint8_t *tmp)
+falcon512dyn_ref_count_nttzero(const int16_t *sig, unsigned logn, uint8_t *tmp)
 {
 	uint16_t *s2;
 	size_t u, n;
