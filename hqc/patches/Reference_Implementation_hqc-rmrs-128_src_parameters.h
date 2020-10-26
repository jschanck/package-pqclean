--- upstream/Reference_Implementation/hqc-rmrs-128/src/parameters.h
+++ upstream-patched/Reference_Implementation/hqc-rmrs-128/src/parameters.h
@@ -8,9 +8,7 @@
 
 #include "api.h"
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
-
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme
@@ -88,9 +86,10 @@
 #define PARAM_GF_MUL_ORDER                  	255
 #define PARAM_K                             	16
 #define PARAM_G                             	31
-#define PARAM_FFT                           	4
+#define PARAM_FFT                           	5
 #define RS_POLY_COEFS 89,69,153,116,176,117,111,75,73,233,242,233,65,210,21,139,103,173,67,118,105,210,174,110,74,69,228,82,255,181,1
 
+#define BITMASK(a, size)                    	((1UL << ((a) % (size))) - 1)
 #define RED_MASK                            	BITMASK(PARAM_N, 64)
 #define SHA512_BYTES                        	64
 #define SEED_BYTES                          	40

