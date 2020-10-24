--- upstream/Optimized_Implementation/hqc-rmrs-256/src/code.h
+++ upstream-patched/Optimized_Implementation/hqc-rmrs-256/src/code.h
@@ -10,7 +10,7 @@
 #include <stddef.h>
 #include <stdint.h>
 
-void code_encode(uint64_t *codeword, const uint64_t *message);
-void code_decode(uint64_t *message, const uint64_t *vector);
+void code_encode(uint8_t *em, const uint8_t *message);
+void code_decode(uint8_t *m, const uint8_t *em);
 
 #endif

