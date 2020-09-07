--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-128/src/vector.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-128/src/vector.h
@@ -17,7 +17,4 @@
 int vect_compare(const uint64_t *v1, const uint64_t *v2, uint32_t size);
 void vect_resize(uint64_t *o, uint32_t size_o, const uint64_t *v, uint32_t size_v);
 
-void vect_print(const uint64_t *v, const uint32_t size);
-void vect_print_sparse(const uint32_t *v, const uint16_t weight);
-
 #endif

