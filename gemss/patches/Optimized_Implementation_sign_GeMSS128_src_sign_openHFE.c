--- upstream/Optimized_Implementation/sign/GeMSS128/src/sign_openHFE.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/sign_openHFE.c
@@ -57,8 +57,10 @@
         for(k1=1;k1<NB_ITE;++k1)
         {
             /* Number of bits to complete the byte of sm8, in [0,7] */
-            val_n=((HFEDELTA+HFEv)<((8-(nb_bits&7U))&7U))?(HFEDELTA+HFEv)
-                  :((8-(nb_bits&7U))&7U);
+            if ((HFEDELTA+HFEv)<((8-(nb_bits&7U))&7U))
+              val_n=(HFEDELTA+HFEv);
+            else
+              val_n=((8-(nb_bits&7U))&7U);
 
             /* First byte of sm8 */
             if(nb_bits&7U)

