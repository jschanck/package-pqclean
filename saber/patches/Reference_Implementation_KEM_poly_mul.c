--- upstream/Reference_Implementation_KEM/poly_mul.c
+++ upstream-patched/Reference_Implementation_KEM/poly_mul.c
@@ -1,6 +1,6 @@
 #include "poly_mul.h"
 #include <stdint.h>
-#include <string.h>
+#include <stddef.h>
 
 #define SCHB_N 16
 
@@ -11,13 +11,13 @@
 #define OVERFLOWING_MUL(X, Y) ((uint16_t)((uint32_t)(X) * (uint32_t)(Y)))
 
 #define KARATSUBA_N 64
-static void karatsuba_simple(const uint16_t *a_1, const uint16_t *b_1, uint16_t *result_final) {
+static void karatsuba_simple(uint16_t *result_final, const uint16_t *a_1, const uint16_t *b_1) {
     uint16_t d01[KARATSUBA_N / 2 - 1];
     uint16_t d0123[KARATSUBA_N / 2 - 1];
     uint16_t d23[KARATSUBA_N / 2 - 1];
     uint16_t result_d01[KARATSUBA_N - 1];
 
-    int32_t i, j;
+    size_t i, j;
 
     memset(result_d01, 0, (KARATSUBA_N - 1)*sizeof(uint16_t));
     memset(d01, 0, (KARATSUBA_N / 2 - 1)*sizeof(uint16_t));
@@ -181,13 +181,13 @@
 
     // MULTIPLICATION
 
-    karatsuba_simple(aw1, bw1, w1);
-    karatsuba_simple(aw2, bw2, w2);
-    karatsuba_simple(aw3, bw3, w3);
-    karatsuba_simple(aw4, bw4, w4);
-    karatsuba_simple(aw5, bw5, w5);
-    karatsuba_simple(aw6, bw6, w6);
-    karatsuba_simple(aw7, bw7, w7);
+    karatsuba_simple(w1, aw1, bw1);
+    karatsuba_simple(w2, aw2, bw2);
+    karatsuba_simple(w3, aw3, bw3);
+    karatsuba_simple(w4, aw4, bw4);
+    karatsuba_simple(w5, aw5, bw5);
+    karatsuba_simple(w6, aw6, bw6);
+    karatsuba_simple(w7, aw7, bw7);
 
     // INTERPOLATION
     for (i = 0; i < N_SB_RES; ++i) {
@@ -229,12 +229,12 @@
 }
 
 /* res += a*b */
-void poly_mul_acc(const uint16_t a[SABER_N], const uint16_t b[SABER_N], uint16_t res[SABER_N])
+void poly_mul_acc(uint16_t res[SABER_N], const uint16_t a[SABER_N], const uint16_t b[SABER_N])
 {
 	uint16_t c[2 * SABER_N] = {0};
-	int i;
+	size_t i;
 
-	toom_cook_4way(a, b, c);
+	toom_cook_4way(c, a, b);
 
 	/* reduction */
 	for (i = SABER_N; i < 2 * SABER_N; i++)

