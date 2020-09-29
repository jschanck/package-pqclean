--- upstream/Reference_Implementation/sign/GeMSS128/src/invMatrixnv_gf2.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/invMatrixnv_gf2.c
@@ -28,7 +28,7 @@
 
 #define ADDROW(LOOPK,LOOPKINV) \
         /* pivot */\
-        mask=-(((*S_cpj)>>ir)&1);\
+        mask=(1+~(((*S_cpj)>>ir)&1));\
         LOOPK;\
         LOOPKINV;
 
@@ -49,7 +49,7 @@
 
 #define LOOPIR(NB_IT,LOOPK1,LOOPK2) \
     bit_ir=UINT_1;\
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* If the pivot is 0, search the pivot */\
         if(!((*S_cpi)&bit_ir))\
@@ -70,7 +70,7 @@
 
 /* Only modify S_inv */
 #define LOOPIR_DOWN_TO_UP(NB_IT) \
-    for(ir=NB_IT-1;ir!=(unsigned int)(-1);--ir,--i)\
+    for(ir=(NB_IT)-1;ir!=(unsigned int)(-1);--ir,--i)\
     {\
         S_cpj=S_cpi;\
         Sinv_cpj=Sinv_cpi;\
@@ -81,7 +81,7 @@
             S_cpj-=NB_WORD_GF2nv;\
             Sinv_cpj-=NB_WORD_GF2nv;\
             /* pivot */\
-            mask=-(((*S_cpj)>>ir)&1);\
+            mask=(1+~(((*S_cpj)>>ir)&1));\
             xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);\
         }\
 \
@@ -133,7 +133,6 @@
         LOOPIR(HFEnvr-1,SWAP_WORD(*S_cpj,*S_cpi),*S_cpj^=*S_cpi&mask);
 
         /* Step 2 */
-        bit_ir=UINT_1<<(HFEnvr-1);
         LOOPIR_DOWN_TO_UP(HFEnvr);
     #else
         /* To begin to last row */
@@ -178,16 +177,16 @@
     }
 
 #define LOOPIR_CST(NB_IT) \
-    for(ir=0;ir<NB_IT;++ir,++i)\
+    for(ir=0;ir<(NB_IT);++ir,++i)\
     {\
         /* row i += (1-pivot_i)* row j */\
-        LOOPJ_CST({mask=(-(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\
+        LOOPJ_CST({mask=(1+~(UINT_1-(((*S_cpi)>>ir)&UINT_1)));\
                    LOOPK(XORLOADMASK1_1(S_cpi+k,S_cpj+k,mask);)\
                    xorLoadMask1_gf2nv(Sinv_cpi,Sinv_cpj,mask);\
                   });\
 \
         /* row j += (pivot_j) * row_i */\
-        LOOPJ_CST({mask=(-(((*S_cpj)>>ir)&UINT_1));\
+        LOOPJ_CST({mask=(1+~(((*S_cpj)>>ir)&UINT_1));\
                    LOOPK(XORLOADMASK1_1(S_cpj+k,S_cpi+k,mask);)\
                    xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);\
                   });\
@@ -315,7 +314,7 @@
                 Sinv_cpj+=NB_WORD_GF2nv;
                 L_cpj+=(j>>6)+1;
 
-                mask=(-(((*L_cpj)>>ir)&UINT_1));
+                mask=(1+~(((*L_cpj)>>ir)&UINT_1));
                 for(k=0;k<=iq;++k)
                 {
                     XORLOADMASK1_1(Sinv_cpj+k,Sinv_cpi+k,mask);
@@ -344,7 +343,7 @@
                 Sinv_cpj+=NB_WORD_GF2nv;
                 L_cpj+=(j>>6)+1;
 
-                mask=(-(((*L_cpj)>>ir)&UINT_1));
+                mask=(1+~(((*L_cpj)>>ir)&UINT_1));
                 for(k=0;k<=iq;++k)
                 {
                     XORLOADMASK1_1(Sinv_cpj+k,Sinv_cpi+k,mask);
@@ -382,7 +381,7 @@
         for(j=0;j<i;++j)
         {
             /* pivot */
-            mask=-(((U[j>>6])>>(j&63U))&1U);
+            mask=(1+~(((U[j>>6])>>(j&63U))&1U));
             xorLoadMask1_gf2nv(Sinv_cpj,Sinv_cpi,mask);
 
             /* next row */

