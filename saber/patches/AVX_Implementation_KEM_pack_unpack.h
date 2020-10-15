--- upstream/AVX_Implementation_KEM/pack_unpack.h
+++ upstream-patched/AVX_Implementation_KEM/pack_unpack.h
@@ -5,39 +5,31 @@
 #include <stdint.h>
 #include "SABER_params.h"
 
-void SABER_pack11bit(uint8_t *pk,  uint16_t skpv[SABER_K][SABER_N]);
-
-void SABER_un_pack11bit(uint8_t *pk, uint16_t data[SABER_K][SABER_N]);
-
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
-
+void BS2POLq(uint16_t data[SABER_N], const uint8_t *bytes);
+void BS2POLVEC(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes, uint16_t modulus);
+void BS2POLVECq(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
+void BS2POLVECp(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
+
+void POLVEC2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N], uint16_t modulus);
+void POLVECq2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+void POLVECp2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+
+void SABER_pack_3bit(uint8_t *bytes, const uint16_t *data);
+void SABER_pack_4bit(uint8_t *bytes, const uint16_t *data);
+void SABER_pack_6bit(uint8_t *bytes, const uint16_t *data);
+void SABER_pack10bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+void SABER_pack11bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+void SABER_pack13bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+void SABER_pack14bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]);
+
+void SABER_poly_un_pack13bit(uint16_t data[SABER_N], const uint8_t *bytes);
+
+void SABER_un_pack3bit(uint16_t *data, const uint8_t *bytes);
+void SABER_un_pack4bit(uint16_t *data, const uint8_t *bytes);
+void SABER_un_pack6bit(uint16_t *data, const uint8_t *bytes);
+void SABER_un_pack10bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
+void SABER_un_pack11bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
+void SABER_un_pack13bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
+void SABER_un_pack14bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes);
 
 #endif

