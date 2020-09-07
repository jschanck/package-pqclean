--- hqc-2020-05-29/Reference_Implementation/hqc-rmrs-128/src/reed_solomon.h
+++ hqc-2020-05-29-patched/Reference_Implementation/hqc-rmrs-128/src/reed_solomon.h
@@ -13,6 +13,4 @@
 void reed_solomon_encode(uint64_t* cdw, const uint64_t* msg);
 void reed_solomon_decode(uint64_t* msg, uint64_t* cdw);
 
-void compute_generator_poly(uint16_t* poly);
-
 #endif

