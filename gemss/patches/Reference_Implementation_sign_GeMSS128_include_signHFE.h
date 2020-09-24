--- upstream/Reference_Implementation/sign/GeMSS128/include/signHFE.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/signHFE.h
@@ -7,6 +7,7 @@
 #include "gf2nx.h"
 #include "config_HFE.h"
 #include "matrix_gf2.h"
+#include "sizes_HFE.h"
 #include <stddef.h>
 
 
@@ -30,7 +31,10 @@
     #endif
 
     #if ENABLED_SEED_SK
-        UINT *sk_uncomp;
+        UINT sk_uncomp[NB_UINT_HFEVPOLY
+                       +(LTRIANGULAR_NV_SIZE<<1)
+                       +(LTRIANGULAR_N_SIZE<<1)+SIZE_VECTOR_t
+                       +MATRIXnv_SIZE+MATRIXn_SIZE];
     #endif
 } secret_key_HFE;
 

