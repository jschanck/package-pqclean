--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
@@ -482,16 +482,13 @@
     /* The current term is X^(q^i + q^j) */
     for(i=2;i<HFEDegI;++i)
     {
-        /* Here a_vec = row i */
+        j = 0;
         #if ENABLED_REMOVE_ODD_DEGREE
-        j=(((ONE32<<i)+ONE32)<=HFE_odd_degree)?0:1;
+        if (((ONE32<<i)+ONE32) > HFE_odd_degree) j=1;
+        #endif
+        /* Here a_vec = row i */
         a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
         for(;j<i;++j)
-        #else
-        /* Here a_vec = row i */
-        a_vecj=alpha_vec;
-        for(j=0;j<i;++j)
-        #endif
         {
             a_veci=a_vec;
             QUADRATIC_CASE_REF(a_veci,a_vecj);
@@ -509,19 +506,19 @@
     /* The current term is X^(q^HFEDegi + q^j) */
 
     /* Here a_vec = row i */
+    j = 0;
     #if ENABLED_REMOVE_ODD_DEGREE
-    j=(((ONE32<<i)+ONE32)<=HFE_odd_degree)?0:1;
-    a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
-    for(;j<HFEDegJ;++j)
-    #else
-    /* Here a_vec = row i */
-    a_vecj=alpha_vec;
-    for(j=0;j<HFEDegJ;++j)
+    if (((ONE32<<i)+ONE32) > HFE_odd_degree) j=1;
     #endif
+    /* Here a_vec = row i */
+    a_vecj=alpha_vec+j*(HFEn-1)*NB_WORD_GFqn;
+    #if HFEDegJ
+    for(; j<HFEDegJ;++j)
     {
         a_veci=a_vec;
         QUADRATIC_CASE_REF(a_veci,a_vecj);
     }
+    #endif
     /* Here a_veci = row i+1 */
 
     /* j=HFEDegJ */
@@ -656,15 +653,17 @@
         #if(HFEDegI!=HFEDegJ)
             /* Monic case */
             set1_gf2n(buf);
-            #if ((!ENABLED_REMOVE_ODD_DEGREE)||(LOG_odd_degree>=HFEDegI))
-            for(j=0;j<HFEDegJ;++j)
-            #else
-            for(j=1;j<HFEDegJ;++j)
+            #if HFEDegJ
+              #if ((!ENABLED_REMOVE_ODD_DEGREE)||(LOG_odd_degree>=HFEDegI))
+              for(j=0;j<HFEDegJ;++j)
+              #else
+              for(j=1;j<HFEDegJ;++j)
+              #endif
+              {
+                  add2_gf2n(buf,F_cp);
+                  F_cp+=NB_WORD_GFqn;
+              }
             #endif
-            {
-                add2_gf2n(buf,F_cp);
-                F_cp+=NB_WORD_GFqn;
-            }
             buf+=NB_WORD_GFqn;
         #endif
     #endif

