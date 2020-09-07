--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-256/src/code.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-256/src/code.h
@@ -10,7 +10,7 @@
 #include <stddef.h>
 #include <stdint.h>
 
-void code_encode(uint64_t *codeword, const uint64_t *message);
-void code_decode(uint64_t *message, const uint64_t *vector);
+void code_encode(uint64_t *em, const uint64_t *message);
+void code_decode(uint64_t *m, const uint64_t *em);
 
 #endif

