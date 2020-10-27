--- upstream/avx2/reduce.h
+++ upstream-patched/avx2/reduce.h
@@ -1,14 +1,14 @@
 #ifndef REDUCE_H
 #define REDUCE_H
 
-#include "params.h"
+#include "consts.h"
 #include <stdint.h>
 
 #define reduce_avx KYBER_NAMESPACE(_reduce_avx)
-int16_t reduce_avx(int16_t *r, const uint16_t *qdata);
+int16_t reduce_avx(int16_t *r, const qdata_t *qdata);
 #define csubq_avx KYBER_NAMESPACE(_csubq_avx)
-int16_t csubq_avx(int16_t *r, const uint16_t *qdata);
+int16_t csubq_avx(int16_t *r, const qdata_t *qdata);
 #define tomont_avx KYBER_NAMESPACE(_tomont_avx)
-int16_t tomont_avx(int16_t *r, const uint16_t *qdata);
+int16_t tomont_avx(int16_t *r, const qdata_t *qdata);
 
 #endif

