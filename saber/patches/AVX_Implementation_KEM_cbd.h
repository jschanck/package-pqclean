--- upstream/AVX_Implementation_KEM/cbd.h
+++ upstream-patched/AVX_Implementation_KEM/cbd.h
@@ -9,9 +9,9 @@
 #ifndef CBD_H
 #define CBD_H
 
+#include "SABER_params.h"
 #include <stdint.h>
-#include "poly.h"
 
-void cbd(uint16_t *r, const unsigned char *buf);
+void cbd(uint16_t s[SABER_N], const uint8_t buf[SABER_POLYCOINBYTES]);
 
 #endif

