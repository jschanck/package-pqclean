--- upstream/crypto_encode/256x2/avx/encode.c
+++ upstream-patched/crypto_encode/256x2/avx/encode.c
@@ -30,12 +30,36 @@
   int32_t c5 = _mm256_movemask_epi8(b5);
   int32_t c6 = _mm256_movemask_epi8(b6);
   int32_t c7 = _mm256_movemask_epi8(b7);
-  0[(int32_t *) s] = c0;
-  1[(int32_t *) s] = c1;
-  2[(int32_t *) s] = c2;
-  3[(int32_t *) s] = c3;
-  4[(int32_t *) s] = c4;
-  5[(int32_t *) s] = c5;
-  6[(int32_t *) s] = c6;
-  7[(int32_t *) s] = c7;
+  *s++ = (unsigned char) c0; c0 >>= 8;
+  *s++ = (unsigned char) c0; c0 >>= 8;
+  *s++ = (unsigned char) c0; c0 >>= 8;
+  *s++ = (unsigned char) c0;
+  *s++ = (unsigned char) c1; c1 >>= 8;
+  *s++ = (unsigned char) c1; c1 >>= 8;
+  *s++ = (unsigned char) c1; c1 >>= 8;
+  *s++ = (unsigned char) c1;
+  *s++ = (unsigned char) c2; c2 >>= 8;
+  *s++ = (unsigned char) c2; c2 >>= 8;
+  *s++ = (unsigned char) c2; c2 >>= 8;
+  *s++ = (unsigned char) c2;
+  *s++ = (unsigned char) c3; c3 >>= 8;
+  *s++ = (unsigned char) c3; c3 >>= 8;
+  *s++ = (unsigned char) c3; c3 >>= 8;
+  *s++ = (unsigned char) c3;
+  *s++ = (unsigned char) c4; c4 >>= 8;
+  *s++ = (unsigned char) c4; c4 >>= 8;
+  *s++ = (unsigned char) c4; c4 >>= 8;
+  *s++ = (unsigned char) c4;
+  *s++ = (unsigned char) c5; c5 >>= 8;
+  *s++ = (unsigned char) c5; c5 >>= 8;
+  *s++ = (unsigned char) c5; c5 >>= 8;
+  *s++ = (unsigned char) c5;
+  *s++ = (unsigned char) c6; c6 >>= 8;
+  *s++ = (unsigned char) c6; c6 >>= 8;
+  *s++ = (unsigned char) c6; c6 >>= 8;
+  *s++ = (unsigned char) c6;
+  *s++ = (unsigned char) c7; c7 >>= 8;
+  *s++ = (unsigned char) c7; c7 >>= 8;
+  *s++ = (unsigned char) c7; c7 >>= 8;
+  *s++ = (unsigned char) c7;
 }

