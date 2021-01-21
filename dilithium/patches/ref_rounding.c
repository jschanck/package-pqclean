--- upstream/ref/rounding.c
+++ upstream-patched/ref/rounding.c
@@ -89,14 +89,18 @@
     return a1;
 
 #if GAMMA2 == (Q-1)/32
-  if(a0 > 0)
+  if(a0 > 0) {
     return (a1 + 1) & 15;
-  else
-    return (a1 - 1) & 15;
+  }
+  return (a1 - 1) & 15;
 #elif GAMMA2 == (Q-1)/88
-  if(a0 > 0)
-    return (a1 == 43) ?  0 : a1 + 1;
-  else
-    return (a1 ==  0) ? 43 : a1 - 1;
+  if(a0 > 0) {
+    if(a1 == 43)
+      return 0;
+    return a1 + 1;
+  }
+  if(a1 == 0)
+    return 43;
+  return a1 - 1;
 #endif
 }

