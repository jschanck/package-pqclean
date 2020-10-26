--- upstream/Optimized_Implementation/hqc-rmrs-256/src/parameters.h
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-256/src/parameters.h
@@ -8,9 +8,7 @@
 
 #include "api.h"
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
-
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme
@@ -45,6 +43,8 @@
   #define PARAM_DELTA                         	Define the parameter delta of the scheme (correcting capacity of the Reed-Solomon code)
   #define PARAM_M                             	Define a positive integer
   #define PARAM_GF_POLY                       	Generator polynomial of galois field GF(2^PARAM_M), represented in hexadecimial form
+  #define PARAM_GF_POLY_WT                    	Hamming weight of PARAM_GF_POLY
+  #define PARAM_GF_POLY_M2                    	Distance between the primitive polynomial first two set bits
   #define PARAM_GF_MUL_ORDER                  	Define the size of the multiplicative group of GF(2^PARAM_M),  i.e 2^PARAM_M -1
   #define PARAM_K                             	Define the size of the information bits of the Reed-Solomon code
   #define PARAM_G                             	Define the size of the generator polynomial of Reed-Solomon code
@@ -85,20 +85,22 @@
 #define VEC_N1_SIZE_64                      	CEIL_DIVIDE(PARAM_N1, 8)
 #define VEC_N1N2_SIZE_64                    	CEIL_DIVIDE(PARAM_N1N2, 64)
 
-#define PARAM_N_MULT                        	59904
-#define VEC_N_256_SIZE_64                     (CEIL_DIVIDE(PARAM_N_MULT, 256) << 2)
+#define PARAM_N_MULT                        	(9*256*CEIL_DIVIDE(CEIL_DIVIDE(PARAM_N, 9), 256))
+#define VEC_N_256_SIZE_64                   	(PARAM_N_MULT / 64)
 #define VEC_N1N2_256_SIZE_64                	(CEIL_DIVIDE(PARAM_N1N2, 256) << 2)
 
 #define PARAM_DELTA                         	29
 #define PARAM_M                             	8
 #define PARAM_GF_POLY                       	0x11D
+#define PARAM_GF_POLY_WT                    	5
+#define PARAM_GF_POLY_M2                    	4
 #define PARAM_GF_MUL_ORDER                  	255
 #define PARAM_K                             	32
 #define PARAM_G                             	59
 #define PARAM_FFT                           	5
 #define RS_POLY_COEFS 49,167,49,39,200,121,124,91,240,63,148,71,150,123,87,101,32,215,159,71,201,115,97,210,186,183,141,217,123,12,31,243,180,219,152,239,99,141,4,246,191,144,8,232,47,27,141,178,130,64,124,47,39,188,216,48,199,187,1
 
-#define RED_MASK                            	BITMASK(PARAM_N, 64)
+#define RED_MASK                            	0x1fffffffff
 #define SHA512_BYTES                        	64
 #define SEED_BYTES                          	40
 #define SEEDEXPANDER_MAX_LENGTH             	4294967295

