--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/convMQS_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/convMQS_gf2.c
@@ -57,7 +57,7 @@
             /* jr=0 */ 
             *pk2=((*pk_cp)>>ir)&ONE8;
             pk_cp+=NB_BYTES_GFqm;
-            for(jr=1;jr<HFENr8;++jr)
+            for(jr=1;(int)jr<HFENr8;++jr)
             {
                 *pk2^=(((*pk_cp)>>ir)&ONE8)<<jr;
                 pk_cp+=NB_BYTES_GFqm;

