--- upstream/ref/reduce.h
+++ upstream-patched/ref/reduce.h
@@ -4,7 +4,7 @@
 #include <stdint.h>
 #include "params.h"
 
-#define MONT -4186625 // 2^32 % Q
+#define MONT (-4186625) // 2^32 % Q
 #define QINV 58728449 // q^(-1) mod 2^32
 
 #define montgomery_reduce DILITHIUM_NAMESPACE(montgomery_reduce)

