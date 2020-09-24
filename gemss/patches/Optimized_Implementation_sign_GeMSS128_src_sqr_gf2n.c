--- upstream/Optimized_Implementation/sign/GeMSS128/src/sqr_gf2n.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/sqr_gf2n.c
@@ -74,55 +74,10 @@
 
 /***********************************************************************/
 /***********************************************************************/
-/***************************** sqr with rem ****************************/
-/***********************************************************************/
-/***********************************************************************/
-
-
-/***********************************************************************/
-/***********************************************************************/
 /************************* sqr then rem version ************************/
 /***********************************************************************/
 /***********************************************************************/
 
-
-/* When rem is a macro */
-#if (K3!=1)
-    #define MUL_MOD_MACRO32(name_function,mul_function,rem_function) \
-        name_function\
-        {\
-            uint64_t res_mul,Q,R;\
-            mul_function;\
-            rem_function;\
-        }
-#else
-    #define MUL_MOD_MACRO32(name_function,mul_function,rem_function) \
-        name_function\
-        {\
-            uint64_t res_mul,Q;\
-            mul_function;\
-            rem_function;\
-        }
-#endif
-
-#define MUL_MOD_MACRO64(name_function,mul_function,rem_function,size) \
-    name_function\
-    {\
-        uint64_t res_mul[size],Q,R;\
-        mul_function;\
-        rem_function;\
-    }
-
-/* HFEn == 64 */
-#define MUL_MOD_MACRO64_K64(name_function,mul_function,rem_function,size) \
-    name_function\
-    {\
-        uint64_t res_mul[size],R;\
-        mul_function;\
-        rem_function;\
-    }
-
-
 #if HFEnr
     #define INIT_Q(size2) uint64_t Q[size2];
 #else
@@ -130,81 +85,108 @@
     #define INIT_Q(size2)
 #endif
 
-#if ((HFEn==312)||(HFEn==402)||(HFEn==544))
-    #define MUL_MOD_MACRO(name_function,mul_function,rem_function,size,size2) \
-        name_function\
-        {\
-            uint64_t res_mul[size];\
-            INIT_Q(size2);\
-            mul_function;\
-            rem_function;\
+#if (REM_MACRO)
+    #if (NB_WORD_GFqn!=1)
+        void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],R;
+            INIT_Q(NB_WORD_GFqn);
+            sqr_gf2x(res_mul,A);
+            REM_GF2N(res,res_mul,Q,R);
         }
-#else
-    #define MUL_MOD_MACRO(name_function,mul_function,rem_function,size,size2) \
-        name_function\
-        {\
-            uint64_t res_mul[size],R;\
-            INIT_Q(size2);\
-            mul_function;\
-            rem_function;\
+
+        void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],R;
+            INIT_Q(NB_WORD_GFqn);
+            sqr_nocst_gf2x(res_mul,A);
+            REM_GF2N(res,res_mul,Q,R);
+        }
+    #elif (HFEn<33)
+        void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul,Q,R;
+            sqr_gf2x(&res_mul,A);
+            REM_GF2N(*res,res_mul,Q,R);
         }
-#endif
 
-/* When rem is a function */
-#define MUL_MOD_FUNCTION32(name_function,mul_function,rem_function) \
-    name_function\
-    {\
-        uint64_t res_mul;\
-        mul_function;\
-        rem_function;\
-    }
+        void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul,Q,R;
+            sqr_nocst_gf2x(&res_mul,A);
+            REM_GF2N(*res,res_mul,Q,R);
+        }
+    #elif HFEnr
+        void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],Q,R;
+            sqr_gf2x(res_mul,A);
+            REM_GF2N(*res,res_mul,Q,R);
+        }
 
-#define MUL_MOD_FUNCTION(name_function,mul_function,rem_function,size) \
-    name_function\
-    {\
-        uint64_t res_mul[size];\
-        mul_function;\
-        rem_function;\
+        void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],Q,R;
+            sqr_nocst_gf2x(res_mul,A);
+            REM_GF2N(*res,res_mul,Q,R);
+        }
+    #else
+/* HFEn == 64 */
+    void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL],R;
+        sqr_gf2x(res_mul,A);
+        REM_GF2N(*res,res_mul,,R);
     }
 
-#if (REM_MACRO)
-    #if (NB_WORD_GFqn!=1)
-        MUL_MOD_MACRO(SQR_THEN_REM_GF2N,sqr_gf2x(res_mul,A),
-                      REM_GF2N(res,res_mul,Q,R),NB_WORD_MUL,NB_WORD_GFqn);
-        MUL_MOD_MACRO(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(res_mul,A),
-                      REM_GF2N(res,res_mul,Q,R),NB_WORD_MUL,NB_WORD_GFqn);
-    #elif (HFEn<33)
-        MUL_MOD_MACRO32(SQR_THEN_REM_GF2N,sqr_gf2x(&res_mul,A),
-                        REM_GF2N(*res,res_mul,Q,R));
-        MUL_MOD_MACRO32(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(&res_mul,A),
-                        REM_GF2N(*res,res_mul,Q,R));
-    #elif HFEnr
-        MUL_MOD_MACRO64(SQR_THEN_REM_GF2N,sqr_gf2x(res_mul,A),
-                        REM_GF2N(*res,res_mul,Q,R),NB_WORD_MUL);
-        MUL_MOD_MACRO64(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(res_mul,A),
-                        REM_GF2N(*res,res_mul,Q,R),NB_WORD_MUL);
-    #else
-        /* HFEn == 64 */
-        MUL_MOD_MACRO64_K64(SQR_THEN_REM_GF2N,sqr_gf2x(res_mul,A),
-                            REM_GF2N(*res,res_mul,,R),NB_WORD_MUL);
-        MUL_MOD_MACRO64_K64(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(res_mul,A),
-                            REM_GF2N(*res,res_mul,,R),NB_WORD_MUL);
+    void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL],R;
+        sqr_nocst_gf2x(res_mul,A);
+        REM_GF2N(*res,res_mul,,R);
+    }
     #endif
 #elif (NB_WORD_GFqn!=1)
-    MUL_MOD_FUNCTION(SQR_THEN_REM_GF2N,sqr_gf2x(res_mul,A),
-                     remsqr_gf2n(res,res_mul),NB_WORD_MUL);
-    MUL_MOD_FUNCTION(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(res_mul,A),
-                     remsqr_gf2n(res,res_mul),NB_WORD_MUL);
+    void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        sqr_gf2x(res_mul,A);
+        remsqr_gf2n(res,res_mul);
+    }
+
+    void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        sqr_nocst_gf2x(res_mul,A);
+        remsqr_gf2n(res,res_mul);
+    }
 #elif (HFEn<33)
-    MUL_MOD_FUNCTION32(SQR_THEN_REM_GF2N,sqr_gf2x(&res_mul,A),
-                       remsqr_gf2n(res,&res_mul));
-    MUL_MOD_FUNCTION32(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(&res_mul,A),
-                       remsqr_gf2n(res,&res_mul));
+    void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul;
+        sqr_gf2x(&res_mul,A);
+        remsqr_gf2n(res,&res_mul);
+    }
+
+    void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul;
+        sqr_nocst_gf2x(&res_mul,A);
+        remsqr_gf2n(res,&res_mul);
+    }
 #else
-    MUL_MOD_FUNCTION(SQR_THEN_REM_GF2N,sqr_gf2x(res_mul,A),
-                     remsqr_gf2n(res,res_mul),NB_WORD_MUL);
-    MUL_MOD_FUNCTION(SQR_NOCST_THEN_REM_GF2N,sqr_nocst_gf2x(res_mul,A),
-                     remsqr_gf2n(res,res_mul),NB_WORD_MUL);
-#endif
+    void PREFIX_NAME(sqr_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        sqr_gf2x(res_mul,A);
+        remsqr_gf2n(res,res_mul);
+    }
 
+    void PREFIX_NAME(sqr_nocst_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        sqr_nocst_gf2x(res_mul,A);
+        remsqr_gf2n(res,res_mul);
+    }
+#endif
 

