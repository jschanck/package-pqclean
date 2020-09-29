--- upstream/Reference_Implementation/sign/GeMSS128/src/predicate.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/predicate.c
@@ -43,7 +43,7 @@
         r|=a[i];
     }
     NORBITS_UINT(r);
-    return r;
+    return (int) r;
 }
 
 
@@ -66,7 +66,7 @@
         r|=a[i];
     }
     ORBITS_UINT(r);
-    return r;
+    return (int) r;
 }
 
 
@@ -115,7 +115,7 @@
         r|=a[i];
     }
     NORBITS_UINT(r);
-    return r;
+    return (int) r;
 }
 
 
@@ -162,7 +162,7 @@
         r|=a[i]^b[i];
     }
     NORBITS_UINT(r);
-    return r;
+    return (int) r;
 }
 
 
@@ -185,7 +185,7 @@
             return (a[i]<b[i]);
         }
     }
-    return (a[0]<b[0]);
+    return (int) (a[0]<b[0]);
 }
 
 
@@ -219,7 +219,7 @@
     {
         bo=i^d;
         NORBITS_UINT(bo);
-        mask|=(-bo)&CMP_LT_UINT(*a,*b);
+        mask|=(1+~bo)&CMP_LT_UINT(*a,*b);
         ++a;
         ++b;
     }

