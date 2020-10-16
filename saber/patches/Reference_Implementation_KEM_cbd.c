--- upstream/Reference_Implementation_KEM/cbd.c
+++ upstream-patched/Reference_Implementation_KEM/cbd.c
@@ -28,7 +28,7 @@
 
   for (i = 0; i < SABER_N / 4; i++)
   {
-    t = load_littleendian(buf + 3 * i, 3);
+    t = (uint32_t) load_littleendian(buf + 3 * i, 3);
     d = 0;
     for (j = 0; j < 3; j++)
       d += (t >> j) & 0x249249;
@@ -53,7 +53,7 @@
 
   for (i = 0; i < SABER_N / 4; i++)
   {
-    t = load_littleendian(buf + 4 * i, 4);
+    t = (uint32_t) load_littleendian(buf + 4 * i, 4);
     d = 0;
     for (j = 0; j < 4; j++)
       d += (t >> j) & 0x11111111;

