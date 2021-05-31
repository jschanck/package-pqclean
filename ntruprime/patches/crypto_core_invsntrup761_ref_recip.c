--- upstream/crypto_core/invsntrup761/ref/recip.c
+++ upstream-patched/crypto_core/invsntrup761/ref/recip.c
@@ -20,17 +20,17 @@
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
@@ -50,7 +50,7 @@
   x -= q*((q18*x)>>18);
   x -= q*((q27*x+67108864)>>27);
   x -= q*((q27*x+67108864)>>27);
-  return x;
+  return (Fq) x;
 }
 
 static Fq Fq_recip(Fq a1)
@@ -83,7 +83,7 @@
   r[0] = Fq_recip(3);
   for (i = 0;i < p;++i) f[i] = 0;
   f[0] = 1; f[p-1] = f[p] = -1;
-  for (i = 0;i < p;++i) g[p-1-i] = in[i];
+  for (i = 0;i < p;++i) g[p-1-i] = (Fq) in[i];
   g[p] = 0;
 
   delta = 1;
@@ -92,13 +92,13 @@
     for (i = p;i > 0;--i) v[i] = v[i-1];
     v[0] = 0;
 
-    swap = int16_negative_mask(-delta) & int16_nonzero_mask(g[0]);
+    swap = int16_negative_mask((int16)-delta) & int16_nonzero_mask(g[0]);
     delta ^= swap&(delta^-delta);
     delta += 1;
 
     for (i = 0;i < p+1;++i) {
-      t = swap&(f[i]^g[i]); f[i] ^= t; g[i] ^= t;
-      t = swap&(v[i]^r[i]); v[i] ^= t; r[i] ^= t;
+      t = swap&(f[i]^g[i]); f[i] ^= (Fq) t; g[i] ^= (Fq) t;
+      t = swap&(v[i]^r[i]); v[i] ^= (Fq) t; r[i] ^= (Fq) t;
     }
 
     f0 = f[0];
@@ -114,6 +114,6 @@
   for (i = 0;i < p;++i) out[i] = Fq_bigfreeze(scale*(int32)v[p-1-i]);
 
   crypto_encode_pxint16(outbytes,out);
-  outbytes[2*p] = int16_nonzero_mask(delta);
+  outbytes[2*p] = (unsigned char) int16_nonzero_mask((int16) delta);
   return 0;
 }

