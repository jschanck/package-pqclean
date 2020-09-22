--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/signHFE.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/signHFE.c
@@ -677,7 +677,7 @@
                 /* Add the v bits to DR */
                 #if HFEnr
                     DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                    for(i=0;i<(NB_WORD_GFqv-1);++i)
+                    for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                     {
                         DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                     }
@@ -685,7 +685,7 @@
                         DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                     #endif
                 #else
-                    for(i=0;i<NB_WORD_GFqv;++i)
+                    for(i=0;(int)i<NB_WORD_GFqv;++i)
                     {
                         DR[NB_WORD_GFqn+i]=V[i];
                     }
@@ -770,9 +770,10 @@
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
@@ -824,13 +825,6 @@
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
@@ -981,7 +975,7 @@
             /* Add the v bits to DR */
             #if HFEnr
                 DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                for(i=0;i<(NB_WORD_GFqv-1);++i)
+                for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                 {
                     DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                 }
@@ -989,7 +983,7 @@
                     DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                 #endif
             #else
-                for(i=0;i<NB_WORD_GFqv;++i)
+                for(i=0;(int)i<NB_WORD_GFqv;++i)
                 {
                     DR[NB_WORD_GFqn+i]=V[i];
                 }

