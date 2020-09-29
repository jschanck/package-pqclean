--- upstream/Reference_Implementation/sign/GeMSS128/src/signHFE.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/signHFE.c
@@ -83,8 +83,10 @@
         for(k1=1;k1<NB_ITE;++k1)
         {
             /* Number of bits to complete the byte of sm8, in [0,7] */
-            val_n=((HFEDELTA+HFEv)<((8-(nb_bits&7U))&7U))?(HFEDELTA+HFEv)
-                  :((8-(nb_bits&7U))&7U);
+            if ((HFEDELTA+HFEv)<((8-(nb_bits&7U))&7U))
+                val_n=(HFEDELTA+HFEv);
+            else
+                val_n=((8-(nb_bits&7U))&7U);
 
             /* First byte of sm8 */
             if(nb_bits&7U)
@@ -193,10 +195,6 @@
 
 
     #if GEN_INVERTIBLE_MATRIX_LU
-        ALIGNED_GFqn_MALLOC(sk_HFE->sk_uncomp,UINT*,NB_UINT_HFEVPOLY
-                                  +(LTRIANGULAR_NV_SIZE<<1)
-                                  +(LTRIANGULAR_N_SIZE<<1)+SIZE_VECTOR_t
-                                  +MATRIXnv_SIZE+MATRIXn_SIZE,sizeof(UINT));
         expandSeed((uint8_t*)(sk_HFE->sk_uncomp),(NB_UINT_HFEVPOLY
                                      +(LTRIANGULAR_NV_SIZE<<1)
                                      +(LTRIANGULAR_N_SIZE<<1)+SIZE_VECTOR_t)<<3,
@@ -313,7 +311,8 @@
 {
     #if HFEv
         cst_sparse_monic_gf2nx F_HFEv;
-        UINT* F;
+        sparse_monic_gf2nx F;
+        sparse_monic_gf2nx F_cp;
         unsigned int i;
     #endif
 
@@ -333,13 +332,10 @@
     #endif
 
     #if HFEv
+        F=sk_HFE->F_struct.poly;
         F_HFEv=sk_HFE->F_HFEv;
 
-        ALIGNED_GFqn_MALLOC(F,UINT*,NB_UINT_HFEPOLY,sizeof(UINT));
-        VERIFY_ALLOC_RET(F);
-
         #if (HFEDeg>1)
-        UINT *F_cp;
         unsigned int j;
 
         /* X^(2^0) */
@@ -351,11 +347,11 @@
         {
             /* Copy i quadratic terms */
 
+            j=0;
             #if ENABLED_REMOVE_ODD_DEGREE
-            for(j=(((1U<<i)+1U)<=HFE_odd_degree)?0:1;j<i;++j)
-            #else
-            for(j=0;j<i;++j)
+            if(((1U<<i)+1U)>HFE_odd_degree) ++j;
             #endif
+            for(;j<i;++j)
             {
                 /* X^(2^i + 2^j) */
                 copy_gf2n(F_cp,F_HFEv);
@@ -370,11 +366,11 @@
         }
         #if HFEDegJ
             /* X^(2^HFEDegI + 2^j) */
+            j=0;
             #if ENABLED_REMOVE_ODD_DEGREE
-            for(j=(((1U<<i)+1U)<=HFE_odd_degree)?0:1;j<HFEDegJ;++j)
-            #else
-            for(j=0;j<HFEDegJ;++j)
+            if(((1U<<i)+1U)>HFE_odd_degree) ++j;
             #endif
+            for(;j<HFEDegJ;++j)
             {
                 copy_gf2n(F_cp,F_HFEv);
                 F_HFEv+=NB_WORD_GFqn;
@@ -382,7 +378,6 @@
             }
         #endif
         #endif
-        sk_HFE->F_struct.poly=F;
     #else
         sk_HFE->F_struct.poly=sk_HFE->F_HFEv;
     #endif
@@ -447,7 +442,7 @@
     #endif
 
     int nb_root;
-    secret_key_HFE sk_HFE;
+    secret_key_HFE sk_HFE={0};
 
     #if(HFEv)
         UINT* F;
@@ -666,9 +661,6 @@
             if(nb_root<0)
             {
                 /* Error from chooseRootHFE */
-                #if HFEv
-                    ALIGNED_GFqn_FREE(F);
-                #endif
                 return nb_root;
             }
 
@@ -677,7 +669,7 @@
                 /* Add the v bits to DR */
                 #if HFEnr
                     DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                    for(i=0;i<(NB_WORD_GFqv-1);++i)
+                    for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                     {
                         DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                     }
@@ -685,7 +677,7 @@
                         DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                     #endif
                 #else
-                    for(i=0;i<NB_WORD_GFqv;++i)
+                    for(i=0;(int)i<NB_WORD_GFqv;++i)
                     {
                         DR[NB_WORD_GFqn+i]=V[i];
                     }
@@ -728,14 +720,6 @@
         }
     } while(b);
 
-    #if ENABLED_SEED_SK
-        free(sk_HFE.sk_uncomp);
-    #endif
-    #if HFEv
-        ALIGNED_GFqn_FREE(F);
-    #endif
-
-
     /* Copy the salt in the signature */
     for(k=0;k<SIZE_SALT_WORD;++k)
     {
@@ -770,9 +754,10 @@
 {
     UINT sm[SIZE_SIGN_UNCOMPRESSED-SIZE_SALT_WORD]={0};
 
-    static_vecnv_gf2 DR[NB_WORD_GF2nv];
-    static_gf2n U[NB_WORD_GFqn];
-    UINT Hi_tab[SIZE_DIGEST_UINT],Hi1_tab[SIZE_DIGEST_UINT];
+    static_vecnv_gf2 DR[NB_WORD_GF2nv] = {0};
+    static_gf2n U[NB_WORD_GFqn] = {0};
+    UINT Hi_tab[SIZE_DIGEST_UINT] = {0};
+    UINT Hi1_tab[SIZE_DIGEST_UINT] = {0};
     UINT *tmp, *Hi=Hi_tab,*Hi1=Hi1_tab;
     unsigned int k;
     #if (HFEnv!=HFEm)
@@ -786,7 +771,7 @@
     #endif
 
     int nb_root;
-    secret_key_HFE sk_HFE;
+    secret_key_HFE sk_HFE={0};
 
     #if(HFEv)
         UINT* F;
@@ -824,13 +809,6 @@
     /* Compute H1 = H(m) */
     HASH((unsigned char*)Hi,m,len);
 
-    /* It is to initialize S0 to 0, because Sk||Xk is stored in sm */
-    for(k=0;k<NB_WORD_GF2nv;++k)
-    {
-        sm[k]=0;
-        DR[k]=0;
-    }
-
     for(k=1;k<=NB_ITE;++k)
     {
         #ifdef KAT_INT
@@ -967,9 +945,6 @@
             if(nb_root<0)
             {
                 /* Error from chooseRootHFE */
-                #if HFEv
-                    ALIGNED_GFqn_FREE(F);
-                #endif
                 return nb_root;
             }
 
@@ -981,7 +956,7 @@
             /* Add the v bits to DR */
             #if HFEnr
                 DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                for(i=0;i<(NB_WORD_GFqv-1);++i)
+                for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                 {
                     DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                 }
@@ -989,7 +964,7 @@
                     DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                 #endif
             #else
-                for(i=0;i<NB_WORD_GFqv;++i)
+                for(i=0;(int)i<NB_WORD_GFqv;++i)
                 {
                     DR[NB_WORD_GFqn+i]=V[i];
                 }
@@ -1026,12 +1001,6 @@
         }
     }
 
-    #if ENABLED_SEED_SK
-        free(sk_HFE.sk_uncomp);
-    #endif
-    #if HFEv
-        ALIGNED_GFqn_FREE(F);
-    #endif
     #ifdef KAT_INT
         CLOSE_KAT_INT_FILE;
     #endif

