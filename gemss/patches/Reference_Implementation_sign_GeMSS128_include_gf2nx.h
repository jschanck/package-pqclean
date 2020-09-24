--- upstream/Reference_Implementation/sign/GeMSS128/include/gf2nx.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/gf2nx.h
@@ -119,7 +119,7 @@
 
 /* A structure with a special list to find the exponents of the monomials */
 typedef struct {
-    cst_sparse_monic_gf2nx poly;
+    UINT poly[NB_UINT_HFEPOLY];
     /* List of the successive differences of the exponents of the monomials of
        poly multiplied by NB_WORD_GFqn */
     unsigned int L[NB_COEFS_HFEPOLY];

