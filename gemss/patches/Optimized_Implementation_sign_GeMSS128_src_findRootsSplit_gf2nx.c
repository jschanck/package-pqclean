--- upstream/Optimized_Implementation/sign/GeMSS128/src/findRootsSplit_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/findRootsSplit_gf2nx.c
@@ -41,7 +41,15 @@
     i=1;
     /* (2^i) < deg does not require modular reduction by f */
     #if(HFEn<33)
-        const unsigned int min=(deg<(1U<<HFEn))?deg:HFEn;
+        const unsigned int min;
+        if (deg<(1U<<HFEn))
+        {
+          min=deg;
+        }
+        else
+        {
+          min=HFEn;
+        }
         while((1U<<i)<min)
     #else
         while((1U<<i)<deg)

