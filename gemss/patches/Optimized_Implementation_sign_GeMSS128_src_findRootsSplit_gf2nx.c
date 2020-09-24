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
@@ -107,8 +115,11 @@
 void PREFIX_NAME(findRootsSplit_gf2nx)(vec_gf2n roots, gf2nx f,
                                        unsigned int deg)
 {
-    gf2nx poly_trace,f_cp,tmp_p;
-    gf2nx poly_frob;
+    UINT poly_frob[((HFEDeg<<1)-1)*NB_WORD_GFqn];
+    UINT p1[HFEDeg*NB_WORD_GFqn];
+    UINT p2[(HFEDeg+1)*NB_WORD_GFqn];
+    UINT *poly_trace=p1;
+    UINT *f_cp=p2;
     static_gf2n inv[NB_WORD_GFqn];
     unsigned int b,i,l,d;
 
@@ -119,11 +130,6 @@
         return;
     }
 
-    poly_frob=(UINT*)malloc(((deg<<1)-1)*NB_WORD_GFqn*sizeof(UINT));
-    /* poly_trace is modulo f, this degree is strictly less than deg */
-    poly_trace=(UINT*)malloc(deg*NB_WORD_GFqn*sizeof(UINT));
-    /* f_cp a copy of f */
-    f_cp=(UINT*)malloc((deg+1)*NB_WORD_GFqn*sizeof(UINT));
     do
     {
         /* Set poly_frob to zero */
@@ -151,16 +157,12 @@
         l=gcd_gf2nx(&b,f_cp,deg,poly_trace,d);
 
     } while((!l)||(l==deg));
-    free(poly_frob);
 
     if(b)
     {
-        tmp_p=poly_trace;
-        poly_trace=f_cp;
-        f_cp=tmp_p;
+        f_cp=poly_trace;
     }
     /* Here, f_cp is a non-trivial divisor of degree l */
-    free(poly_trace);
 
     /* f_cp is the gcd */
     /* Here, it becomes monic */
@@ -180,7 +182,6 @@
     /* f_cp is monic */
     /* We can apply findRootsSplit_gf2nx recursively */
     findRootsSplit_gf2nx(roots,f_cp,l);
-    free(f_cp);
 
     /* f is monic and f_cp is monic so Q is monic */
     /* We can apply findRootsSplit_gf2nx recursively */

