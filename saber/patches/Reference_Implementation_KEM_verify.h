--- upstream/Reference_Implementation_KEM/verify.h
+++ upstream-patched/Reference_Implementation_KEM/verify.h
@@ -8,12 +8,13 @@
 #ifndef VERIFY_H
 #define VERIFY_H
 
-#include <stdio.h>
+#include <stddef.h>
+#include <stdint.h>
 
 /* returns 0 for equal strings, 1 for non-equal strings */
-int verify(const unsigned char *a, const unsigned char *b, size_t len);
+uint8_t verify(const uint8_t *a, const uint8_t *b, size_t len);
 
 /* b = 1 means mov, b = 0 means don't mov*/
-void cmov(unsigned char *r, const unsigned char *x, size_t len, unsigned char b);
+void cmov(uint8_t *r, const uint8_t *x, size_t len, uint8_t b);
 
 #endif
