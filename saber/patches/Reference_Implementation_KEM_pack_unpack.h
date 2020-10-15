--- upstream/Reference_Implementation_KEM/pack_unpack.h
+++ upstream-patched/Reference_Implementation_KEM/pack_unpack.h
@@ -6,15 +6,15 @@
 #include "SABER_params.h"
 
 void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N]);
-void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N]);
+void BS2POLT(uint16_t data[SABER_N], const uint8_t bytes[SABER_SCALEBYTES_KEM]);
 
 void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[SABER_L][SABER_N]);
 void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[SABER_L][SABER_N]);
 
-void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[SABER_L][SABER_N]);
-void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[SABER_L][SABER_N]);
+void BS2POLVECq(uint16_t data[SABER_L][SABER_N], const uint8_t bytes[SABER_POLYVECBYTES]);
+void BS2POLVECp(uint16_t data[SABER_L][SABER_N], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES]);
 
-void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[SABER_N]);
+void BS2POLmsg(uint16_t data[SABER_N], const uint8_t bytes[SABER_KEYBYTES]);
 void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[SABER_N]);
 
 #endif

