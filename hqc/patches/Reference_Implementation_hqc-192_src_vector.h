--- hqc-2020-05-29/Reference_Implementation/hqc-192/src/vector.h
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-192/src/vector.h
@@ -18,7 +18,4 @@
 int vect_compare(const uint64_t *v1, const uint64_t *v2, uint32_t size);
 void vect_resize(uint64_t *o, uint32_t size_o, const uint64_t *v, uint32_t size_v);
 
-void vect_print(const uint64_t *v, const uint32_t size);
-void vect_print_sparse(const uint32_t *v, const uint16_t weight);
-
 #endif

