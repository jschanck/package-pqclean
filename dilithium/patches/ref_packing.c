--- upstream/ref/packing.c
+++ upstream-patched/ref/packing.c
@@ -174,11 +174,12 @@
 
   k = 0;
   for(i = 0; i < K; ++i) {
-    for(j = 0; j < N; ++j)
+    for(j = 0; j < N; ++j) {
       if(h->vec[i].coeffs[j] != 0)
-        sig[k++] = j;
+        sig[k++] = (uint8_t) j;
+    }
 
-    sig[OMEGA + i] = k;
+    sig[OMEGA + i] = (uint8_t) k;
   }
 }
 
@@ -213,8 +214,9 @@
   /* Decode h */
   k = 0;
   for(i = 0; i < K; ++i) {
-    for(j = 0; j < N; ++j)
+    for(j = 0; j < N; ++j) {
       h->vec[i].coeffs[j] = 0;
+    }
 
     if(sig[OMEGA + i] < k || sig[OMEGA + i] > OMEGA)
       return 1;
@@ -229,9 +231,10 @@
   }
 
   /* Extra indices are zero for strong unforgeability */
-  for(j = k; j < OMEGA; ++j)
+  for(j = k; j < OMEGA; ++j) {
     if(sig[j])
       return 1;
+  }
 
   return 0;
 }

