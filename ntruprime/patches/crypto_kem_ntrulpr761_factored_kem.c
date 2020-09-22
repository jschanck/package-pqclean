--- upstream/crypto_kem/ntrulpr761/factored/kem.c
+++ upstream-patched/crypto_kem/ntrulpr761/factored/kem.c
@@ -24,7 +24,7 @@
 /* return -1 if x<0; otherwise return 0 */
 static int int16_negative_mask(int16 x)
 {
-  uint16 u = x;
+  uint16 u = (uint16) x;
   u >>= 15;
   return -(int) u;
   /* alternative with gcc -fwrapv: */
@@ -45,26 +45,26 @@
 /* assumes twos complement; use, e.g., gcc -fwrapv */
 static Fq Fq_freeze(int32 x)
 {
-  x -= q*((q18*x)>>18);
-  x -= q*((q27*x+67108864)>>27);
-  return x;
+  x -= (int32) (q*((q18*x)>>18));
+  x -= (int32) (q*((q27*x+67108864)>>27));
+  return (Fq) x;
 }
 
 /* works for all uint32 x */
 static Fq Fq_bigfreeze(uint32 x)
 {
-  x -= q*((x*(uint64)q31)>>31);
-  x -= q*((x*(uint64)q31)>>31);
+  x -= (uint32) (q*((x*(uint64)q31)>>31));
+  x -= (uint32) (q*((x*(uint64)q31)>>31));
   x -= q;
-  x += (-(x>>31))&(uint32)q;
-  return x;
+  x += (~(x>>31)+1)&(uint32)q;
+  return (Fq) x;
 }
 
 /* ----- Top and Right */
 
 static int8 Top(Fq C)
 {
-  return (tau1*(int32)(C+tau0)+16384)>>15;
+  return (int8) ((tau1*(int32)(C+tau0)+16384)>>15);
 }
 
 static Fq Right(int8 T)
@@ -93,7 +93,7 @@
   for (i = w;i < p;++i) L[i] = (in[i]&(uint32)-3)|1;
   for (i = p;i < ppadsort;++i) L[i] = 0xffffffff;
   crypto_sort_uint32(L,ppadsort);
-  for (i = 0;i < p;++i) out[i] = (L[i]&3)-1;
+  for (i = 0;i < p;++i) out[i] = (small) ((L[i]&3)-1);
 }
 
 /* ----- underlying hash function */
@@ -104,7 +104,7 @@
 {
   unsigned char h[64];
   int i;
-  crypto_hash_sha512(h,in,inlen);
+  crypto_hash_sha512(h,in,(size_t) inlen);
   for (i = 0;i < 32;++i) out[i] = h[i];
 }
 
@@ -258,7 +258,7 @@
       int8 T[I];
       Top_decode(T,c+Rounded_bytes);
       for (i = 0;i < I;++i)
-        r[i] = -int16_negative_mask(Fq_freeze(Right(T[i])-aB[i]+4*w+1));
+        r[i] = (int8) -int16_negative_mask(Fq_freeze(Right(T[i])-aB[i]+4*w+1));
     }
   }
   {
@@ -267,9 +267,9 @@
     unsigned char x[1+Inputs_bytes+Ciphertexts_bytes+Confirm_bytes];
     Hide(cnew,x,r,pk,cache);
     mask = crypto_verify_clen(c,cnew);
-    for (i = 0;i < Inputs_bytes;++i) x[1+i] ^= mask&(x[1+i]^rho[i]);
+    for (i = 0;i < Inputs_bytes;++i) x[1+i] ^= (unsigned char) (mask&(x[1+i]^rho[i]));
     for (i = 0;i < Ciphertexts_bytes+Confirm_bytes;++i) x[1+Inputs_bytes+i] = c[i];
-    x[0] = 1+mask;
+    x[0] = (unsigned char) (1+mask);
     Hash(k,x,sizeof x);
   }
   return 0;

