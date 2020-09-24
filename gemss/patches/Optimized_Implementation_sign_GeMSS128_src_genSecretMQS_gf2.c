--- upstream/Optimized_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/genSecretMQS_gf2.c
@@ -30,7 +30,7 @@
 
 #if HFEv
     #define LINEAR_VCASE_REF(a_veci) \
-        a_veci-=(HFEn-1)*NB_WORD_GFqn;\
+        (a_veci)-=(HFEn-1)*NB_WORD_GFqn;\
         MQS_cp=MQS+(HFEn+1)*NB_WORD_GFqn;\
         for(j=0;j<HFEv;++j)\
         {\
@@ -47,7 +47,7 @@
                 add2_gf2n(MQS_cp,tmp1);\
                 MQS_cp+=NB_WORD_GFqn;\
             }\
-            a_veci+=NB_WORD_GFqn;\
+            (a_veci)+=NB_WORD_GFqn;\
         }\
         F_cp+=HFEv*NB_WORD_GFqn;
 #else
@@ -64,7 +64,7 @@
     for(j=1;j<HFEn;++j)\
     {\
         mul_gf2n(lin_cp,F_cp,a_vec);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;
@@ -80,7 +80,7 @@
     {\
         mul_gf2n(tmp1,F_cp,a_vec);\
         add2_gf2n(lin_cp,tmp1);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;\
@@ -97,7 +97,7 @@
     for(j=1;j<HFEn;++j)\
     {\
         add2_gf2n(lin_cp,a_vec);\
-        a_vec+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
         lin_cp+=NB_WORD_GFqn;\
     }
 
@@ -124,7 +124,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_vec+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_vec)+ja*NB_WORD_GFqn);\
         mul_gf2n(MQS_cp,tmp1,F_cp);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
@@ -143,16 +143,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,tmp_i,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_i,(a_vecj)+ja*NB_WORD_GFqn);\
             copy_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,tmp_j,a_vec+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_j,(a_vec)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_vec+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     F_cp+=NB_WORD_GFqn;
 
@@ -175,7 +175,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_veci+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_veci)+ja*NB_WORD_GFqn);\
         mul_gf2n(tmp_i,tmp1,F_cp);\
         add2_gf2n(MQS_cp,tmp_i);\
         MQS_cp+=NB_WORD_GFqn;\
@@ -196,16 +196,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,tmp_i,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_i,(a_vecj)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,tmp_j,a_veci+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,tmp_j,(a_veci)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_veci+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_veci)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     /* Here, a_veci = row i+1 */\
     /* Here, a_vecj = row j+1 */\
@@ -229,7 +229,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(tmp1,a_vecj+ja*NB_WORD_GFqn,a_veci+ja*NB_WORD_GFqn);\
+        add_gf2n(tmp1,(a_vecj)+ja*NB_WORD_GFqn,(a_veci)+ja*NB_WORD_GFqn);\
         add2_gf2n(MQS_cp,tmp1);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
@@ -246,16 +246,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,a_veci,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_veci,(a_vecj)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,a_vecj,a_veci+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vecj,(a_veci)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_veci+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_veci)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }\
     /* Here, a_veci = row i+1 */\
     /* Here, a_vecj = row j+1 */
@@ -276,7 +276,7 @@
     for(ja=0;ja<HFEn-1;++ja)\
     {\
         /* x_0*x_(ja+1) + x_(ja+1)*x_0 */\
-        add_gf2n(MQS_cp,a_vecj+ja*NB_WORD_GFqn,a_vec+ja*NB_WORD_GFqn);\
+        add_gf2n(MQS_cp,(a_vecj)+ja*NB_WORD_GFqn,(a_vec)+ja*NB_WORD_GFqn);\
         MQS_cp+=NB_WORD_GFqn;\
     }\
 \
@@ -291,16 +291,16 @@
         for(ja=1;ja<(HFEn-ia);++ja)\
         {\
             /* Compute the coefficient of x_ia*x_(ja+1) */\
-            mul_gf2n(tmp1,a_vec,a_vecj+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vec,(a_vecj)+ja*NB_WORD_GFqn);\
             copy_gf2n(MQS_cp,tmp1);\
             /* Compute the coefficient of x_(ja+1)*x_ia */\
-            mul_gf2n(tmp1,a_vecj,a_vec+ja*NB_WORD_GFqn);\
+            mul_gf2n(tmp1,a_vecj,(a_vec)+ja*NB_WORD_GFqn);\
             add2_gf2n(MQS_cp,tmp1);\
             MQS_cp+=NB_WORD_GFqn;\
         }\
         JUMP_VINEGAR_REF;\
-        a_vec+=NB_WORD_GFqn;\
-        a_vecj+=NB_WORD_GFqn;\
+        (a_vec)+=NB_WORD_GFqn;\
+        (a_vecj)+=NB_WORD_GFqn;\
     }
 
 
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
@@ -604,8 +601,6 @@
         /* F begins to X^3, the first "quadratic" term */
         F+=(NB_WORD_GFqn*(HFEv+1))<<1;
 
-        F_cp=F;
-
         /* X^3 */
         #if ((!ENABLED_REMOVE_ODD_DEGREE)||(1<=LOG_odd_degree))
             copy_gf2n(buf,F);
@@ -656,15 +651,17 @@
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

