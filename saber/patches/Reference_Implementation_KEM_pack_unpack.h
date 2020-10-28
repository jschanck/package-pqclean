--- upstream/Reference_Implementation_KEM/pack_unpack.h
+++ upstream-patched/Reference_Implementation_KEM/pack_unpack.h
@@ -3,18 +3,19 @@
 
 #include <stdio.h>
 #include <stdint.h>
+#include "poly.h"
 #include "SABER_params.h"
 
-void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N]);
-void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N]);
+void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const poly *data);
+void BS2POLT(poly *data, const uint8_t bytes[SABER_SCALEBYTES_KEM]);
 
-void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[SABER_L][SABER_N]);
-void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[SABER_L][SABER_N]);
+void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const poly data[SABER_L]);
+void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const poly data[SABER_L]);
 
-void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[SABER_L][SABER_N]);
-void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[SABER_L][SABER_N]);
+void BS2POLVECq(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECBYTES]);
+void BS2POLVECp(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES]);
 
-void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[SABER_N]);
-void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[SABER_N]);
+void BS2POLmsg(poly *data, const uint8_t bytes[SABER_KEYBYTES]);
+void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const poly *data);
 
 #endif

