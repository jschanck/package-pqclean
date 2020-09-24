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
@@ -351,11 +353,11 @@
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
@@ -370,11 +372,11 @@
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
@@ -677,7 +679,7 @@
                 /* Add the v bits to DR */
                 #if HFEnr
                     DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                    for(i=0;i<(NB_WORD_GFqv-1);++i)
+                    for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                     {
                         DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                     }
@@ -685,7 +687,7 @@
                         DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                     #endif
                 #else
-                    for(i=0;i<NB_WORD_GFqv;++i)
+                    for(i=0;(int)i<NB_WORD_GFqv;++i)
                     {
                         DR[NB_WORD_GFqn+i]=V[i];
                     }
@@ -770,9 +772,10 @@
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
@@ -824,13 +827,6 @@
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
@@ -981,7 +977,7 @@
             /* Add the v bits to DR */
             #if HFEnr
                 DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                for(i=0;i<(NB_WORD_GFqv-1);++i)
+                for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                 {
                     DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                 }
@@ -989,7 +985,7 @@
                     DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                 #endif
             #else
-                for(i=0;i<NB_WORD_GFqv;++i)
+                for(i=0;(int)i<NB_WORD_GFqv;++i)
                 {
                     DR[NB_WORD_GFqn+i]=V[i];
                 }

