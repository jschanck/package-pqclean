--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/evalMQSv_gf2.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/evalMQSv_gf2.c
@@ -140,7 +140,7 @@
 
     /* Compute one time all -((xi>>1)&UINT_1) */
     k=0;
-    for(i=0;i<NB_VARq;++i)
+    for(i=0;(int)i<NB_VARq;++i)
     {
         xi=m[i];
         for(j=0;j<NB_BITS_UINT;++j,++k)

