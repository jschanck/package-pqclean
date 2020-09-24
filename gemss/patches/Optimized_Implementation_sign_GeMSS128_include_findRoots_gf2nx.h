--- upstream/Optimized_Implementation/sign/GeMSS128/include/findRoots_gf2nx.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/findRoots_gf2nx.h
@@ -19,14 +19,14 @@
     convHFEpolynomialSparseToDense_gf2nx(poly2,F);\
     /* Initialize to F-U */\
     add2_gf2n(poly2,U);\
-    l=gcd_gf2nx(&i,poly2,d2,poly,l);
+    (l)=gcd_gf2nx(&(i),poly2,d2,poly,l);
 
 
-int PREFIX_NAME(findRootsHFE_gf2nx)(vec_gf2n* roots,
-                                    const complete_sparse_monic_gf2nx F,
+int PREFIX_NAME(findRootsHFE_gf2nx)(vec_gf2n roots,
+                                    complete_sparse_monic_gf2nx F,
                                     cst_gf2n U);
 int PREFIX_NAME(findUniqRootHFE_gf2nx)(gf2n root,
-                                       const complete_sparse_monic_gf2nx F,
+                                       complete_sparse_monic_gf2nx F,
                                        cst_gf2n U);
 #define findRootsHFE_gf2nx PREFIX_NAME(findRootsHFE_gf2nx)
 #define findUniqRootHFE_gf2nx PREFIX_NAME(findUniqRootHFE_gf2nx)

