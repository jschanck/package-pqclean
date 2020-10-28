--- upstream/AVX_Implementation_KEM/pack_unpack.h
+++ upstream-patched/AVX_Implementation_KEM/pack_unpack.h
@@ -3,41 +3,19 @@
 
 #include <stdio.h>
 #include <stdint.h>
+#include "poly.h"
 #include "SABER_params.h"
 
-void SABER_pack11bit(uint8_t *pk,  uint16_t skpv[SABER_K][SABER_N]);
+void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const poly *data);
+void BS2POLT(poly *data, const uint8_t bytes[SABER_SCALEBYTES_KEM]);
 
-void SABER_un_pack11bit(uint8_t *pk, uint16_t data[SABER_K][SABER_N]);
+void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const poly data[SABER_L]);
+void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const poly data[SABER_L]);
 
-void SABER_pack14bit(uint8_t *sk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_un_pack14bit(uint8_t *sk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_pack_3bit(uint8_t *bytes, uint16_t *data);
-
-void SABER_un_pack3bit(uint8_t *bytes, uint16_t *data);
-
-void SABER_pack10bit(uint8_t *pk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_un_pack10bit(const unsigned char *pk, uint16_t data[SABER_K][SABER_N]);
-
-void SABER_pack13bit(uint8_t *sk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_poly_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_N]);
-
-void SABER_un_pack13bit(const unsigned char *sk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_pack_4bit(uint8_t *bytes, uint16_t *data);
-
-void SABER_un_pack4bit(const unsigned char *bytes, uint16_t *Mask_ar);
-
-void SABER_pack_6bit(uint8_t *bytes, uint16_t *data);
-
-void SABER_un_pack6bit(const unsigned char *bytes, uint16_t *data);
-
-void POLVEC2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus);
-
-void BS2POLVEC(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus);
+void BS2POLVECq(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECBYTES]);
+void BS2POLVECp(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES]);
 
+void BS2POLmsg(poly *data, const uint8_t bytes[SABER_KEYBYTES]);
+void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const poly *data);
 
 #endif

