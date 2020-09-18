--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/src/mul_gf2n.c
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/src/mul_gf2n.c
@@ -132,44 +132,6 @@
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
@@ -177,67 +139,60 @@
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
-        }
-#else
-    #define MUL_MOD_MACRO(name_function,mul_function,rem_function,size,size2) \
-        name_function\
-        {\
-            uint64_t res_mul[size],R;\
-            INIT_Q(size2);\
-            mul_function;\
-            rem_function;\
-        }
-#endif
-
-/* When rem is a function */
-#define MUL_MOD_FUNCTION32(name_function,mul_function,rem_function) \
-    name_function\
-    {\
-        uint64_t res_mul;\
-        mul_function;\
-        rem_function;\
-    }
-
-#define MUL_MOD_FUNCTION(name_function,mul_function,rem_function,size) \
-    name_function\
-    {\
-        uint64_t res_mul[size];\
-        mul_function;\
-        rem_function;\
-    }
 
 #if (REM_MACRO)
     #if (NB_WORD_GFqn!=1)
-        MUL_MOD_MACRO(MUL_THEN_REM_GF2N,mul_gf2x(res_mul,A,B),
-                      REM_GF2N(res,res_mul,Q,R),NB_WORD_MUL,NB_WORD_GFqn);
+        void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL], R;
+            INIT_Q(NB_WORD_GFqn);
+            mul_gf2x(res_mul,A,B);
+            REM_GF2N(res,res_mul,Q,R);
+        }
     #elif (HFEn<33)
-        MUL_MOD_MACRO32(MUL_THEN_REM_GF2N,mul_gf2x(&res_mul,A,B),
-                        REM_GF2N(*res,res_mul,Q,R));
+        void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+        {
+            uint64_t res_mul,Q,R;
+            mul_gf2x(&res_mul,A,B);
+            REM_GF2N(*res,res_mul,Q,R);
+        }
     #elif HFEnr
-        MUL_MOD_MACRO64(MUL_THEN_REM_GF2N,mul_gf2x(res_mul,A,B),
-                        REM_GF2N(*res,res_mul,Q,R),NB_WORD_MUL);
+        void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],Q,R;
+            mul_gf2x(res_mul,A,B);
+            REM_GF2N(*res,res_mul,Q,R);
+        }
     #else
         /* HFEn == 64 */
-        MUL_MOD_MACRO64_K64(MUL_THEN_REM_GF2N,mul_gf2x(res_mul,A,B),
-                            REM_GF2N(*res,res_mul,,R),NB_WORD_MUL);
+        void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+        {
+            uint64_t res_mul[NB_WORD_MUL],R;
+            mul_gf2x(res_mul,A,B);
+            REM_GF2N(*res,res_mul,,R);
+        }
     #endif
 #elif (NB_WORD_GFqn!=1)
-    MUL_MOD_FUNCTION(MUL_THEN_REM_GF2N,mul_gf2x(res_mul,A,B),
-                     rem_gf2n(res,res_mul),NB_WORD_MUL);
+    void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        mul_gf2x(res_mul,A,B);
+        rem_gf2n(res,res_mul);
+    }
 #elif (HFEn<33)
-    MUL_MOD_FUNCTION32(MUL_THEN_REM_GF2N,mul_gf2x(&res_mul,A,B),
-                       rem_gf2n(res,&res_mul));
+    void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+    {
+        uint64_t res_mul;
+        mul_gf2x(&res_mul,A,B);
+        rem_gf2n(res,&res_mul);
+    }
 #else
-    MUL_MOD_FUNCTION(MUL_THEN_REM_GF2N,mul_gf2x(res_mul,A,B),
-                     rem_gf2n(res,res_mul),NB_WORD_MUL);
+    void PREFIX_NAME(mul_then_rem_gf2n)(uint64_t res[NB_WORD_GFqn], const uint64_t A[NB_WORD_GFqn], const uint64_t B[NB_WORD_GFqn])
+    {
+        uint64_t res_mul[NB_WORD_MUL];
+        mul_gf2x(res_mul,A,B);
+        rem_gf2n(res,res_mul);
+    }
 #endif
 
 

