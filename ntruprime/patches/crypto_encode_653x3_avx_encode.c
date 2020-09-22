--- upstream/crypto_encode/653x3/avx/encode.c
+++ upstream-patched/crypto_encode/653x3/avx/encode.c
@@ -7,13 +7,17 @@
 #define loops 6
 #define overshoot 29
 
-static const __attribute((aligned(32))) uint8 lobytes_buf[32] = {
-  255,0,255,0,255,0,255,0,
-  255,0,255,0,255,0,255,0,
-  255,0,255,0,255,0,255,0,
-  255,0,255,0,255,0,255,0,
+static const union {
+  uint8 init[32];
+  __m256i val;
+} lobytes_buf = { .init = {
+    255,0,255,0,255,0,255,0,
+    255,0,255,0,255,0,255,0,
+    255,0,255,0,255,0,255,0,
+    255,0,255,0,255,0,255,0,
+  }
 };
-#define lobytes (*(__m256i *) lobytes_buf)
+#define lobytes (lobytes_buf.val)
 
 void crypto_encode(unsigned char *s,const void *v)
 {

