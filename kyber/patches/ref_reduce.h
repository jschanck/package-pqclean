--- upstream/ref/reduce.h
+++ upstream-patched/ref/reduce.h
@@ -4,8 +4,8 @@
 #include <stdint.h>
 #include "params.h"
 
-#define MONT -1044 // 2^16 mod q
-#define QINV -3327 // q^-1 mod 2^16
+#define MONT (-1044) // 2^16 mod q
+#define QINV (-3327) // q^-1 mod 2^16
 
 #define montgomery_reduce KYBER_NAMESPACE(montgomery_reduce)
 int16_t montgomery_reduce(int32_t a);

