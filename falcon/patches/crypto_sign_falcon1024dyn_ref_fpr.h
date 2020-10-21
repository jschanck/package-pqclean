--- upstream/crypto_sign/falcon1024dyn/ref/fpr.h
+++ upstream-patched/crypto_sign/falcon1024dyn/ref/fpr.h
@@ -439,20 +439,32 @@
 fpr_lt(fpr x, fpr y)
 {
 	/*
-	 * If x >= 0 or y >= 0, a signed comparison yields the proper
-	 * result:
+	 * If both x and y are positive, then a signed comparison yields
+	 * the proper result:
 	 *   - For positive values, the order is preserved.
 	 *   - The sign bit is at the same place as in integers, so
 	 *     sign is preserved.
+	 * Moreover, we can compute [x < y] as sgn(x-y) and the computation
+	 * of x-y will not overflow.
+	 *
+	 * If the signs differ, then sgn(x) gives the proper result.
 	 *
 	 * If both x and y are negative, then the order is reversed.
-	 * We cannot simply invert the comparison result in that case
-	 * because it would not handle the edge case x = y properly.
+	 * Hence [x < y] = sgn(y-x). We must compute this separately from
+	 * sgn(x-y); simply inverting sgn(x-y) would not handle the edge
+	 * case x = y properly.
 	 */
 	int cc0, cc1;
+	int64_t sx;
+	int64_t sy;
+
+	sx = *(int64_t *)&x;
+	sy = *(int64_t *)&y;
+	sy &= ~((sx ^ sy) >> 63); /* set sy=0 if signs differ */
+
+	cc0 = (int)((sx - sy) >> 63) & 1; /* Neither subtraction overflows when */
+	cc1 = (int)((sy - sx) >> 63) & 1; /* the signs are the same. */
 
-	cc0 = *(int64_t *)&x < *(int64_t *)&y;
-	cc1 = *(int64_t *)&x > *(int64_t *)&y;
 	return cc0 ^ ((cc0 ^ cc1) & (int)((x & y) >> 63));
 }
 

