--- upstream/Reference_Implementation/sign/GeMSS128/src/convMQS_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/convMQS_gf2.c
@@ -108,8 +108,7 @@
     unsigned int j;
 
     #if HFEmr8
-        uint8_t *pk_U=(uint8_t*)malloc(HFEmr8*NB_BYTES_EQUATION
-                                             *sizeof(uint8_t));
+        uint8_t pk_U[HFEmr8*NB_BYTES_EQUATION]={0};
 
         convMQS_one_to_last_mr8_equations_gf2(pk_U,pk);
         for(j=0;j<HFEmr8;++j)
@@ -118,7 +117,6 @@
                           pk_U+j*NB_BYTES_EQUATION);
         }
 
-        free(pk_U);
     #endif
 
     #if HFEmq8
@@ -186,8 +184,7 @@
     unsigned int j;
 
     #if HFEmr8
-        uint8_t *pk_U=(uint8_t*)malloc(HFEmr8*NB_BYTES_EQUATION
-                                             *sizeof(uint8_t));
+        uint8_t pk_U[HFEmr8*NB_BYTES_EQUATION]={0};
 
         convMQS_one_to_last_mr8_equations_gf2(pk_U,pk);
     
@@ -216,8 +213,6 @@
             pk2_cp+=NB_BYTES_EQUATION;
             *pk2_cp^=((uint8_t)(val>>(j*HFENr8c)))<<HFENr8;
         }
-
-        free(pk_U);
     #endif
 
     #if HFEmq8

