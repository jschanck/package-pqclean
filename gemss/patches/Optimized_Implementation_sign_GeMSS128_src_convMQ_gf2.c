--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/convMQ_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/convMQ_gf2.c
@@ -98,7 +98,7 @@
     /* i == HFEnv */
     nb_bits=HFEnv;
     /* For each column */
-    for(j=HFEnv-1;j>=LOST_BITS;--j,++k)
+    for(j=HFEnv-1;j>=(int)LOST_BITS;--j,++k)
     {
         pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&ONE8)<<(k&7);
         nb_bits+=j;
@@ -248,7 +248,6 @@
     #endif
 
     #if LAST_ROW_R
-        ir=LAST_ROW_R;
         if(nb_bits&63)
         {
             #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
@@ -276,7 +275,7 @@
                 #else
                     pk2[k]=pk64[k]>>(nb_bits&63);
 
-                    if(((nb_bits&63)+ir)>64)
+                    if(((nb_bits&63)+LAST_ROW_R)>64)
                     {
                         end=0;
                         pk_end=(uint8_t*)(pk64+k+1);
@@ -295,7 +294,7 @@
                 }
 
                 pk2[k]=pk64[k]>>(nb_bits&63);
-                if(((nb_bits&63)+ir)>64)
+                if(((nb_bits&63)+LAST_ROW_R)>64)
                 {
                     pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
                 }

