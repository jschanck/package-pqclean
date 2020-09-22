--- upstream/crypto_core/inv3sntrup653/ref/recip.c
+++ upstream-patched/crypto_core/inv3sntrup653/ref/recip.c
@@ -18,17 +18,17 @@
 /* return -1 if x!=0; else return 0 */
 static int int16_nonzero_mask(int16 x)
 {
-  uint16 u = x; /* 0, else 1...65535 */
+  uint16 u = (uint16) x; /* 0, else 1...65535 */
   uint32 v = u; /* 0, else 1...65535 */
-  v = -v; /* 0, else 2^32-65535...2^32-1 */
+  v = ~v+1; /* 0, else 2^32-65535...2^32-1 */
   v >>= 31; /* 0, else 1 */
-  return -v; /* 0, else -1 */
+  return -(int) v; /* 0, else -1 */
 }
 
 /* return -1 if x<0; otherwise return 0 */
 static int int16_negative_mask(int16 x)
 {
-  uint16 u = x;
+  uint16 u = (uint16) x;
   u >>= 15;
   return -(int) u;
   /* alternative with gcc -fwrapv: */
@@ -43,7 +43,7 @@
 /* works for -16384 <= x < 16384 */
 static small F3_freeze(int16 x)
 {
-  return x-3*((10923*x+16384)>>15);
+  return (small) (x-3*((10923*x+16384)>>15));
 }
 
 /* byte p of output is 0 if recip succeeded; else -1 */
@@ -62,7 +62,7 @@
   f[0] = 1; f[p-1] = f[p] = -1;
   for (i = 0;i < p;++i) {
     small i1 = in[i]&1;
-    g[p-1-i] = i1-(in[i]&(i1<<1));
+    g[p-1-i] = (small) (i1-(in[i]&(i1<<1)));
   }
   g[p] = 0;
     
@@ -73,25 +73,25 @@
     v[0] = 0;
     
     sign = -g[0]*f[0];
-    swap = int16_negative_mask(-delta) & int16_nonzero_mask(g[0]);
+    swap = int16_negative_mask((int16) -delta) & int16_nonzero_mask(g[0]);
     delta ^= swap&(delta^-delta);
     delta += 1;
     
     for (i = 0;i < p+1;++i) {
-      t = swap&(f[i]^g[i]); f[i] ^= t; g[i] ^= t;
-      t = swap&(v[i]^r[i]); v[i] ^= t; r[i] ^= t;
+      t = swap&(f[i]^g[i]); f[i] ^= (small) t; g[i] ^= (small) t;
+      t = swap&(v[i]^r[i]); v[i] ^= (small) t; r[i] ^= (small) t;
     }
   
-    for (i = 0;i < p+1;++i) g[i] = F3_freeze(g[i]+sign*f[i]);
-    for (i = 0;i < p+1;++i) r[i] = F3_freeze(r[i]+sign*v[i]);
+    for (i = 0;i < p+1;++i) g[i] = F3_freeze((int16) (g[i]+sign*f[i]));
+    for (i = 0;i < p+1;++i) r[i] = F3_freeze((int16) (r[i]+sign*v[i]));
 
     for (i = 0;i < p;++i) g[i] = g[i+1];
     g[p] = 0;
   }
   
   sign = f[0];
-  for (i = 0;i < p;++i) out[i] = sign*v[p-1-i];
+  for (i = 0;i < p;++i) out[i] = (small) (sign*v[p-1-i]);
   
-  out[p] = int16_nonzero_mask(delta);
+  out[p] = (small) int16_nonzero_mask((int16) delta);
   return 0;
 } 

