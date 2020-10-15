--- upstream/AVX_Implementation_KEM/pack_unpack.c
+++ upstream-patched/AVX_Implementation_KEM/pack_unpack.c
@@ -1,11 +1,10 @@
 #include "pack_unpack.h"
 
-void SABER_pack_3bit(uint8_t *bytes, uint16_t *data){
+void SABER_pack_3bit(uint8_t *bytes, const uint16_t *data){
 
 	uint32_t j;
 	uint32_t offset_data=0,offset_byte=0;
 	
-	offset_byte=0;
 	for(j=0;j<SABER_N/8;j++){
 		offset_byte=3*j;
 		offset_data=8*j;
@@ -15,12 +14,11 @@
 	}
 }
 
-void SABER_un_pack3bit(uint8_t *bytes, uint16_t *data){
+void SABER_un_pack3bit(uint16_t *data, const uint8_t *bytes){
 
 	uint32_t j;
 	uint32_t offset_data=0,offset_byte=0;	
 	
-	offset_byte=0;
 	for(j=0;j<SABER_N/8;j++){
 		offset_byte=3*j;
 		offset_data=8*j;
@@ -36,7 +34,7 @@
 
 }
 
-void SABER_pack_4bit(uint8_t *bytes, uint16_t *data){
+void SABER_pack_4bit(uint8_t *bytes, const uint16_t *data){
 
 	uint32_t j;
 	uint32_t offset_data=0;
@@ -48,7 +46,7 @@
 	}
 }
 
-void SABER_un_pack4bit(const unsigned char *bytes, uint16_t *Mask_ar){
+void SABER_un_pack4bit(uint16_t *data, const uint8_t *bytes){
 
 	uint32_t j;
 	uint32_t offset_data=0;
@@ -56,17 +54,16 @@
 	for(j=0;j<SABER_N/2;j++)
 	{
 		offset_data=2*j;
-		Mask_ar[offset_data] = bytes[j] & 0x0f;
-		Mask_ar[offset_data+1] = (bytes[j]>>4) & 0x0f;
+		data[offset_data] = bytes[j] & 0x0f;
+		data[offset_data+1] = (bytes[j]>>4) & 0x0f;
 	}
 }
 
-void SABER_pack_6bit(uint8_t *bytes, uint16_t *data){
+void SABER_pack_6bit(uint8_t *bytes, const uint16_t *data){
 
 	uint32_t j;
 	uint32_t offset_data=0,offset_byte=0;
 	
-	offset_byte=0;
 	for(j=0;j<SABER_N/4;j++){
 		offset_byte=3*j;
 		offset_data=4*j;
@@ -77,12 +74,11 @@
 }
 
 
-void SABER_un_pack6bit(const unsigned char *bytes, uint16_t *data){
+void SABER_un_pack6bit(uint16_t *data, const uint8_t *bytes){
 
 	uint32_t j;
 	uint32_t offset_data=0,offset_byte=0;	
 	
-	offset_byte=0;
 	for(j=0;j<SABER_N/4;j++){
 		offset_byte=3*j;
 		offset_data=4*j;
@@ -94,12 +90,11 @@
 
 }
 
-void SABER_pack10bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_pack10bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*10)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -118,12 +113,11 @@
 	}
 }
 
-void POLVECp2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void POLVECp2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*10)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -142,12 +136,11 @@
 	}
 }
 
-void POLVECq2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void POLVECq2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*13)/8;
 		for(j=0;j<SABER_N/8;j++){
@@ -185,12 +178,32 @@
 
 }
 
-void BS2POLVECp(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
+void BS2POLq(uint16_t data[SABER_N], const uint8_t *bytes){
+	
+	uint32_t j;
+	uint32_t offset_data=0,offset_byte=0;	
+	
+		for(j=0;j<SABER_N/8;j++){
+			offset_byte=13*j;
+			offset_data=8*j;
+			data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
+			data[offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
+			data[offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
+			data[offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
+			data[offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
+			data[offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
+			data[offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
+			data[offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
+		}
+}
+
+
+
+void BS2POLVECp(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*10)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -205,12 +218,11 @@
 	}
 }
 
-void BS2POLVECq(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
+void BS2POLVECq(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*13)/8;
 		for(j=0;j<SABER_N/8;j++){
@@ -232,12 +244,11 @@
 
 
 
-void SABER_un_pack10bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_un_pack10bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*10)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -255,12 +266,11 @@
 }
 
 
-void SABER_pack13bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_pack13bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*13)/8;
 		for(j=0;j<SABER_N/8;j++){
@@ -298,12 +308,11 @@
 
 }
 
-void SABER_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_un_pack13bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*13)/8;
 		for(j=0;j<SABER_N/8;j++){
@@ -323,12 +332,11 @@
 
 }
 
-void SABER_poly_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_N]){
+void SABER_poly_un_pack13bit(uint16_t data[SABER_N], const uint8_t *bytes){
 	
 	uint32_t j;
 	uint32_t offset_data=0,offset_byte=0;	
 	
-	offset_byte=0;
 	//for(i=0;i<SABER_K;i++){
 		//i=0;
 		//offset_byte1=i*(SABER_N*13)/8;
@@ -351,13 +359,12 @@
 }
 
 
-void SABER_pack11bit(uint8_t *bytes,  uint16_t data[SABER_K][SABER_N]){
+void SABER_pack11bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 /*This function packs 11 bit data stream into 8 bits of data.
 */
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*11)/8;
 		for(j=0;j<SABER_N/8;j++){
@@ -390,7 +397,7 @@
 
 }
 
-void SABER_un_pack11bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_un_pack11bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
@@ -423,12 +430,11 @@
 
 }
 
-void SABER_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_pack14bit(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N]){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*14)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -454,12 +460,11 @@
 }
 
 
-void SABER_un_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
+void SABER_un_pack14bit(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes){
 	
 	uint32_t i,j;
 	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
 	
-	offset_byte=0;
 	for(i=0;i<SABER_K;i++){
 		offset_byte1=i*(SABER_N*14)/8;
 		for(j=0;j<SABER_N/4;j++){
@@ -478,7 +483,7 @@
 
 }
 
-void POLVEC2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){
+void POLVEC2BS(uint8_t *bytes, const uint16_t data[SABER_K][SABER_N], uint16_t modulus){
 
 	if(modulus==1024)
 		POLVECp2BS(bytes, data);
@@ -486,12 +491,12 @@
 		POLVECq2BS(bytes, data);
 }
 
-void BS2POLVEC(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){
+void BS2POLVEC(uint16_t data[SABER_K][SABER_N], const uint8_t *bytes, uint16_t modulus){
 
 	if(modulus==1024)
-		BS2POLVECp(bytes, data);
+		BS2POLVECp(data, bytes);
 	else if(modulus==8192)
-		BS2POLVECq(bytes, data);
+		BS2POLVECq(data, bytes);
 
 }
 

