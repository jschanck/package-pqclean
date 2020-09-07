--- hqc-2020-05-29/Optimized_Implementation/hqc-192/src/gf.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-192/src/gf.h
@@ -9,7 +9,7 @@
 #include <stddef.h>
 #include <stdint.h>
 
-void gf_generate(uint16_t *exp, uint16_t *log, const int16_t m);
+void gf_generate(uint16_t *exp, uint16_t *log, int16_t m);
 
 uint16_t gf_log(uint16_t elt);
 uint16_t gf_mul(uint16_t a, uint16_t b);

