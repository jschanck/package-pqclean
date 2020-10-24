--- upstream/Reference_Implementation/hqc-rmrs-128/src/reed_muller.h
+++ upstream-patched/Reference_Implementation/hqc-rmrs-128/src/reed_muller.h
@@ -10,7 +10,7 @@
 #include <stddef.h>
 #include <stdint.h>
 
-void reed_muller_encode(uint64_t* cdw, const uint64_t* msg);
-void reed_muller_decode(uint64_t* msg, const uint64_t* cdw);
+void reed_muller_encode(uint8_t* cdw, const uint8_t* msg);
+void reed_muller_decode(uint8_t* msg, const uint8_t* cdw);
 
 #endif

