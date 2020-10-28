--- upstream/Reference_Implementation_KEM/cbd.h
+++ upstream-patched/Reference_Implementation_KEM/cbd.h
@@ -5,9 +5,11 @@
 by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
 Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
 ----------------------------------------------------------------------*/
+
 #ifndef CBD_H
 #define CBD_H
 
+#include "SABER_params.h"
 #include <stdint.h>
 
 void cbd(uint16_t s[SABER_N], const uint8_t buf[SABER_POLYCOINBYTES]);

