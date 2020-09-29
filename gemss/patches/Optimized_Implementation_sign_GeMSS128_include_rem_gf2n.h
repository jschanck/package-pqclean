--- upstream/Optimized_Implementation/sign/GeMSS128/include/rem_gf2n.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/rem_gf2n.h
@@ -7,7 +7,6 @@
 #include "gf2x.h"
 #include "tools_gf2n.h"
 #include "macro.h"
-#include "rem_gf2x.h"
 #include "rem5_gf2n.h"
 
 
@@ -36,112 +35,84 @@
 
 
 /* Automatic choice of REM_GF2N */
-
-#if(NB_WORD_GFqn==1)
-    #ifdef __TRINOMIAL_GF2N__
-        /* Example: REM64_TRINOMIAL_GF2X(P,Pol,HFEn,K3mod64,Q,R,MASK_GF2n) */
-        #if(K3==1)
-            #define REM_GF2N(P,Pol,Q,R) CONCAT(CONCAT_NB_BITS_MMUL_SUP(REM),\
-_TRINOMIAL_K31_GF2X(P,Pol,HFEn,K3mod64,Q,R,MASK_GF2n))
-        #else
-            #define REM_GF2N(P,Pol,Q,R) CONCAT(CONCAT_NB_BITS_MMUL_SUP(REM),\
-_TRINOMIAL_GF2X(P,Pol,HFEn,K3mod64,Q,R,MASK_GF2n))
-        #endif
-    #endif
-
-    #ifdef __PENTANOMIAL_GF2N__
-        #if (HFEn!=64)
-            /* Example: REM64_PENTANOMIAL_GF2X(P,Pol,HFEn,K1,K2,K3mod64,
-                                               Q,R,MASK_GF2n) */
-            #define REM_GF2N(P,Pol,Q,R) CONCAT(CONCAT_NB_BITS_MMUL_SUP(REM),\
-_PENTANOMIAL_GF2X(P,Pol,HFEn,K1,K2,K3mod64,Q,R,MASK_GF2n))
-        #else
-            /* HFEn == 64 */
-            #define REM_GF2N(P,Pol,Q,R) \
-                REM64_PENTANOMIAL_K64_GF2X(P,Pol,64,K1,K2,K3mod64,R)
-        #endif
-    #endif
-
-#elif(NB_WORD_GFqn==2)
-    #if (HFEn<97)
-        #ifdef __TRINOMIAL_GF2N__
-            #define REM_GF2N(P,Pol,Q,R) REM96_TRINOMIAL_GF2X(P,Pol,\
-K3mod64,KI,Q,R,MASK_GF2n)
-        #endif
-
-        #ifdef __PENTANOMIAL_GF2N__
-            #define REM_GF2N(P,Pol,Q,R) REM96_PENTANOMIAL_GF2X(P,Pol,\
-K1,K2,K3mod64,KI,Q,R,MASK_GF2n)
-        #endif
-    #else
-        #ifdef __TRINOMIAL_GF2N__
-            #define REM_GF2N(P,Pol,Q,R) REM128_TRINOMIAL_GF2X(P,Pol,\
-K3mod64,KI,KI64,Q,R,MASK_GF2n)
-        #endif
-
-        #ifdef __PENTANOMIAL_GF2N__
-            #if (HFEnr)
-                #define REM_GF2N(P,Pol,Q,R) REM128_PENTANOMIAL_GF2X(P,Pol,\
-K1,K2,K3mod64,KI,KI64,Q,R,MASK_GF2n)
-            #else
-                /* HFEn == 128 */
-                #define REM_GF2N(P,Pol,Q,R) \
-                    REM128_PENTANOMIAL_K128_GF2X(P,Pol,K1,K2,K3mod64,R)
-            #endif
-        #endif
-    #endif
-
-#else
-    #ifdef __TRINOMIAL_GF2N__
-        #if ((HFEn>256)&&(HFEn<289)&&(K3>32)&&(K3<64))
-            #define REM_GF2N(P,Pol,Q,R) REM288_SPECIALIZED_TRINOMIAL_GF2X(P,Pol\
-,K3,KI,KI64,K364,Q,R,MASK_GF2n)
-        #elif (HFEn==313)
-            #define REM_GF2N(P,Pol,Q,R) REM320_SPECIALIZED_TRINOMIAL_GF2X(\
-P,Pol,K3mod64,KI,KI64,K364,Q,R,MASK_GF2n)
-        #elif (HFEn==354)
-            #define REM_GF2N(P,Pol,Q,R) REM384_SPECIALIZED_TRINOMIAL_GF2X(\
-P,Pol,K3mod64,KI,KI64,K364,Q,R,MASK_GF2n)
-        #elif (HFEn==358)
-            #define REM_GF2N(P,Pol,Q,R) REM384_SPECIALIZED358_TRINOMIAL_GF2X(\
-P,Pol,K3mod64,KI,KI64,K364,Q,R,MASK_GF2n)
-        #elif (HFEn==402)
-            #define REM_GF2N(P,Pol,Q,R) REM402_SPECIALIZED_TRINOMIAL_GF2X(\
-P,Pol,K3mod64,KI,KI64,K364,Q,R,MASK_GF2n)
-        #else
-            /* Example: REM192_TRINOMIAL_GF2X(P,Pol,K3mod64,KI,KI64,K364mod64,
-                                              Q,R,MASK_GF2n) */
-            #define REM_GF2N(P,Pol,Q,R) CONCAT(CONCAT_NB_BITS_MMUL_SUP(REM),\
-_TRINOMIAL_GF2X(P,Pol,K3mod64,KI,KI64,K364mod64,Q,R,MASK_GF2n))
-        #endif
-    #endif
-
-    #ifdef __PENTANOMIAL_GF2N__
-        #if ((HFEn==312)&&(K3==128))
-            #define REM_GF2N(P,Pol,Q,R) REM312_PENTANOMIAL_K3_IS_128_GF2X(\
-P,Pol,K1,K2,,KI,KI64,K164,K264,,Q,R,MASK_GF2n)
-        #elif ((HFEn==448)&&(K3==64))
-            #define REM_GF2N(P,Pol,Q,R) REM448_PENTANOMIAL_K448_K3_IS_64_GF2X(\
-P,Pol,K1,K2,,K164,K264,,R)
-        #elif ((HFEn==544)&&(K3==128))
-            #define REM_GF2N(P,Pol,Q,R) REM544_PENTANOMIAL_K3_IS_128_GF2X(\
-P,Pol,K1,K2,,KI,KI64,K164,K264,,Q,R,MASK_GF2n)
-        #elif (HFEnr)
-            /* Example: REM192_PENTANOMIAL_GF2X(P,Pol,K1,K2,K3mod64,KI,KI64,
-                        K164,K264,K364mod64,Q,R,MASK_GF2n) */
-            #define REM_GF2N(P,Pol,Q,R) CONCAT(CONCAT_NB_BITS_MMUL_SUP(REM),\
-_PENTANOMIAL_GF2X(P,Pol,K1,K2,K3mod64,KI,KI64,K164,K264,K364mod64,Q,R,\
-MASK_GF2n))
-        #else
-            /* HFEn == NB_WORD_GFqn*64 */
-            /* Example: REM192_PENTANOMIAL_K192_GF2X(P,Pol,K1,K2,K3mod64,\
-                                                     K164,K264,K364mod64,R) */
-            #define REM_GF2N_TMP CONCAT(CONCAT_NB_BITS_MMUL_SUP(CONCAT(\
-CONCAT_NB_BITS_MMUL_SUP(REM),_PENTANOMIAL_K)),_GF2X)
-            #define REM_GF2N(P,Pol,Q,R) \
-                REM_GF2N_TMP(P,Pol,K1,K2,K3mod64,K164,K264,K364mod64,R)
-        #endif
-    #endif
+#if (HFEn==174||HFEn==175||HFEn==177)
+/* Assumes KI >= K3, which it is for {Blue,Red,}GeMSS128 */
+#define REM_GF2N(P,Pol,Q,R) \
+    (Q)[0]=((Pol)[2]>>(KI))^((Pol)[3]<<(KI64));\
+    (Q)[1]=((Pol)[3]>>(KI))^((Pol)[4]<<(KI64));\
+    (Q)[2]=((Pol)[4]>>(KI))^((Pol)[5]<<(KI64));\
+    XOR3(P,Pol,Q);\
+    (P)[0]^=(Q)[0]<<(K3);\
+    (P)[1]^=((Q)[0]>>(K364))^((Q)[1]<<(K3));\
+    (P)[2]^=((Q)[1]>>(K364))^((Q)[2]<<(K3));\
+    (R)=(Q)[2]>>((KI)-(K3));\
+    (P)[0]^=(R);\
+    (P)[0]^=(R)<<(K3);\
+    (P)[2]&=(MASK_GF2n);
+
+#elif (HFEn==265||HFEn==266)
+/* Assumes KI < K3, which it is for {Blue,Red,}GeMSS192 */
+#define REM_GF2N(P,Pol,Q,R)\
+    (Q)[0]=((Pol)[4]>>(KI))^((Pol)[5]<<(KI64));\
+    (Q)[1]=((Pol)[5]>>(KI))^((Pol)[6]<<(KI64));\
+    (Q)[2]=((Pol)[6]>>(KI))^((Pol)[7]<<(KI64));\
+    (Q)[3]=((Pol)[7]>>(KI))^((Pol)[8]<<(KI64));\
+    (Q)[4]=((Pol)[8]>>(KI));\
+    XOR5(P,Pol,Q);\
+    (P)[0]^=(Q)[0]<<(K3);\
+    (P)[1]^=((Q)[0]>>(K364))^((Q)[1]<<(K3));\
+    (P)[2]^=((Q)[1]>>(K364))^((Q)[2]<<(K3));\
+    (P)[3]^=((Q)[2]>>(K364))^((Q)[3]<<(K3));\
+    (P)[4]^=((Q)[3]>>(K364))^((Q)[4]<<(K3));\
+    /* 64-((K364)+(KI)) == ((K3)-(KI)) */\
+    (R)=((Q)[3]>>((K364)+(KI)))^((Q)[4]<<((K3)-(KI)));\
+    (P)[0]^=(R);\
+    (P)[0]^=(R)<<(K3);\
+    /* This row is the unique difference with REM288_TRINOMIAL_GF2X */\
+    (P)[1]^=(R)>>(K364);\
+    (P)[4]&=(MASK_GF2n);
+
+#elif (HFEn==354)
+#define REM_GF2N(P,Pol,Q,R) \
+    {uint64_t R2;\
+    (Q)[0]=((Pol)[5]>>(KI))^((Pol)[6]<<(KI64));\
+    (Q)[1]=((Pol)[6]>>(KI))^((Pol)[7]<<(KI64));\
+    (Q)[2]=((Pol)[7]>>(KI))^((Pol)[8]<<(KI64));\
+    (Q)[3]=((Pol)[8]>>(KI))^((Pol)[9]<<(KI64));\
+    (Q)[4]=((Pol)[9]>>(KI))^((Pol)[10]<<(KI64));\
+    (Q)[5]=((Pol)[10]>>(KI))^((Pol)[11]<<(KI64));\
+    XOR6(P,Pol,Q);\
+    /* 64-((K364)+(KI)) == ((K3mod64)-(KI)) */\
+    (R)=((Q)[3]>>((K364)+(KI)))^((Q)[4]<<((K3mod64)-(KI)));\
+    (P)[0]^=(R);\
+    (R2)=((Q)[4]>>((K364)+(KI)))^((Q)[5]<<((K3mod64)-(KI)));\
+    (P)[1]^=(R2);\
+    (P)[1]^=((R)^(Q)[0])<<(K3mod64);\
+    (P)[2]^=(((R)^(Q)[0])>>(K364))^((R2^(Q)[1])<<(K3mod64));\
+    (P)[3]^=((R2^(Q)[1])>>(K364))^((Q)[2]<<(K3mod64));\
+    (P)[4]^=((Q)[2]>>(K364))^((Q)[3]<<(K3mod64));\
+    (P)[5]^=(Q)[3]>>(K364);\
+    (P)[5]&=(MASK_GF2n);}
+
+#elif (HFEn==358)
+#define REM_GF2N(P,Pol,Q,R) \
+    (Q)[0]=((Pol)[5]>>(KI))^((Pol)[6]<<(KI64));\
+    (Q)[1]=((Pol)[6]>>(KI))^((Pol)[7]<<(KI64));\
+    (Q)[2]=((Pol)[7]>>(KI))^((Pol)[8]<<(KI64));\
+    (Q)[3]=((Pol)[8]>>(KI))^((Pol)[9]<<(KI64));\
+    (Q)[4]=((Pol)[9]>>(KI))^((Pol)[10]<<(KI64));\
+    (Q)[5]=((Pol)[10]>>(KI))^((Pol)[11]<<(KI64));\
+    /* 64-((k364)+(KI)) == ((K3mod64)-(KI)) */\
+    (R)=((Q)[4]>>((K364)+(KI)))^((Q)[5]<<((K3mod64)-(KI)));\
+    (Q)[0]^=(R);\
+    XOR6(P,Pol,Q);\
+    (P)[0]^=(Q)[0]<<(K3mod64);\
+    (P)[1]^=((Q)[0]>>(K364))^((Q)[1]<<(K3mod64));\
+    (P)[2]^=((Q)[1]>>(K364))^((Q)[2]<<(K3mod64));\
+    (P)[3]^=((Q)[2]>>(K364))^((Q)[3]<<(K3mod64));\
+    (P)[4]^=((Q)[3]>>(K364))^((Q)[4]<<(K3mod64));\
+    (P)[5]^=((Q)[4]>>(K364));\
+    (P)[5]&=(MASK_GF2n);
 #endif
 
 

