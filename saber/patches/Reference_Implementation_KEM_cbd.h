--- upstream/Reference_Implementation_KEM/cbd.h
+++ upstream-patched/Reference_Implementation_KEM/cbd.h
@@ -8,6 +8,7 @@
 #ifndef CBD_H
 #define CBD_H
 
+#include "SABER_params.h"
 #include <stdint.h>
 
 void cbd(uint16_t s[SABER_N], const uint8_t buf[SABER_POLYCOINBYTES]);

