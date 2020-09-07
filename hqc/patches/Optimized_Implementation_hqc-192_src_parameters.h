--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/parameters.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/parameters.h
@@ -10,7 +10,7 @@
 #define HQC_PARAMETERS_H
 
 #define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
+#define BITMASK(a, size) ((1UL << ((a) % (size))) - 1) /*!< Create a mask*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme

