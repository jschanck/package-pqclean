--- upstream/crypto_core/mult3sntrup761/avx/ntt.c
+++ upstream-patched/crypto_core/mult3sntrup761/avx/ntt.c
@@ -11,7 +11,12 @@
 typedef int16_t int16;
 typedef int32_t int32;
 
-static const int16 __attribute((aligned(32))) qdata_7681[] = {
+typedef union {
+  int16 data[106*16];
+  __m256i _dummy;
+} vec1696;
+
+static const vec1696 qdata_7681 = { .data = {
 #define precomp_8_1_0_0_0_0_1_1_1_1_0_0_0_0_1_1_1_1 *(const int16x16 *)(qdata+0)
   -3593,-3593,-3593,-3593,-3625,-3625,-3625,-3625,-3593,-3593,-3593,-3593,-3625,-3625,-3625,-3625,
 #define precomp_8_1_2_2_2_2_3_3_3_3_2_2_2_2_3_3_3_3 *(const int16x16 *)(qdata+16)
@@ -224,6 +229,7 @@
   -3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,
 #define scaledzeta_x16_8_7 *(const int16x16 *)(qdata+1680)
   -3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,
+  }
 } ;
 
 static inline int16x16 add_x16(int16x16 a,int16x16 b)
@@ -1335,7 +1341,7 @@
 
 void ntt512_7681(int16 *f,int reps)
 {
-  ntt512(f,reps,qdata_7681);
+  ntt512(f,reps,qdata_7681.data);
 }
 
 // inv stopntt 512
@@ -1950,5 +1956,5 @@
 
 void invntt512_7681(int16 *f,int reps)
 {
-  invntt512(f,reps,qdata_7681);
+  invntt512(f,reps,qdata_7681.data);
 }

