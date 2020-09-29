--- upstream/Reference_Implementation/sign/GeMSS128/src/frobeniusMap_gf2nx.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/frobeniusMap_gf2nx.c
@@ -26,7 +26,7 @@
  * @remark  Requirement: F.L must be initialized with initListDifferences_gf2nx.
  * @remark  Constant-time implementation when CONSTANT_TIME!=0.
  */
-unsigned int PREFIX_NAME(frobeniusMap_HFE_gf2nx)(gf2nx Xqn, const
+unsigned int PREFIX_NAME(frobeniusMap_HFE_gf2nx)(gf2nx Xqn,
                                     complete_sparse_monic_gf2nx F, cst_gf2n U)
 {
     static_gf2n cst[NB_WORD_GFqn];
@@ -125,7 +125,7 @@
             b=isNot0_gf2n(Xqn+i*NB_WORD_GFqn);
             mask|=b;
             /* We add 1 to d as soon as we exceed all left zero coefficients */
-            d+=mask;
+            d+=(unsigned int)mask;
         }
     #else
         if(d==1)

