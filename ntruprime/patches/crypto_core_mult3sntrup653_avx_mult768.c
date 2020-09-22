--- upstream/crypto_core/mult3sntrup653/avx/mult768.c
+++ upstream-patched/crypto_core/mult3sntrup653/avx/mult768.c
@@ -15,6 +15,21 @@
 #define mulhrs_x16 _mm256_mulhrs_epi16
 #define signmask_x16(x) _mm256_srai_epi16((x),15)
 
+typedef union {
+  int16 v[3][512];
+  int16x16 _dummy;
+} vec3x512;
+
+typedef union {
+  int16 v[768];
+  int16x16 _dummy;
+} vec768;
+
+typedef union {
+  int16 v[3*512];
+  int16x16 _dummy;
+} vec1536;
+
 static int16x16 squeeze_3_x16(int16x16 x)
 {
   return sub_x16(x,mullo_x16(mulhrs_x16(x,const_x16(10923)),const_x16(3)));
@@ -133,14 +148,14 @@
   }
 }
 
-#define ALIGNED __attribute((aligned(32)))
-
 static void mult768(int16 h[1536],const int16 f[768],const int16 g[768])
 {
-  ALIGNED int16 fpad[3][512];
-  ALIGNED int16 gpad[3][512];
+  vec3x512 x1, x2;
+  vec1536 x3;
+#define fpad (x1.v)
+#define gpad (x2.v)
 #define hpad fpad
-  ALIGNED int16 h_7681[1536];
+#define h_7681 (x3.v)
   int i;
 
   good(fpad,f);
@@ -169,7 +184,7 @@
   }
 
   invntt512_7681(hpad[0],3);
-  ungood(h_7681,hpad);
+  ungood(h_7681,(const int16(*)[512]) hpad);
 
   for (i = 0;i < 1536;i += 16) {
     int16x16 u = load_x16(&h_7681[i]);
@@ -198,9 +213,11 @@
 
 int crypto_core(unsigned char *outbytes,const unsigned char *inbytes,const unsigned char *kbytes,const unsigned char *cbytes)
 {
-  ALIGNED int16 f[768];
-  ALIGNED int16 g[768];
-  ALIGNED int16 fg[1536];
+  vec768 x1, x2;
+  vec1536 x3;
+#define f (x1.v)
+#define g (x2.v)
+#define fg (x3.v)
 #define h f
   int i;
   int16x16 x;
@@ -210,19 +227,19 @@
   for (i = p&~15;i < 768;i += 16) store_x16(&g[i],x);
 
   for (i = 0;i < p;++i) {
-    int8 fi = inbytes[i];
+    int8 fi = (int8) inbytes[i];
     int8 fi0 = fi&1;
-    f[i] = fi0-(fi&(fi0<<1));
+    f[i] = (int16) (fi0-(fi&(fi0<<1)));
   }
   for (i = 0;i < p;++i) {
-    int8 gi = kbytes[i];
+    int8 gi = (int8) kbytes[i];
     int8 gi0 = gi&1;
-    g[i] = gi0-(gi&(gi0<<1));
+    g[i] = (int16) (gi0-(gi&(gi0<<1)));
   }
 
   mult768(fg,f,g);
 
-  fg[0] -= fg[p-1];
+  fg[0] = (int16) (fg[0] - fg[p-1]);
   for (i = 0;i < 768;i += 16) {
     int16x16 fgi = load_x16(&fg[i]);
     int16x16 fgip = load_x16(&fg[i + p]);
@@ -232,7 +249,7 @@
     store_x16(&h[i],x);
   }
 
-  for (i = 0;i < p;++i) outbytes[i] = h[i];
+  for (i = 0;i < p;++i) outbytes[i] = (unsigned char) h[i];
 
   return 0;
 }

