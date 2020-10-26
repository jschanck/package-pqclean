--- upstream/Reference_Implementation/hqc-rmrs-192/src/parameters.h
+++ upstream-patched/Reference_Implementation/hqc-rmrs-192/src/parameters.h
@@ -8,9 +8,7 @@
 
 #include "api.h"
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
-
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme
@@ -91,6 +89,7 @@
 #define PARAM_FFT                           	5
 #define RS_POLY_COEFS 45,216,239,24,253,104,27,40,107,50,163,210,227,134,224,158,119,13,158,1,238,164,82,43,15,232,246,142,50,189,29,232,1
 
+#define BITMASK(a, size)                    	((1UL << ((a) % (size))) - 1)
 #define RED_MASK                            	BITMASK(PARAM_N, 64)
 #define SHA512_BYTES                        	64
 #define SEED_BYTES                          	40

