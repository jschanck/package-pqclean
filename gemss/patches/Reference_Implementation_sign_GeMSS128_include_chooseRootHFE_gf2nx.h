--- upstream/Reference_Implementation/sign/GeMSS128/include/chooseRootHFE_gf2nx.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/chooseRootHFE_gf2nx.h
@@ -30,7 +30,7 @@
     #include "gf2nx.h"
 
     int PREFIX_NAME(chooseRootHFE_gf2nx)(gf2n root,
-                                         const complete_sparse_monic_gf2nx F,
+                                         complete_sparse_monic_gf2nx F,
                                          cst_gf2n U);
     #define chooseRootHFE_gf2nx PREFIX_NAME(chooseRootHFE_gf2nx)
 #endif

