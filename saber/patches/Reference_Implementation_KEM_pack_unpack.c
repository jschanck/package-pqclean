--- upstream/Reference_Implementation_KEM/pack_unpack.c
+++ upstream-patched/Reference_Implementation_KEM/pack_unpack.c
@@ -1,199 +1,214 @@
 #include "pack_unpack.h"
-#include "api.h"
+#include "poly.h"
+#include "SABER_params.h"
 #include <string.h>
 
-void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const uint16_t data[SABER_N])
+void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const poly *data)
 {
-	size_t j, offset_byte, offset_data;
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
 #if SABER_ET == 3
 	for (j = 0; j < SABER_N / 8; j++)
 	{
-		offset_byte = 3 * j;
-		offset_data = 8 * j;
-		bytes[offset_byte + 0] = (data[offset_data + 0] & 0x7) | ((data[offset_data + 1] & 0x7) << 3) | ((data[offset_data + 2] & 0x3) << 6);
-		bytes[offset_byte + 1] = ((data[offset_data + 2] >> 2) & 0x01) | ((data[offset_data + 3] & 0x7) << 1) | ((data[offset_data + 4] & 0x7) << 4) | (((data[offset_data + 5]) & 0x01) << 7);
-		bytes[offset_byte + 2] = ((data[offset_data + 5] >> 1) & 0x03) | ((data[offset_data + 6] & 0x7) << 2) | ((data[offset_data + 7] & 0x7) << 5);
+		out[0] = (in[0] & 0x7) | ((in[1] & 0x7) << 3) | (in[2] << 6);
+		out[1] = ((in[2] >> 2) & 0x01) | ((in[3] & 0x7) << 1) | ((in[4] & 0x7) << 4) | (in[5] << 7);
+		out[2] = ((in[5] >> 1) & 0x03) | ((in[6] & 0x7) << 2) | (in[7] << 5);
+		in += 8;
+		out += 3;
 	}
 #elif SABER_ET == 4
 	for (j = 0; j < SABER_N / 2; j++)
 	{
-		offset_byte = j;
-		offset_data = 2 * j;
-		bytes[offset_byte] = (data[offset_data] & 0x0f) | ((data[offset_data + 1] & 0x0f) << 4);
+		out[0] = (in[0] & 0x0f) | (in[1] << 4);
+		in += 2;
+		out += 1;
 	}
 #elif SABER_ET == 6
 	for (j = 0; j < SABER_N / 4; j++)
 	{
-		offset_byte = 3 * j;
-		offset_data = 4 * j;
-		bytes[offset_byte + 0] = (data[offset_data + 0] & 0x3f) | ((data[offset_data + 1] & 0x03) << 6);
-		bytes[offset_byte + 1] = ((data[offset_data + 1] >> 2) & 0x0f) | ((data[offset_data + 2] & 0x0f) << 4);
-		bytes[offset_byte + 2] = ((data[offset_data + 2] >> 4) & 0x03) | ((data[offset_data + 3] & 0x3f) << 2);
+		out[0] = (in[0] & 0x3f) | (in[1] << 6);
+		out[1] = ((in[1] >> 2) & 0x0f) | (in[2] << 4);
+		out[2] = ((in[2] >> 4) & 0x03) | (in[3] << 2);
+		in += 4;
+		out += 3;
 	}
 #else
 #error "Unsupported SABER parameter."
 #endif
 }
 
-void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N])
+void BS2POLT(poly *data, const uint8_t bytes[SABER_SCALEBYTES_KEM])
 {
-	size_t j, offset_byte, offset_data;
+	/* This function does not reduce its output mod T */
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
 #if SABER_ET == 3
 	for (j = 0; j < SABER_N / 8; j++)
 	{
-		offset_byte = 3 * j;
-		offset_data = 8 * j;
-		data[offset_data + 0] = (bytes[offset_byte + 0]) & 0x07;
-		data[offset_data + 1] = ((bytes[offset_byte + 0]) >> 3) & 0x07;
-		data[offset_data + 2] = (((bytes[offset_byte + 0]) >> 6) & 0x03) | (((bytes[offset_byte + 1]) & 0x01) << 2);
-		data[offset_data + 3] = ((bytes[offset_byte + 1]) >> 1) & 0x07;
-		data[offset_data + 4] = ((bytes[offset_byte + 1]) >> 4) & 0x07;
-		data[offset_data + 5] = (((bytes[offset_byte + 1]) >> 7) & 0x01) | (((bytes[offset_byte + 2]) & 0x03) << 1);
-		data[offset_data + 6] = ((bytes[offset_byte + 2] >> 2) & 0x07);
-		data[offset_data + 7] = ((bytes[offset_byte + 2] >> 5) & 0x07);
+		out[0] = in[0];
+		out[1] = in[0] >> 3;
+		out[2] = (in[0] >> 6) | (in[1] << 2);
+		out[3] = in[1] >> 1;
+		out[4] = in[1] >> 4;
+		out[5] = (in[1] >> 7) | (in[2] << 1);
+		out[6] = in[2] >> 2;
+		out[7] = in[2] >> 5;
+		in += 3;
+		out += 8;
 	}
 #elif SABER_ET == 4
 	for (j = 0; j < SABER_N / 2; j++)
 	{
-		offset_byte = j;
-		offset_data = 2 * j;
-		data[offset_data] = bytes[offset_byte] & 0x0f;
-		data[offset_data + 1] = (bytes[offset_byte] >> 4) & 0x0f;
+		out[0] = in[0];
+		out[1] = in[0] >> 4;
+		in += 1;
+		out += 2;
 	}
 #elif SABER_ET == 6
 	for (j = 0; j < SABER_N / 4; j++)
 	{
-		offset_byte = 3 * j;
-		offset_data = 4 * j;
-		data[offset_data + 0] = bytes[offset_byte + 0] & 0x3f;
-		data[offset_data + 1] = ((bytes[offset_byte + 0] >> 6) & 0x03) | ((bytes[offset_byte + 1] & 0x0f) << 2);
-		data[offset_data + 2] = ((bytes[offset_byte + 1] & 0xff) >> 4) | ((bytes[offset_byte + 2] & 0x03) << 4);
-		data[offset_data + 3] = ((bytes[offset_byte + 2] & 0xff) >> 2);
+		out[0] = in[0];
+		out[1] = (in[0] >> 6) | (in[1] << 2);
+		out[2] = (in[1] >> 4) | (in[2] << 4);
+		out[3] = (in[2] >> 2);
+		in += 3;
+		out += 4;
 	}
 #else
 #error "Unsupported SABER parameter."
 #endif
 }
 
-static void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const uint16_t data[SABER_N])
+static void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const poly *data)
 {
-	size_t j, offset_byte, offset_data;
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
 	for (j = 0; j < SABER_N / 8; j++)
 	{
-		offset_byte = 13 * j;
-		offset_data = 8 * j;
-		bytes[offset_byte + 0] = (data[offset_data + 0] & (0xff));
-		bytes[offset_byte + 1] = ((data[offset_data + 0] >> 8) & 0x1f) | ((data[offset_data + 1] & 0x07) << 5);
-		bytes[offset_byte + 2] = ((data[offset_data + 1] >> 3) & 0xff);
-		bytes[offset_byte + 3] = ((data[offset_data + 1] >> 11) & 0x03) | ((data[offset_data + 2] & 0x3f) << 2);
-		bytes[offset_byte + 4] = ((data[offset_data + 2] >> 6) & 0x7f) | ((data[offset_data + 3] & 0x01) << 7);
-		bytes[offset_byte + 5] = ((data[offset_data + 3] >> 1) & 0xff);
-		bytes[offset_byte + 6] = ((data[offset_data + 3] >> 9) & 0x0f) | ((data[offset_data + 4] & 0x0f) << 4);
-		bytes[offset_byte + 7] = ((data[offset_data + 4] >> 4) & 0xff);
-		bytes[offset_byte + 8] = ((data[offset_data + 4] >> 12) & 0x01) | ((data[offset_data + 5] & 0x7f) << 1);
-		bytes[offset_byte + 9] = ((data[offset_data + 5] >> 7) & 0x3f) | ((data[offset_data + 6] & 0x03) << 6);
-		bytes[offset_byte + 10] = ((data[offset_data + 6] >> 2) & 0xff);
-		bytes[offset_byte + 11] = ((data[offset_data + 6] >> 10) & 0x07) | ((data[offset_data + 7] & 0x1f) << 3);
-		bytes[offset_byte + 12] = ((data[offset_data + 7] >> 5) & 0xff);
+		out[0] = in[0];
+		out[1] = ((in[0] >> 8) & 0x1f) | (in[1] << 5);
+		out[2] = in[1] >> 3;
+		out[3] = ((in[1] >> 11) & 0x03) | (in[2] << 2);
+		out[4] = ((in[2] >> 6) & 0x7f) | (in[3] << 7);
+		out[5] = in[3] >> 1;
+		out[6] = ((in[3] >> 9) & 0x0f) | (in[4] << 4);
+		out[7] = in[4] >> 4;
+		out[8] = ((in[4] >> 12) & 0x01) | (in[5] << 1);
+		out[9] = ((in[5] >> 7) & 0x3f) | (in[6] << 6);
+		out[10] = in[6] >> 2;
+		out[11] = ((in[6] >> 10) & 0x07) | (in[7] << 3);
+		out[12] = in[7] >> 5;
+		in += 8;
+		out += 13;
 	}
 }
 
-static void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[SABER_N])
-{
-	size_t j, offset_byte, offset_data;
+static void BS2POLq(poly *data, const uint8_t bytes[SABER_POLYBYTES])
+{
+	/* This function does not reduce its output mod Q */
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
 	for (j = 0; j < SABER_N / 8; j++)
 	{
-		offset_byte = 13 * j;
-		offset_data = 8 * j;
-		data[offset_data + 0] = (bytes[offset_byte + 0] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f) << 8);
-		data[offset_data + 1] = (bytes[offset_byte + 1] >> 5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff) << 3) | ((bytes[offset_byte + 3] & 0x03) << 11);
-		data[offset_data + 2] = (bytes[offset_byte + 3] >> 2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f) << 6);
-		data[offset_data + 3] = (bytes[offset_byte + 4] >> 7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff) << 1) | ((bytes[offset_byte + 6] & 0x0f) << 9);
-		data[offset_data + 4] = (bytes[offset_byte + 6] >> 4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff) << 4) | ((bytes[offset_byte + 8] & 0x01) << 12);
-		data[offset_data + 5] = (bytes[offset_byte + 8] >> 1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f) << 7);
-		data[offset_data + 6] = (bytes[offset_byte + 9] >> 6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff) << 2) | ((bytes[offset_byte + 11] & 0x07) << 10);
-		data[offset_data + 7] = (bytes[offset_byte + 11] >> 3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff) << 5);
+		out[0] = (in[0]) | (in[1] << 8);
+		out[1] = (in[1] >> 5) | (in[2] << 3) | (in[3] << 11);
+		out[2] = (in[3] >> 2) | (in[4] << 6);
+		out[3] = (in[4] >> 7) | (in[5] << 1) | (in[6] << 9);
+		out[4] = (in[6] >> 4) | (in[7] << 4) | (in[8] << 12);
+		out[5] = (in[8] >> 1) | (in[9] << 7);
+		out[6] = (in[9] >> 6) | (in[10] << 2) | (in[11] << 10);
+		out[7] = (in[11] >> 3) | (in[12] << 5);
+		in += 13;
+		out += 8;
 	}
 }
 
-static void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const uint16_t data[SABER_N])
-{
-	size_t j, offset_byte, offset_data;
+static void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const poly *data)
+{
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
 	for (j = 0; j < SABER_N / 4; j++)
 	{
-		offset_byte = 5 * j;
-		offset_data = 4 * j;
-		bytes[offset_byte + 0] = (data[offset_data + 0] & (0xff));
-		bytes[offset_byte + 1] = ((data[offset_data + 0] >> 8) & 0x03) | ((data[offset_data + 1] & 0x3f) << 2);
-		bytes[offset_byte + 2] = ((data[offset_data + 1] >> 6) & 0x0f) | ((data[offset_data + 2] & 0x0f) << 4);
-		bytes[offset_byte + 3] = ((data[offset_data + 2] >> 4) & 0x3f) | ((data[offset_data + 3] & 0x03) << 6);
-		bytes[offset_byte + 4] = ((data[offset_data + 3] >> 2) & 0xff);
+		out[0] = in[0];
+		out[1] = ((in[0] >> 8) & 0x03) | (in[1] << 2);
+		out[2] = ((in[1] >> 6) & 0x0f) | (in[2] << 4);
+		out[3] = ((in[2] >> 4) & 0x3f) | (in[3] << 6);
+		out[4] = in[3] >> 2;
+		in += 4;
+		out += 5;
 	}
 }
 
-static void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[SABER_N])
+static void BS2POLp(poly *data, const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES])
 {
-	size_t j, offset_byte, offset_data;
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
 	for (j = 0; j < SABER_N / 4; j++)
 	{
-		offset_byte = 5 * j;
-		offset_data = 4 * j;
-		data[offset_data + 0] = (bytes[offset_byte + 0] & (0xff)) | ((bytes[offset_byte + 1] & 0x03) << 8);
-		data[offset_data + 1] = ((bytes[offset_byte + 1] >> 2) & (0x3f)) | ((bytes[offset_byte + 2] & 0x0f) << 6);
-		data[offset_data + 2] = ((bytes[offset_byte + 2] >> 4) & (0x0f)) | ((bytes[offset_byte + 3] & 0x3f) << 4);
-		data[offset_data + 3] = ((bytes[offset_byte + 3] >> 6) & (0x03)) | ((bytes[offset_byte + 4] & 0xff) << 2);
+		out[0] = in[0] | (in[1] << 8);
+		out[1] = (in[1] >> 2) | (in[2] << 6);
+		out[2] = (in[2] >> 4) | (in[3] << 4);
+		out[3] = (in[3] >> 6) | (in[4] << 2);
+		in += 5;
+		out += 4;
 	}
 }
 
-void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const uint16_t data[SABER_L][SABER_N])
+void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const poly data[SABER_L])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		POLq2BS(bytes + i * SABER_POLYBYTES, data[i]);
+		POLq2BS(bytes + i * SABER_POLYBYTES, &data[i]);
 	}
 }
 
-void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[SABER_L][SABER_N])
+void BS2POLVECq(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECBYTES])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLq(bytes + i * SABER_POLYBYTES, data[i]);
+		BS2POLq(&data[i], bytes + i * SABER_POLYBYTES);
 	}
 }
 
-void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const uint16_t data[SABER_L][SABER_N])
+void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const poly data[SABER_L])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		POLp2BS(bytes + i * (SABER_EP * SABER_N / 8), data[i]);
+		POLp2BS(bytes + i * SABER_POLYCOMPRESSEDBYTES, &data[i]);
 	}
 }
 
-void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[SABER_L][SABER_N])
+void BS2POLVECp(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLp(bytes + i * (SABER_EP * SABER_N / 8), data[i]);
+		BS2POLp(&data[i], bytes + i * SABER_POLYCOMPRESSEDBYTES);
 	}
 }
 
-void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[SABER_N])
+void BS2POLmsg(poly *data, const uint8_t bytes[SABER_KEYBYTES])
 {
 	size_t i, j;
 	for (j = 0; j < SABER_KEYBYTES; j++)
 	{
 		for (i = 0; i < 8; i++)
 		{
-			data[j * 8 + i] = ((bytes[j] >> i) & 0x01);
+			data->coeffs[j * 8 + i] = ((bytes[j] >> i) & 0x01);
 		}
 	}
 }
 
-void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const uint16_t data[SABER_N])
+void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const poly *data)
 {
 	size_t i, j;
 	memset(bytes, 0, SABER_KEYBYTES);
@@ -202,7 +217,8 @@
 	{
 		for (i = 0; i < 8; i++)
 		{
-			bytes[j] = bytes[j] | ((data[j * 8 + i] & 0x01) << i);
+			bytes[j] = bytes[j] | ((data->coeffs[j * 8 + i] & 0x01) << i);
 		}
 	}
 }
+

