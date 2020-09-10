--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/repetition.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/repetition.c
@@ -10,7 +10,7 @@
 #include <stdio.h>
 #include <nmmintrin.h>
 
-#define MASK_N2                              ((1UL << PARAM_N2) - 1)
+#define MASK_N2 ((((uint64_t) 1) << PARAM_N2) - 1)
 
 /**
  * @brief Decoding the code words to a message using the repetition code

