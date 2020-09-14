--- hqc-2020-05-29/Optimized_Implementation/hqc-256/src/vector.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-256/src/vector.h
@@ -14,10 +14,7 @@
 void vect_set_random_from_randombytes(uint64_t *v);
 
 void vect_add(uint64_t *o, const uint64_t *v1, const uint64_t *v2, uint32_t size);
-int vect_compare(const uint64_t *v1, const uint64_t *v2, uint32_t size);
+uint8_t vect_compare(const uint8_t *v1, const uint8_t *v2, uint32_t size);
 void vect_resize(uint64_t *o, uint32_t size_o, const uint64_t *v, uint32_t size_v);
 
-void vect_print(const uint64_t *v, const uint32_t size);
-void vect_print_sparse(const uint32_t *v, const uint16_t weight);
-
 #endif

