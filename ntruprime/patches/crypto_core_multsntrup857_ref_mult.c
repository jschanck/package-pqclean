--- upstream/crypto_core/multsntrup857/ref/mult.c
+++ upstream-patched/crypto_core/multsntrup857/ref/mult.c
@@ -17,7 +17,7 @@
 {
   x -= q*((q18*x)>>18);
   x -= q*((q27*x+67108864)>>27);
-  return x;
+  return (Fq) x;
 }
 
 int crypto_core(unsigned char *outbytes,const unsigned char *inbytes,const unsigned char *kbytes,const unsigned char *cbytes)
@@ -33,9 +33,9 @@
     f[i] = Fq_freeze(f[i]);
 
   for (i = 0;i < p;++i) {
-    small gi = kbytes[i];
+    small gi = (small) kbytes[i];
     small gi0 = gi&1;
-    g[i] = gi0-(gi&(gi0<<1));
+    g[i] = (small) (gi0-(gi&(gi0<<1)));
   }
 
   for (i = 0;i < p;++i) {

