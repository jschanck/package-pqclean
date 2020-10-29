--- upstream/AVX_Implementation_KEM/pack_unpack.c
+++ upstream-patched/AVX_Implementation_KEM/pack_unpack.c
@@ -1,499 +1,224 @@
 #include "pack_unpack.h"
-
-void SABER_pack_3bit(uint8_t *bytes, uint16_t *data){
-
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;
-	
-	offset_byte=0;
-	for(j=0;j<SABER_N/8;j++){
-		offset_byte=3*j;
-		offset_data=8*j;
-		bytes[offset_byte + 0]= (data[offset_data + 0] & 0x7) | ( (data[offset_data + 1] & 0x7)<<3 ) | ((data[offset_data + 2] & 0x3)<<6);
-		bytes[offset_byte + 1]= ((data[offset_data + 2] >> 2 ) & 0x01)  | ( (data[offset_data + 3] & 0x7)<<1 ) | ( (data[offset_data + 4] & 0x7)<<4 ) | (((data[offset_data + 5]) & 0x01)<<7);
-		bytes[offset_byte + 2]= ((data[offset_data + 5] >> 1 ) & 0x03) | ( (data[offset_data + 6] & 0x7)<<2 ) | ( (data[offset_data + 7] & 0x7)<<5 );
-	}
-}
-
-void SABER_un_pack3bit(uint8_t *bytes, uint16_t *data){
-
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;	
-	
-	offset_byte=0;
-	for(j=0;j<SABER_N/8;j++){
-		offset_byte=3*j;
-		offset_data=8*j;
-		data[offset_data + 0] = (bytes[offset_byte+0])&0x07;
-		data[offset_data + 1] = ( (bytes[offset_byte+0])>>3 )&0x07;
-		data[offset_data + 2] = ( ( (bytes[offset_byte+0])>>6 )&0x03) | ( ( (bytes[offset_byte+1])&0x01)<<2 );
-		data[offset_data + 3] = ( (bytes[offset_byte+1])>>1 )&0x07;
-		data[offset_data + 4] = ( (bytes[offset_byte+1])>>4 )&0x07;
-		data[offset_data + 5] = ( ( (bytes[offset_byte+1])>>7 )&0x01) | ( ( (bytes[offset_byte+2])&0x03)<<1 );
-		data[offset_data + 6] = ( (bytes[offset_byte+2]>>2)&0x07 );
-		data[offset_data + 7] = ( (bytes[offset_byte+2]>>5)&0x07 );
-	}
-
-}
-
-void SABER_pack_4bit(uint8_t *bytes, uint16_t *data){
-
-	uint32_t j;
-	uint32_t offset_data=0;
-	
-	for(j=0;j<SABER_N/2;j++)
+#include "poly.h"
+#include "SABER_params.h"
+#include <string.h>
+
+void POLT2BS(uint8_t bytes[SABER_SCALEBYTES_KEM], const poly *data)
+{
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
+#if SABER_ET == 3
+	for (j = 0; j < SABER_N / 8; j++)
 	{
-		offset_data=2*j;
-		bytes[j]= (data[offset_data] & 0x0f) | ( (data[offset_data + 1] & 0x0f)<<4 );
+		out[0] = (in[0] & 0x7) | ((in[1] & 0x7) << 3) | (in[2] << 6);
+		out[1] = ((in[2] >> 2) & 0x01) | ((in[3] & 0x7) << 1) | ((in[4] & 0x7) << 4) | (in[5] << 7);
+		out[2] = ((in[5] >> 1) & 0x03) | ((in[6] & 0x7) << 2) | (in[7] << 5);
+		in += 8;
+		out += 3;
 	}
-}
-
-void SABER_un_pack4bit(const unsigned char *bytes, uint16_t *Mask_ar){
-
-	uint32_t j;
-	uint32_t offset_data=0;
-	
-	for(j=0;j<SABER_N/2;j++)
+#elif SABER_ET == 4
+	for (j = 0; j < SABER_N / 2; j++)
 	{
-		offset_data=2*j;
-		Mask_ar[offset_data] = bytes[j] & 0x0f;
-		Mask_ar[offset_data+1] = (bytes[j]>>4) & 0x0f;
-	}
-}
-
-void SABER_pack_6bit(uint8_t *bytes, uint16_t *data){
-
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;
-	
-	offset_byte=0;
-	for(j=0;j<SABER_N/4;j++){
-		offset_byte=3*j;
-		offset_data=4*j;
-		bytes[offset_byte + 0]= (data[offset_data + 0]&0x3f) | ((data[offset_data+1]&0x03)<<6);
- 		bytes[offset_byte + 1]= ((data[offset_data+1]>>2)&0x0f) | ((data[offset_data+2]&0x0f)<<4);
- 		bytes[offset_byte + 2]= ((data[offset_data+2]>>4)&0x03) | ((data[offset_data+3]&0x3f)<<2);
-	}
-}
-
-
-void SABER_un_pack6bit(const unsigned char *bytes, uint16_t *data){
-
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;	
-	
-	offset_byte=0;
-	for(j=0;j<SABER_N/4;j++){
-		offset_byte=3*j;
-		offset_data=4*j;
-		data[offset_data + 0] = bytes[offset_byte+0]&0x3f;
-		data[offset_data + 1] = ((bytes[offset_byte+0]>>6)&0x03) |  ((bytes[offset_byte+1]&0x0f)<<2)  ;
-		data[offset_data + 2] = ((bytes[offset_byte+1]&0xff)>>4) | ((bytes[offset_byte+2]&0x03)<<4) ;
-		data[offset_data + 3] = ((bytes[offset_byte+2]&0xff)>>2);
+		out[0] = (in[0] & 0x0f) | (in[1] << 4);
+		in += 2;
+		out += 1;
 	}
-
-}
-
-void SABER_pack10bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*10)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+5*j;
-			offset_data=4*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x03 ) | ((data[i][ offset_data + 1 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>6) & 0x0f ) | ( (data[i][ offset_data + 2 ] &0x0f) << 4);
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>4) & 0x3f ) | ((data[i][ offset_data + 3 ] & 0x03) << 6);
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 3 ] >>2) & 0xff );
-		}
+#elif SABER_ET == 6
+	for (j = 0; j < SABER_N / 4; j++)
+	{
+		out[0] = (in[0] & 0x3f) | (in[1] << 6);
+		out[1] = ((in[1] >> 2) & 0x0f) | (in[2] << 4);
+		out[2] = ((in[2] >> 4) & 0x03) | (in[3] << 2);
+		in += 4;
+		out += 3;
+	}
+#else
+#error "Unsupported SABER parameter."
+#endif
+}
+
+void BS2POLT(poly *data, const uint8_t bytes[SABER_SCALEBYTES_KEM])
+{
+	/* This function does not reduce its output mod T */
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
+#if SABER_ET == 3
+	for (j = 0; j < SABER_N / 8; j++)
+	{
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
-}
-
-void POLVECp2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*10)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+5*j;
-			offset_data=4*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x03 ) | ((data[i][ offset_data + 1 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>6) & 0x0f ) | ( (data[i][ offset_data + 2 ] &0x0f) << 4);
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>4) & 0x3f ) | ((data[i][ offset_data + 3 ] & 0x03) << 6);
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 3 ] >>2) & 0xff );
-		}
+#elif SABER_ET == 4
+	for (j = 0; j < SABER_N / 2; j++)
+	{
+		out[0] = in[0];
+		out[1] = in[0] >> 4;
+		in += 1;
+		out += 2;
 	}
-}
-
-void POLVECq2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*13)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+13*j;
-			offset_data=8*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x1f ) | ((data[i][ offset_data + 1 ] & 0x07) << 5);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>3) & 0xff );
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>11) & 0x03 ) | ((data[i][ offset_data + 2 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>6) & 0x7f ) | ( (data[i][ offset_data + 3 ] & 0x01) << 7 );
-
-			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>1) & 0xff );
-
-			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>9) & 0x0f ) | ( (data[i][ offset_data + 4 ] & 0x0f) << 4 );
-
-			bytes[offset_byte + 7]= ( (data[i][ offset_data + 4] >>4) & 0xff );
-
-			bytes[offset_byte + 8]= ( (data[i][ offset_data + 4 ] >>12) & 0x01 ) | ( (data[i][ offset_data + 5 ] & 0x7f) << 1 );
-
-			bytes[offset_byte + 9]= ( (data[i][ offset_data + 5 ] >>7) & 0x3f ) | ( (data[i][ offset_data + 6 ] & 0x03) << 6 );
-
-			bytes[offset_byte + 10]= ( (data[i][ offset_data + 6 ] >>2) & 0xff );
-
-			bytes[offset_byte + 11]= ( (data[i][ offset_data + 6 ] >>10) & 0x07 ) | ( (data[i][ offset_data + 7 ] & 0x1f) << 3 );
-
-			bytes[offset_byte + 12]= ( (data[i][ offset_data + 7 ] >>5) & 0xff );
-
-		}
+#elif SABER_ET == 6
+	for (j = 0; j < SABER_N / 4; j++)
+	{
+		out[0] = in[0];
+		out[1] = (in[0] >> 6) | (in[1] << 2);
+		out[2] = (in[1] >> 4) | (in[2] << 4);
+		out[3] = (in[2] >> 2);
+		in += 3;
+		out += 4;
+	}
+#else
+#error "Unsupported SABER parameter."
+#endif
+}
+
+static void POLq2BS(uint8_t bytes[SABER_POLYBYTES], const poly *data)
+{
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
+	for (j = 0; j < SABER_N / 8; j++)
+	{
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
-
-
 }
 
-void BS2POLVECp(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*10)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+5*j;
-			offset_data=4*j;
-			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x03)<<8);
-			data[i][offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 2 ] & 0x0f)<<6);		
-			data[i][offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 3 ] & 0x3f)<<4);
-			data[i][offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 4 ] & 0xff)<<2);		
-
-		}
+static void BS2POLq(poly *data, const uint8_t bytes[SABER_POLYBYTES])
+{
+	/* This function does not reduce its output mod Q */
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
+	for (j = 0; j < SABER_N / 8; j++)
+	{
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
 
-void BS2POLVECq(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*13)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+13*j;
-			offset_data=8*j;
-			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
-			data[i][offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
-			data[i][offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
-			data[i][offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
-			data[i][offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
-			data[i][offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
-			data[i][offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
-			data[i][offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
-		}
+static void POLp2BS(uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], const poly *data)
+{
+	size_t j;
+	const uint16_t *in = data->coeffs;
+	uint8_t *out = bytes;
+	for (j = 0; j < SABER_N / 4; j++)
+	{
+		out[0] = in[0];
+		out[1] = ((in[0] >> 8) & 0x03) | (in[1] << 2);
+		out[2] = ((in[1] >> 6) & 0x0f) | (in[2] << 4);
+		out[3] = ((in[2] >> 4) & 0x3f) | (in[3] << 6);
+		out[4] = in[3] >> 2;
+		in += 4;
+		out += 5;
 	}
-
-
 }
 
-
-
-void SABER_un_pack10bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*10)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+5*j;
-			offset_data=4*j;
-			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x03)<<8);
-			data[i][offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 2 ] & 0x0f)<<6);		
-			data[i][offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 3 ] & 0x3f)<<4);
-			data[i][offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 4 ] & 0xff)<<2);		
-
-		}
+static void BS2POLp(poly *data, const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES])
+{
+	size_t j;
+	const uint8_t *in = bytes;
+	uint16_t *out = data->coeffs;
+	for (j = 0; j < SABER_N / 4; j++)
+	{
+		out[0] = in[0] | (in[1] << 8);
+		out[1] = (in[1] >> 2) | (in[2] << 6);
+		out[2] = (in[2] >> 4) | (in[3] << 4);
+		out[3] = (in[3] >> 6) | (in[4] << 2);
+		in += 5;
+		out += 4;
 	}
-
-
 }
 
-
-void SABER_pack13bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*13)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+13*j;
-			offset_data=8*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x1f ) | ((data[i][ offset_data + 1 ] & 0x07) << 5);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>3) & 0xff );
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>11) & 0x03 ) | ((data[i][ offset_data + 2 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>6) & 0x7f ) | ( (data[i][ offset_data + 3 ] & 0x01) << 7 );
-
-			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>1) & 0xff );
-
-			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>9) & 0x0f ) | ( (data[i][ offset_data + 4 ] & 0x0f) << 4 );
-
-			bytes[offset_byte + 7]= ( (data[i][ offset_data + 4] >>4) & 0xff );
-
-			bytes[offset_byte + 8]= ( (data[i][ offset_data + 4 ] >>12) & 0x01 ) | ( (data[i][ offset_data + 5 ] & 0x7f) << 1 );
-
-			bytes[offset_byte + 9]= ( (data[i][ offset_data + 5 ] >>7) & 0x3f ) | ( (data[i][ offset_data + 6 ] & 0x03) << 6 );
-
-			bytes[offset_byte + 10]= ( (data[i][ offset_data + 6 ] >>2) & 0xff );
-
-			bytes[offset_byte + 11]= ( (data[i][ offset_data + 6 ] >>10) & 0x07 ) | ( (data[i][ offset_data + 7 ] & 0x1f) << 3 );
-
-			bytes[offset_byte + 12]= ( (data[i][ offset_data + 7 ] >>5) & 0xff );
-
-		}
+void POLVECq2BS(uint8_t bytes[SABER_POLYVECBYTES], const poly data[SABER_L])
+{
+	size_t i;
+	for (i = 0; i < SABER_L; i++)
+	{
+		POLq2BS(bytes + i * SABER_POLYBYTES, &data[i]);
 	}
-
-
 }
 
-void SABER_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*13)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+13*j;
-			offset_data=8*j;
-			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
-			data[i][offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
-			data[i][offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
-			data[i][offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
-			data[i][offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
-			data[i][offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
-			data[i][offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
-			data[i][offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
-		}
+void BS2POLVECq(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECBYTES])
+{
+	size_t i;
+	for (i = 0; i < SABER_L; i++)
+	{
+		BS2POLq(&data[i], bytes + i * SABER_POLYBYTES);
 	}
-
-
-}
-
-void SABER_poly_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_N]){
-	
-	uint32_t j;
-	uint32_t offset_data=0,offset_byte=0;	
-	
-	offset_byte=0;
-	//for(i=0;i<SABER_K;i++){
-		//i=0;
-		//offset_byte1=i*(SABER_N*13)/8;
-		for(j=0;j<SABER_N/8;j++){
-			//offset_byte=offset_byte1+13*j;
-			offset_byte=13*j;
-			offset_data=8*j;
-			data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
-			data[offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
-			data[offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
-			data[offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
-			data[offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
-			data[offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
-			data[offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
-			data[offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
-		}
-	//}
-
-
 }
 
-
-void SABER_pack11bit(uint8_t *bytes,  uint16_t data[SABER_K][SABER_N]){
-/*This function packs 11 bit data stream into 8 bits of data.
-*/
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*11)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+11*j;
-			offset_data=8*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x07 ) | ((data[i][ offset_data + 1 ] & 0x1f) << 3);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>5) & 0x3f ) | ((data[i][ offset_data + 2 ] & 0x03) << 6);
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>2) & 0xff );
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>10) & 0x01 ) | ((data[i][ offset_data + 3 ] & 0x7f) << 1);
-
-			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>7) & 0x0f ) | ((data[i][ offset_data + 4 ] & 0x0f) << 4);
-
-			bytes[offset_byte + 6]= ( (data[i][ offset_data + 4 ] >>4) & 0x7f ) | ((data[i][ offset_data + 5 ] & 0x01) << 7);
-
-			bytes[offset_byte + 7]= ( (data[i][ offset_data + 5 ] >>1) & 0xff );
-
-			bytes[offset_byte + 8]= ( (data[i][ offset_data + 5 ] >>9) & 0x03 ) | ((data[i][ offset_data + 6 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 9]= ( (data[i][ offset_data + 6 ] >>6) & 0x1f ) | ((data[i][ offset_data + 7 ] & 0x07) << 5);
-
-			bytes[offset_byte + 10]=( (data[i][ offset_data + 7 ] >>3) & 0xff );
-			
-		}
+void POLVECp2BS(uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], const poly data[SABER_L])
+{
+	size_t i;
+	for (i = 0; i < SABER_L; i++)
+	{
+		POLp2BS(bytes + i * SABER_POLYCOMPRESSEDBYTES, &data[i]);
 	}
-
 }
 
-void SABER_un_pack11bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
-
-
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*11)/8;
-		for(j=0;j<SABER_N/8;j++){
-			offset_byte=offset_byte1+11*j;
-			offset_data=8*j;
-
-			data[i][offset_data+ 0]=(bytes[offset_byte+0]) | ( (bytes[offset_byte + 1] & 0x07) << 8 );
-
-			data[i][offset_data+ 1]= ( (bytes[offset_byte+1] >>3)&0x1f) | ( (bytes[offset_byte + 2] & 0x3f) << 5 );
-
-			data[i][offset_data+ 2]= ( (bytes[offset_byte+2] >>6)&0x03) | ( (bytes[offset_byte + 3] & 0xff) << 2 ) | ( (bytes[offset_byte + 4] & 0x01) << 10 );
-
-			data[i][offset_data+ 3]= ( (bytes[offset_byte+4] >>1)&0x7f) | ( (bytes[offset_byte + 5] & 0x0f) << 7 );
-
-			data[i][offset_data+ 4]= ( (bytes[offset_byte+5] >>4)&0x0f) | ( (bytes[offset_byte + 6] & 0x7f) << 4 );
-
-			data[i][offset_data+ 5]= ( (bytes[offset_byte+6] >>7)&0x01) | ( (bytes[offset_byte + 7] & 0xff) << 1 ) | ( (bytes[offset_byte + 8] & 0x03) << 9 );
-
-			data[i][offset_data+ 6]= ( (bytes[offset_byte+8] >>2)&0x3f) | ( (bytes[offset_byte + 9] & 0x1f) << 6 );
-
-			data[i][offset_data+ 7]= ( (bytes[offset_byte+9] >>5)&0x07) | ( (bytes[offset_byte + 10] & 0xff) << 3 );
-		}
+void BS2POLVECp(poly data[SABER_L], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES])
+{
+	size_t i;
+	for (i = 0; i < SABER_L; i++)
+	{
+		BS2POLp(&data[i], bytes + i * SABER_POLYCOMPRESSEDBYTES);
 	}
-
-
 }
 
-void SABER_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*14)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+7*j;
-			offset_data=4*j;
-			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));
-
-			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x3f ) | ((data[i][ offset_data + 1 ] & 0x03) << 6);
-
-			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>2) & 0xff );
-
-			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>10) & 0x0f ) | ((data[i][ offset_data + 2 ] & 0x0f) << 4);
-
-			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>4) & 0xff );
-
-			bytes[offset_byte + 5]= ( (data[i][ offset_data + 2 ] >>12) & 0x03 ) | ((data[i][ offset_data + 3 ] & 0x3f) << 2);
-
-			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>6) & 0xff );
+void BS2POLmsg(poly *data, const uint8_t bytes[SABER_KEYBYTES])
+{
+	size_t i, j;
+	for (j = 0; j < SABER_KEYBYTES; j++)
+	{
+		for (i = 0; i < 8; i++)
+		{
+			data->coeffs[j * 8 + i] = ((bytes[j] >> i) & 0x01);
 		}
 	}
-
-
 }
 
+void POLmsg2BS(uint8_t bytes[SABER_KEYBYTES], const poly *data)
+{
+	size_t i, j;
+	memset(bytes, 0, SABER_KEYBYTES);
 
-void SABER_un_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
-	
-	uint32_t i,j;
-	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
-	
-	offset_byte=0;
-	for(i=0;i<SABER_K;i++){
-		offset_byte1=i*(SABER_N*14)/8;
-		for(j=0;j<SABER_N/4;j++){
-			offset_byte=offset_byte1+7*j;
-			offset_data=4*j;
-			data[i][offset_data+ 0]=(bytes[offset_byte+0]&0xff) | ( (bytes[offset_byte + 1] & 0x3f) << 8 );
-
-			data[i][offset_data+ 1]= ( (bytes[offset_byte+1] >>6)&0x03) | ((bytes[offset_byte+2]&0xff)<<2 ) | ( (bytes[offset_byte + 3] & 0x0f) << 10 );
-
-			data[i][offset_data+ 2]= ( (bytes[offset_byte+3] >>4)&0x0f) | ( (bytes[offset_byte + 4] ) << 4 ) | ( (bytes[offset_byte + 5] & 0x03) << 12 );
-
-			data[i][offset_data+ 3]= ( (bytes[offset_byte+5] >>2)&0x3f) | ( (bytes[offset_byte + 6] ) << 6 );
+	for (j = 0; j < SABER_KEYBYTES; j++)
+	{
+		for (i = 0; i < 8; i++)
+		{
+			bytes[j] = bytes[j] | ((data->coeffs[j * 8 + i] & 0x01) << i);
 		}
 	}
-
-
 }
 
-void POLVEC2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){
-
-	if(modulus==1024)
-		POLVECp2BS(bytes, data);
-	else if(modulus==8192)
-		POLVECq2BS(bytes, data);
-}
-
-void BS2POLVEC(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){
-
-	if(modulus==1024)
-		BS2POLVECp(bytes, data);
-	else if(modulus==8192)
-		BS2POLVECq(bytes, data);
-
-}
-
-
-

