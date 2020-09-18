--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/convMQ_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/convMQ_gf2.c
@@ -98,7 +98,7 @@
     /* i == HFEnv */
     nb_bits=HFEnv;
     /* For each column */
-    for(j=HFEnv-1;j>=LOST_BITS;--j,++k)
+    for(j=HFEnv-1;j>=(int)LOST_BITS;--j,++k)
     {
         pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&ONE8)<<(k&7);
         nb_bits+=j;

