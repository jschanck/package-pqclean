--- hqc-2020-05-29/Optimized_Implementation/hqc-rmrs-192/src/reed_muller.h
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-rmrs-192/src/reed_muller.h
@@ -10,7 +10,7 @@
 #include <stddef.h>
 #include <stdint.h>
 
-void reed_muller_encode(uint64_t* cdw, const uint64_t* msg);
-void reed_muller_decode(uint64_t* msg, const uint64_t* cdw);
+void reed_muller_encode(uint8_t* cdw, const uint8_t* msg);
+void reed_muller_decode(uint8_t* msg, const uint8_t* cdw);
 
 #endif

