--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/parameters.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/parameters.h
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
@@ -92,6 +92,8 @@
 #define PARAM_DELTA                         	22
 #define PARAM_M                             	8
 #define PARAM_GF_POLY                       	0x11D
+#define PARAM_GF_POLY_WT                    	5
+#define PARAM_GF_POLY_M2                    	4
 #define PARAM_GF_MUL_ORDER                  	255
 #define PARAM_K                             	32
 #define PARAM_G                             	45

