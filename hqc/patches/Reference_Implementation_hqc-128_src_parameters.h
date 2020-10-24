--- upstream/Reference_Implementation/hqc-128/src/parameters.h
+++ upstream-patched/Reference_Implementation/hqc-128/src/parameters.h
@@ -9,8 +9,7 @@
 #ifndef HQC_PARAMETERS_H
 #define HQC_PARAMETERS_H
 
-#define CEIL_DIVIDE(a, b)  (((a)/(b)) + ((a) % (b) == 0 ? 0 : 1)) /*!< Divide a by b and ceil the result*/
-#define BITMASK(a, size) ((1UL << (a % size)) - 1) /*!< Create a mask*/
+#define CEIL_DIVIDE(a, b)  (((a)+(b)-1)/(b)) /*!< Divide a by b and ceil the result*/
 
 /*
   #define PARAM_N                             	Define the parameter n of the scheme

