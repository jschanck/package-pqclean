--- upstream/Optimized_Implementation/hqc-256/src/bch.h
+++ upstream-patched/Optimized_Implementation/hqc-256/src/bch.h
@@ -12,7 +12,4 @@
 
 void bch_code_decode(uint64_t *message, uint64_t *vector);
 
-size_t compute_bch_poly(uint16_t *bch_poly, size_t *t, const uint16_t *exp, const uint16_t *log);
-void table_alphaij_generation(const uint16_t *exp);
-
 #endif

