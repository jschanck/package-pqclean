--- upstream/Reference_Implementation_KEM/verify.c
+++ upstream-patched/Reference_Implementation_KEM/verify.c
@@ -5,12 +5,11 @@
  by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
 Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
 ----------------------------------------------------*/
-#include <string.h>
-#include <stdint.h>
+
 #include "verify.h"
 
 /* returns 0 for equal strings, 1 for non-equal strings */
-int verify(const unsigned char *a, const unsigned char *b, size_t len)
+uint8_t verify(const uint8_t *a, const uint8_t *b, size_t len)
 {
   uint64_t r;
   size_t i;
@@ -19,12 +18,13 @@
   for (i = 0; i < len; i++)
     r |= a[i] ^ b[i];
 
-  r = (-r) >> 63;
-  return r;
+  r = (~r + 1); // Two's complement
+  r >>= 63;
+  return (uint8_t) r;
 }
 
 /* b = 1 means mov, b = 0 means don't mov*/
-void cmov(unsigned char *r, const unsigned char *x, size_t len, unsigned char b)
+void cmov(uint8_t *r, const uint8_t *x, size_t len, uint8_t b)
 {
   size_t i;
 

