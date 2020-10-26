--- upstream/Reference_Implementation/hqc-rmrs-256/src/parameters.h
+++ upstream-patched/Reference_Implementation/hqc-rmrs-256/src/parameters.h
@@ -8,9 +8,7 @@
 
 #include "api.h"
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
-
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme
@@ -91,7 +89,7 @@
 #define PARAM_FFT                           	5
 #define RS_POLY_COEFS 49,167,49,39,200,121,124,91,240,63,148,71,150,123,87,101,32,215,159,71,201,115,97,210,186,183,141,217,123,12,31,243,180,219,152,239,99,141,4,246,191,144,8,232,47,27,141,178,130,64,124,47,39,188,216,48,199,187,1
 
-#define RED_MASK                            	BITMASK(PARAM_N, 64)
+#define RED_MASK                            	0x1fffffffff
 #define SHA512_BYTES                        	64
 #define SEED_BYTES                          	40
 #define SEEDEXPANDER_MAX_LENGTH             	4294967295

