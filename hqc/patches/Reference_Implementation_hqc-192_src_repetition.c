--- hqc-2020-05-29/Reference_Implementation/hqc-192/src/repetition.c
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-192/src/repetition.c
@@ -8,7 +8,7 @@
 #include <stdint.h>
 #include <stdio.h>
 
-#define MASK_N2                              ((1UL << PARAM_N2) - 1)
+#define MASK_N2 ((((uint64_t) 1) << PARAM_N2) - 1)
 
 static inline int32_t popcount(uint64_t n);
 

