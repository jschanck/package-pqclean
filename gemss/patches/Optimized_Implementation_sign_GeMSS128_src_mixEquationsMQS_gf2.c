--- upstream/Optimized_Implementation/sign/GeMSS128/src/mixEquationsMQS_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/mixEquationsMQS_gf2.c
@@ -51,14 +51,13 @@
 
         for(i=0;i<HFEmq;++i)
         {
-            *((UINT*)pk)=pk_last[i];
+            STORE_UINT(pk, pk_last[i])
             pk+=8;
         }
 
-        /* We fill the last bytes of pk without 64-bit cast */
         for(i=0;i<(NB_BYTES_GFqm&7);++i)
         {
-            pk[i]=pk_last[NB_WORD_GF2m-1]>>(i<<3);
+            pk[i]=(uint8_t)(pk_last[NB_WORD_GF2m-1]>>(i<<3));
         }
     #endif
 }

