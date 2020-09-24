--- upstream/Reference_Implementation/sign/GeMSS128/src/sign_openHFE.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/sign_openHFE.c
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
@@ -509,12 +511,8 @@
 
     /* Compute p(S_(NB_IT),X_(NB_IT)) */
     #if (FORMAT_HYBRID_CPK8&&EVAL_HYBRID_CPK8_UNCOMP)
-        UINT* pk_tmp;
+        UINT pk_tmp[(1+NB_WORD_UNCOMP_EQ*HFEmr8)];
         unsigned int i;
-        #if HFEmr8
-            /* 1 to store the constant */
-            pk_tmp=(UINT*)malloc((1+NB_WORD_UNCOMP_EQ*HFEmr8)*sizeof(UINT));
-        #endif
 
         #if (HFENr8&&(HFEmr8>1))
             uint64_t val;
@@ -578,10 +576,6 @@
     #endif
 
 
-    #if (FORMAT_HYBRID_CPK8&&EVAL_HYBRID_CPK8_UNCOMP&&HFEmr8)
-        free(pk_tmp);
-    #endif
-
     return ret;
 }
 

