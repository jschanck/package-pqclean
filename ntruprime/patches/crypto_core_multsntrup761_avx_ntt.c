--- upstream/crypto_core/multsntrup761/avx/ntt.c
+++ upstream-patched/crypto_core/multsntrup761/avx/ntt.c
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
@@ -224,9 +229,10 @@
   -3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,-3625,
 #define scaledzeta_x16_8_7 *(const int16x16 *)(qdata+1680)
   -3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,-3182,
+  }
 } ;
 
-static const int16 __attribute((aligned(32))) qdata_10753[] = {
+static const vec1696 qdata_10753 = { .data = {
     // precomp_8_1_0_0_0_0_1_1_1_1_0_0_0_0_1_1_1_1
   1018,1018,1018,1018,3688,3688,3688,3688,1018,1018,1018,1018,3688,3688,3688,3688,
     // precomp_8_1_2_2_2_2_3_3_3_3_2_2_2_2_3_3_3_3
@@ -439,6 +445,7 @@
   3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,3688,
     // scaledzeta_x16_8_7
   4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,4188,
+  }
 } ;
 
 static inline int16x16 add_x16(int16x16 a,int16x16 b)
@@ -1544,18 +1551,18 @@
     _mm256_storeu_si256((int16x16 *) (f+112),e7);
     f += 128;
   }
-  f -= 128*reps;
+  // f -= 128*reps;
   // stopntt 512
 }
 
 void ntt512_7681(int16 *f,int reps)
 {
-  ntt512(f,reps,qdata_7681);
+  ntt512(f,reps,qdata_7681.data);
 }
 
 void ntt512_10753(int16 *f,int reps)
 {
-  ntt512(f,reps,qdata_10753);
+  ntt512(f,reps,qdata_10753.data);
 }
 // inv stopntt 512
 
@@ -2163,16 +2170,16 @@
     _mm256_storeu_si256((int16x16 *) (f+448),e28);
     f += 512;
   }
-  f -= 512*reps;
+  // f -= 512*reps;
   // inv startntt 512
 }
 
 void invntt512_7681(int16 *f,int reps)
 {
-  invntt512(f,reps,qdata_7681);
+  invntt512(f,reps,qdata_7681.data);
 }
 
 void invntt512_10753(int16 *f,int reps)
 {
-  invntt512(f,reps,qdata_10753);
+  invntt512(f,reps,qdata_10753.data);
 }

