--- upstream/Reference_Implementation_KEM/pack_unpack.c
+++ upstream-patched/Reference_Implementation_KEM/pack_unpack.c
@@ -35,7 +35,7 @@
 #endif
 }
 
-void BS2POLT(const uint8_t bytes[SABER_SCALEBYTES_KEM], uint16_t data[SABER_N])
+void BS2POLT(uint16_t data[SABER_N], const uint8_t bytes[SABER_SCALEBYTES_KEM])
 {
 	size_t j, offset_byte, offset_data;
 #if SABER_ET == 3
@@ -98,7 +98,7 @@
 	}
 }
 
-static void BS2POLq(const uint8_t bytes[SABER_POLYBYTES], uint16_t data[SABER_N])
+static void BS2POLq(uint16_t data[SABER_N], const uint8_t bytes[SABER_POLYBYTES])
 {
 	size_t j, offset_byte, offset_data;
 	for (j = 0; j < SABER_N / 8; j++)
@@ -131,7 +131,7 @@
 	}
 }
 
-static void BS2POLp(const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES], uint16_t data[SABER_N])
+static void BS2POLp(uint16_t data[SABER_N], const uint8_t bytes[SABER_POLYCOMPRESSEDBYTES])
 {
 	size_t j, offset_byte, offset_data;
 	for (j = 0; j < SABER_N / 4; j++)
@@ -154,12 +154,12 @@
 	}
 }
 
-void BS2POLVECq(const uint8_t bytes[SABER_POLYVECBYTES], uint16_t data[SABER_L][SABER_N])
+void BS2POLVECq(uint16_t data[SABER_L][SABER_N], const uint8_t bytes[SABER_POLYVECBYTES])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLq(bytes + i * SABER_POLYBYTES, data[i]);
+		BS2POLq(data[i], bytes + i * SABER_POLYBYTES);
 	}
 }
 
@@ -172,16 +172,16 @@
 	}
 }
 
-void BS2POLVECp(const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES], uint16_t data[SABER_L][SABER_N])
+void BS2POLVECp(uint16_t data[SABER_L][SABER_N], const uint8_t bytes[SABER_POLYVECCOMPRESSEDBYTES])
 {
 	size_t i;
 	for (i = 0; i < SABER_L; i++)
 	{
-		BS2POLp(bytes + i * (SABER_EP * SABER_N / 8), data[i]);
+		BS2POLp(data[i], bytes + i * (SABER_EP * SABER_N / 8));
 	}
 }
 
-void BS2POLmsg(const uint8_t bytes[SABER_KEYBYTES], uint16_t data[SABER_N])
+void BS2POLmsg(uint16_t data[SABER_N], const uint8_t bytes[SABER_KEYBYTES])
 {
 	size_t i, j;
 	for (j = 0; j < SABER_KEYBYTES; j++)

