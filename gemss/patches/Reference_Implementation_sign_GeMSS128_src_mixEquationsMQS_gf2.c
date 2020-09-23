--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/mixEquationsMQS_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/mixEquationsMQS_gf2.c
@@ -51,11 +51,10 @@
 
         for(i=0;i<HFEmq;++i)
         {
-            *((UINT*)pk)=pk_last[i];
+            STORE_UINT(pk, pk_last[i])
             pk+=8;
         }
 
-        /* We fill the last bytes of pk without 64-bit cast */
         for(i=0;i<(NB_BYTES_GFqm&7);++i)
         {
             pk[i]=pk_last[NB_WORD_GF2m-1]>>(i<<3);

