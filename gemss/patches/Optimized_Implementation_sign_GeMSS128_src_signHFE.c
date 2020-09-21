--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/signHFE.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/signHFE.c
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
@@ -981,7 +981,7 @@
             /* Add the v bits to DR */
             #if HFEnr
                 DR[NB_WORD_GFqn-1]^=V[0]<<HFEnr;
-                for(i=0;i<(NB_WORD_GFqv-1);++i)
+                for(i=0;(int)i<(NB_WORD_GFqv-1);++i)
                 {
                     DR[NB_WORD_GFqn+i]=(V[i]>>(64-HFEnr))^(V[i+1]<<HFEnr);
                 }
@@ -989,7 +989,7 @@
                     DR[NB_WORD_GFqn+i]=V[i]>>(64-HFEnr);
                 #endif
             #else
-                for(i=0;i<NB_WORD_GFqv;++i)
+                for(i=0;(int)i<NB_WORD_GFqv;++i)
                 {
                     DR[NB_WORD_GFqn+i]=V[i];
                 }

