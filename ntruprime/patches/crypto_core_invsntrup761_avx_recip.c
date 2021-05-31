--- upstream/crypto_core/invsntrup761/avx/recip.c
+++ upstream-patched/crypto_core/invsntrup761/avx/recip.c
@@ -22,11 +22,11 @@
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
@@ -47,7 +47,7 @@
 {
   x -= q*((q18*x)>>18);
   x -= q*((q27*x+67108864)>>27);
-  return x;
+  return (Fq) x;
 }
 
 static Fq Fq_bigfreeze(int32 x)
@@ -168,13 +168,13 @@
     if (q > 5167) f0 = Fq_freeze(f0);
 
     minusdelta = -delta;
-    swap = int16_negative_mask(minusdelta) & int16_nonzero_mask(g0);
+    swap = int16_negative_mask((int16) minusdelta) & int16_nonzero_mask(g0);
     delta ^= swap & (delta ^ minusdelta);
     delta += 1;
 
     fgflip = swap & (f0 ^ g0);
-    f0 ^= fgflip;
-    g0 ^= fgflip;
+    f0 ^= (Fq) fgflip;
+    g0 ^= (Fq) fgflip;
 
     f[0] = f0;
 
@@ -188,13 +188,13 @@
     if (q > 5167) f0 = Fq_freeze(f0);
 
     minusdelta = -delta;
-    swap = int16_negative_mask(minusdelta) & int16_nonzero_mask(g0);
+    swap = int16_negative_mask((int16) minusdelta) & int16_nonzero_mask(g0);
     delta ^= swap & (delta ^ minusdelta);
     delta += 1;
 
     fgflip = swap & (f0 ^ g0);
-    f0 ^= fgflip;
-    g0 ^= fgflip;
+    f0 ^= (Fq) fgflip;
+    g0 ^= (Fq) fgflip;
 
     f[0] = f0;
 
@@ -206,6 +206,6 @@
   for (i = 0;i < p;++i) out[i] = Fq_bigfreeze(scale*(int32)Fq_freeze(v[p-i]));
 
   crypto_encode_pxint16(outbytes,out);
-  outbytes[2*p] = int16_nonzero_mask(delta);
+  outbytes[2*p] = (unsigned char) int16_nonzero_mask((int16) delta);
   return 0;
 }

