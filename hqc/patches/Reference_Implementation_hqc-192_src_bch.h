--- hqc-2020-05-29/Reference_Implementation/hqc-192/src/bch.h
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-192/src/bch.h
@@ -13,6 +13,4 @@
 void bch_code_encode(uint64_t *codeword, const uint64_t *message);
 void bch_code_decode(uint64_t *message, uint64_t *vector);
 
-size_t compute_bch_poly(uint16_t *bch_poly, size_t *t, const uint16_t *exp, const uint16_t *log);
-
 #endif

