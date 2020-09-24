--- upstream/Reference_Implementation/sign/GeMSS128/src/sign_keypairHFE.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/sign_keypairHFE.c
@@ -112,7 +112,7 @@
     #if (ENABLED_SEED_SK&&GEN_INV_MATRIX_TRIAL_ERROR)
         expandSeedCxtDeclaration;
     #endif
-    mqsnv_gf2n Q;
+    UINT Q[MQnv_GFqn_SIZE];
     sparse_monic_gf2nx F;
     GLnv_gf2 S;
     GLn_gf2 T;
@@ -125,11 +125,17 @@
         Mnv_gf2 S_buf;
     #endif
     #if ENABLED_SEED_SK
-        UINT *sk_uncomp;
+        UINT sk_uncomp[(NB_UINT_HFEVPOLY+
+                       (LTRIANGULAR_NV_SIZE<<1)+
+                       (LTRIANGULAR_N_SIZE<<1)+
+                       SIZE_VECTOR_t)];
     #endif
     #if (GEN_INV_MATRIX_TRIAL_ERROR&&(!ENABLED_SEED_SK)&&GEN_INVERSE_IN_FIRST)
         unsigned int i;
     #endif
+    #if (FORMAT_HYBRID_CPK8)
+        uint8_t pk_tmp[MQ_GFqm8_SIZE];
+    #endif
     int ret;
 
 
@@ -141,18 +147,12 @@
     #if ENABLED_SEED_SK
         #if GEN_INVERTIBLE_MATRIX_LU
             /* The seed generates L,U and L',U' such as S=LU and T=L'U' */
-            sk_uncomp=(UINT*)malloc((NB_UINT_HFEVPOLY+(LTRIANGULAR_NV_SIZE<<1)
-                                     +(LTRIANGULAR_N_SIZE<<1)+SIZE_VECTOR_t)
-                                    *sizeof(UINT));
-            VERIFY_ALLOC_RET(sk_uncomp);
             expandSeed((uint8_t*)sk_uncomp,(NB_UINT_HFEVPOLY
                                      +(LTRIANGULAR_NV_SIZE<<1)
                                      +(LTRIANGULAR_N_SIZE<<1)+SIZE_VECTOR_t)<<3,
                  (uint8_t*)sk,SIZE_SEED_SK);
         #elif GEN_INV_MATRIX_TRIAL_ERROR
             /* The seed generates S and T */
-            sk_uncomp=(UINT*)malloc(SIZE_SK_HFE_UNCOMPRESSED_WORD*sizeof(UINT));
-            VERIFY_ALLOC_RET(sk_uncomp);
             expandSeedIUF(&hashInstance,(uint8_t*)sk,SIZE_SEED_SK<<3);
             expandSeedSqueeze(&hashInstance,(uint8_t*)sk_uncomp,
                                SIZE_SK_HFE_UNCOMPRESSED_WORD<<6);
@@ -176,24 +176,12 @@
     /* Here, the first element (of GF(2^n)) of Q is reserved to store cst.
        The matrix Q is stored as upper triangular matrix. */
 
-    Q=(UINT*)malloc(MQnv_GFqn_SIZE*sizeof(UINT));
-    if(!Q)
-    {
-        #if ENABLED_SEED_SK
-            free(sk_uncomp);
-        #endif
-        return ERROR_ALLOC;
-    }
     #if PRECOMPUTE2
         genSecretMQSprec(Q,F);
     #else
         ret=genSecretMQS_gf2(Q,F);
         if(ret)
         {
-            #if ENABLED_SEED_SK
-                free(sk_uncomp);
-            #endif
-            free(Q);
             return ret;
         }
     #endif
@@ -203,10 +191,6 @@
         S=MALLOC_MATRIXnv;
         if(!S)
         {
-            #if ENABLED_SEED_SK
-                free(sk_uncomp);
-            #endif
-            free(Q);
             return ERROR_ALLOC;
         }
         /* The allocated memory for S will be use for T */
@@ -383,57 +367,18 @@
     #endif
 
 
-    #if (ENABLED_SEED_SK&&GEN_INVERTIBLE_MATRIX_LU\
-                        &&(!AFFINE_TRANSFORMATION_BY_t))
-        free(sk_uncomp);
-    #endif
-
-
-    #if (FORMAT_HYBRID_CPK8)
-        uint8_t* pk_tmp=(uint8_t*)malloc(MQ_GFqm8_SIZE*sizeof(uint8_t));
-    #endif
-
-    #if (FORMAT_HYBRID_CPK8)
-        if(!pk_tmp)
-        {
-            #if (ENABLED_SEED_SK&&\
-                 (GEN_INV_MATRIX_TRIAL_ERROR||AFFINE_TRANSFORMATION_BY_t))
-                free(sk_uncomp);
-            #endif
-            free(Q);
-            #if ((!ENABLED_SEED_SK)||GEN_INVERTIBLE_MATRIX_LU)
-                /* T is stored in S. free(S) would have the same effect. */
-                free(T);
-            #endif
-            #if (GEN_INV_MATRIX_TRIAL_ERROR&&ENABLED_SEED_SK\
-                                           &&GEN_INVERSE_IN_FIRST)
-                /* T is stored in S_buf */
-                free(S_buf);
-            #endif
-            return ERROR_ALLOC;
-        }
-    #endif
-
-
     /* Use T (variable S) to compute cst_pk and Q_pk */
     #if (FORMAT_HYBRID_CPK8)
         mixEquationsMQS8_gf2(pk_tmp,Q,T);
     #elif FORMAT_MONOMIAL_PK8
         mixEquationsMQS8_gf2(pk,Q,T);
     #endif
-    free(Q);
 
-
-    #if (ENABLED_SEED_SK&&GEN_INV_MATRIX_TRIAL_ERROR\
-                        &&(!AFFINE_TRANSFORMATION_BY_t))
-        free(sk_uncomp);
-    #endif
     #if (GEN_INV_MATRIX_TRIAL_ERROR&&ENABLED_SEED_SK&&GEN_INVERSE_IN_FIRST)
         /* T is stored in S_buf */
         free(S_buf);
     #endif
 
-
     /* Generate the inverse of T */
     #if (GEN_INV_MATRIX_TRIAL_ERROR&&(!ENABLED_SEED_SK)\
                                    &&(!GEN_INVERSE_IN_FIRST))
@@ -466,10 +411,6 @@
         #else
             add2_gf2m((UINT*)pk,t);
         #endif
-
-        #if ENABLED_SEED_SK
-            free(sk_uncomp);
-        #endif
     #endif
 
 
@@ -477,10 +418,6 @@
         convMQS_one_eq_to_hybrid_rep8_gf2(pk,pk_tmp);
     #endif
 
-    #if (FORMAT_HYBRID_CPK8)
-        free(pk_tmp);
-    #endif
-
     return 0;
 }
 

