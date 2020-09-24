--- upstream/Optimized_Implementation/sign/GeMSS128/src/div_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/div_gf2nx.c
@@ -120,8 +120,11 @@
         }
 
         leading_coef=A+da*NB_WORD_GFqn;
-        i=(db<<1)-da;
-        i=MAXI(0,(int)i);
+        i=0;
+        if(2*db > da)
+        {
+            i = 2*db - da;
+        }
         res=A+(da-db+i)*NB_WORD_GFqn;
 
         for(;i<db;++i)

