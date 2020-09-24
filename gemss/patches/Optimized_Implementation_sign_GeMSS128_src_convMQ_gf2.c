--- upstream/Optimized_Implementation/sign/GeMSS128/src/convMQ_gf2.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/convMQ_gf2.c
@@ -98,7 +98,7 @@
     /* i == HFEnv */
     nb_bits=HFEnv;
     /* For each column */
-    for(j=HFEnv-1;j>=LOST_BITS;--j,++k)
+    for(j=HFEnv-1;j>=(int)LOST_BITS;--j,++k)
     {
         pk2[k>>3]^=((pk[nb_bits>>3]>>(nb_bits&7))&ONE8)<<(k&7);
         nb_bits+=j;
@@ -135,10 +135,15 @@
  */
 UINT PREFIX_NAME(convMQ_last_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk)
 {
-    const uint64_t *pk64;
     unsigned int iq,ir,k,nb_bits;
+    uint64_t t1, t2;
+    const uint8_t *pk64 = pk;
+    #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
+    const uint8_t *pk_end;
+    uint64_t end;
+    unsigned int l;
+    #endif
 
-    pk64=(uint64_t*)pk;
 
     nb_bits=1;
     /* For each row */
@@ -150,29 +155,34 @@
             {
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
-                pk2[k]=pk64[k]>>(nb_bits&63);
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
                 if(((nb_bits&63)+ir)>64)
                 {
-                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
+                    LOAD_UINT(t1, &pk64[8*(k+1)])
+                    pk2[k]^=t1<<(64-(nb_bits&63));
                 }
 
                 if(((nb_bits&63)+ir)>=64)
                 {
-                    ++pk64;
+                    pk64+=8;
                 }
             } else
             {
                 for(k=0;k<=iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
             }
 
-            pk64+=iq;
+            pk64+=8*iq;
             /* 0 padding on the last word */
             pk2[iq]&=(ONE64<<ir)-ONE64;
             pk2+=iq+1;
@@ -184,16 +194,19 @@
         {
             for(k=0;k<=iq;++k)
             {
-                pk2[k]=(pk64[k]>>(nb_bits&63))^(pk64[k+1]<<(64-(nb_bits&63)));
+                LOAD_UINT(t1, &pk64[8*k])
+                LOAD_UINT(t2, &pk64[8*(k+1)])
+                pk2[k]=(t1>>(nb_bits&63))^(t2<<(64-(nb_bits&63)));
             }
         } else
         {
             for(k=0;k<=iq;++k)
             {
-                pk2[k]=pk64[k];
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1;
             }
         }
-        pk64+=iq+1;
+        pk64+=8*(iq+1);
         pk2+=iq+1;
         nb_bits+=(iq+1)<<6;
     }
@@ -205,29 +218,34 @@
             {
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
-                pk2[k]=pk64[k]>>(nb_bits&63);
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
                 if(((nb_bits&63)+ir)>64)
                 {
-                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
+                    LOAD_UINT(t1, &pk64[8*(k+1)])
+                    pk2[k]^=t1<<(64-(nb_bits&63));
                 }
 
                 if(((nb_bits&63)+ir)>=64)
                 {
-                    ++pk64;
+                    pk64+=8;
                 }
             } else
             {
                 for(k=0;k<=iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
             }
 
-            pk64+=iq;
+            pk64+=8*iq;
             /* 0 padding on the last word */
             pk2[iq]&=(ONE64<<ir)-ONE64;
             pk2+=iq+1;
@@ -241,14 +259,7 @@
     #define LAST_ROW_R ((HFEnv-LOST_BITS)&63)
     iq=LAST_ROW_Q;
 
-    #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
-        uint8_t *pk_end;
-        uint64_t end;
-        unsigned int l;
-    #endif
-
     #if LAST_ROW_R
-        ir=LAST_ROW_R;
         if(nb_bits&63)
         {
             #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
@@ -257,15 +268,18 @@
 
                 for(k=0;k<NB_WHOLE_BLOCKS;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
                 #if (NB_WHOLE_BLOCKS<LAST_ROW_Q)
-                    pk2[k]=pk64[k]>>(nb_bits&63);
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1>>(nb_bits&63);
 
                     end=0;
-                    pk_end=(uint8_t*)(pk64+k+1);
+                    pk_end=pk64+8*(k+1);
                     for(l=0;l<(((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7);++l)
                     {
                         end^=((uint64_t)(pk_end[l]))<<(l<<3);
@@ -274,12 +288,13 @@
                     pk2[k]^=end<<(64-(nb_bits&63));
                     pk2[k+1]=end>>(nb_bits&63);
                 #else
-                    pk2[k]=pk64[k]>>(nb_bits&63);
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1>>(nb_bits&63);
 
-                    if(((nb_bits&63)+ir)>64)
+                    if(((nb_bits&63)+LAST_ROW_R)>64)
                     {
                         end=0;
-                        pk_end=(uint8_t*)(pk64+k+1);
+                        pk_end=pk64+8*(k+1);
                         for(l=0;l<(((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7);++l)
                         {
                             end^=((uint64_t)(pk_end[l]))<<(l<<3);
@@ -290,14 +305,18 @@
             #else
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
-                pk2[k]=pk64[k]>>(nb_bits&63);
-                if(((nb_bits&63)+ir)>64)
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
+                if(((nb_bits&63)+LAST_ROW_R)>64)
                 {
-                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
+                    LOAD_UINT(t1, &pk64[8*(k+1)])
+                    pk2[k]^=t1<<(64-(nb_bits&63));
                 }
             #endif
         } else
@@ -305,11 +324,12 @@
             #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
 
                 end=0;
-                pk_end=(uint8_t*)(pk64+k);
+                pk_end=pk64+8*k;
                 for(l=0;l<(((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7);++l)
                 {
                     end^=((uint64_t)(pk_end[l]))<<(l<<3);
@@ -318,7 +338,8 @@
             #else
                 for(k=0;k<=iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
             #endif
         }
@@ -328,13 +349,16 @@
             #if (((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7)
                 for(k=0;k<(iq-1);++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
-                pk2[k]=pk64[k]>>(nb_bits&63);
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
 
                 end=0;
-                pk_end=(uint8_t*)(pk64+k+1);
+                pk_end=pk64+8*(k+1);
                 for(l=0;l<(((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7);++l)
                 {
                     end^=((uint64_t)(pk_end[l]))<<(l<<3);
@@ -343,15 +367,18 @@
             #else
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
             #endif
         } else
         {
             for(k=0;k<iq;++k)
             {
-                pk2[k]=pk64[k];
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1;
             }
         }
     #endif
@@ -380,10 +407,11 @@
  */
 UINT PREFIX_NAME(convMQ_uncompressL_gf2)(uint64_t* pk2, const uint8_t* pk)
 {
-    const uint64_t *pk64;
+    const uint8_t *pk64;
     unsigned int iq,ir,k,nb_bits;
+    uint64_t t1, t2;
 
-    pk64=(uint64_t*)pk;
+    pk64=pk;
 
     nb_bits=1;
     /* For each row */
@@ -395,29 +423,34 @@
             {
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
-                pk2[k]=pk64[k]>>(nb_bits&63);
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
                 if(((nb_bits&63)+ir)>64)
                 {
-                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
+                    LOAD_UINT(t1, &pk64[8*(k+1)])
+                    pk2[k]^=t1<<(64-(nb_bits&63));
                 }
 
                 if(((nb_bits&63)+ir)>=64)
                 {
-                    ++pk64;
+                    pk64+=8;
                 }
             } else
             {
                 for(k=0;k<=iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
             }
 
-            pk64+=iq;
+            pk64+=8*iq;
             /* 0 padding on the last word */
             pk2[iq]&=(ONE64<<ir)-ONE64;
             pk2+=iq+1;
@@ -429,16 +462,19 @@
         {
             for(k=0;k<=iq;++k)
             {
-                pk2[k]=(pk64[k]>>(nb_bits&63))^(pk64[k+1]<<(64-(nb_bits&63)));
+                LOAD_UINT(t1, &pk64[8*k])
+                LOAD_UINT(t2, &pk64[8*(k+1)])
+                pk2[k]=(t1>>(nb_bits&63))^(t2<<(64-(nb_bits&63)));
             }
         } else
         {
             for(k=0;k<=iq;++k)
             {
-                pk2[k]=pk64[k];
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1;
             }
         }
-        pk64+=iq+1;
+        pk64+=8*(iq+1);
         pk2+=iq+1;
         nb_bits+=(iq+1)<<6;
     }
@@ -450,29 +486,34 @@
             {
                 for(k=0;k<iq;++k)
                 {
-                    pk2[k]=(pk64[k]>>(nb_bits&63))
-                          ^(pk64[k+1]<<(64-(nb_bits&63)));
+                    LOAD_UINT(t1, &pk64[8*k])
+                    LOAD_UINT(t2, &pk64[8*(k+1)])
+                    pk2[k]=(t1>>(nb_bits&63))
+                          ^(t2<<(64-(nb_bits&63)));
                 }
 
-                pk2[k]=pk64[k]>>(nb_bits&63);
+                LOAD_UINT(t1, &pk64[8*k])
+                pk2[k]=t1>>(nb_bits&63);
                 if(((nb_bits&63)+ir)>64)
                 {
-                    pk2[k]^=pk64[k+1]<<(64-(nb_bits&63));
+                    LOAD_UINT(t1, &pk64[8*(k+1)])
+                    pk2[k]^=t1<<(64-(nb_bits&63));
                 }
 
                 if(((nb_bits&63)+ir)>=64)
                 {
-                    ++pk64;
+                    pk64+=8;
                 }
             } else
             {
                 for(k=0;k<=iq;++k)
                 {
-                    pk2[k]=pk64[k];
+                    LOAD_UINT(t1, &pk64[8*k])
+                    pk2[k]=t1;
                 }
             }
 
-            pk64+=iq;
+            pk64+=8*iq;
             /* 0 padding on the last word */
             pk2[iq]&=(ONE64<<ir)-ONE64;
             pk2+=iq+1;

