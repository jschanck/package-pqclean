--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/evalMQSv_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/evalMQSv_gf2.c
@@ -109,18 +109,6 @@
 /**************************************************************************/
 
 
-#if NB_VARr
-    #define REM_X \
-        xi=m[i];\
-        for(j=0;j<NB_VARr;++j,++k)\
-        {\
-            x[k]=-((xi>>j)&UINT_1);\
-        }
-#else
-    #define REM_X
-#endif
-
-
 
 
 /* Input:
@@ -139,16 +127,18 @@
     unsigned int i,j,k;
 
     /* Compute one time all -((xi>>1)&UINT_1) */
+    i=0;
     k=0;
-    for(i=0;i<NB_VARq;++i)
+    while(k < NB_VAR)
     {
         xi=m[i];
-        for(j=0;j<NB_BITS_UINT;++j,++k)
+        for(j=0; (j<NB_BITS_UINT) && (k<NB_VAR); ++j)
         {
-            x[k]=-((xi>>j)&UINT_1);
+              x[k]=-((xi>>j)&UINT_1);
+              ++k;
         }
+        ++i;
     }
-    REM_X;
 
     /* Constant cst_pk */
     COPY_64bits_variables(c,pk);
@@ -187,16 +177,18 @@
     unsigned int i,j,k;
 
     /* Compute one time all -((xi>>1)&UINT_1) */
+    i=0;
     k=0;
-    for(i=0;i<NB_VARq;++i)
+    while(k < NB_VAR)
     {
         xi=m[i];
-        for(j=0;j<NB_BITS_UINT;++j,++k)
+        for(j=0; (j<NB_BITS_UINT) && (k<NB_VAR); ++j)
         {
-            x[k]=-((xi>>j)&UINT_1);
+              x[k]=-((xi>>j)&UINT_1);
+              ++k;
         }
+        ++i;
     }
-    REM_X;
 
     /* Constant cst_pk */
     COPY_64bits_variables(c,pk);

