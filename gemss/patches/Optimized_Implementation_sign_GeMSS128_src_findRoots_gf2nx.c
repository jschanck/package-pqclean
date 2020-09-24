--- upstream/Optimized_Implementation/sign/GeMSS128/src/findRoots_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/findRoots_gf2nx.c
@@ -81,12 +81,10 @@
         free(poly);
         free(poly2);
         return 0;
-    } else
-    {
-        /* poly2 is the gcd */
-        /* Here, it becomes monic */
-        convMonic_gf2nx(poly2,l);
     }
+    /* poly2 is the gcd */
+    /* Here, it becomes monic */
+    convMonic_gf2nx(poly2,l);
     free(poly);
 
 
@@ -174,17 +172,15 @@
         free(poly);
         free(poly2);
         return 0;
-    } else
-    {
-        /* poly2 is the gcd such that poly2 = a*x+b. */
-        /* The root is b*a^(-1). */
-        inv_gf2n(inv,poly2+NB_WORD_GFqn);
-        mul_gf2n(root,inv,poly2);
-
-        free(poly);
-        free(poly2);
-        return 1;
     }
+    /* poly2 is the gcd such that poly2 = a*x+b. */
+    /* The root is b*a^(-1). */
+    inv_gf2n(inv,poly2+NB_WORD_GFqn);
+    mul_gf2n(root,inv,poly2);
+
+    free(poly);
+    free(poly2);
+    return 1;
     #endif
 }
 

