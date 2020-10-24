--- upstream/Optimized_Implementation/hqc-128/src/parameters.h
+++ upstream-patched/Optimized_Implementation/hqc-128/src/parameters.h
@@ -9,8 +9,7 @@
 #ifndef HQC_PARAMETERS_H
 #define HQC_PARAMETERS_H
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme
@@ -47,6 +46,8 @@
   #define PARAM_DELTA                         	Define the parameter delta of the scheme (correcting capacity of the BCH code)
   #define PARAM_M                             	Define a positive integer
   #define PARAM_GF_POLY                       	Generator polynomial of galois field GF(2^PARAM_M), represented in hexadecimial form
+  #define PARAM_GF_POLY_WT                    	Hamming weight of PARAM_GF_POLY
+  #define PARAM_GF_POLY_M2                    	Distance between the primitive polynomial first two set bits
   #define PARAM_GF_MUL_ORDER                  	Define the size of the multiplicative group of GF(2^PARAM_M),  i.e 2^PARAM_M -1
   #define PARAM_K                             	Define the size of the information bits of the BCH code
   #define PARAM_G                             	Define the size of the generator polynomial of BCH code
@@ -96,6 +97,8 @@
 #define PARAM_DELTA                         	57
 #define PARAM_M                             	10
 #define PARAM_GF_POLY                       	0x409
+#define PARAM_GF_POLY_WT                    	3
+#define PARAM_GF_POLY_M2                    	7
 #define PARAM_GF_MUL_ORDER                  	1023
 #define PARAM_K                             	256
 #define PARAM_G                             	511

