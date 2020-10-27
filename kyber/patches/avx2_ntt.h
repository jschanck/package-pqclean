--- upstream/avx2/ntt.h
+++ upstream-patched/avx2/ntt.h
@@ -2,27 +2,27 @@
 #define NTT_H
 
 #include <stdint.h>
-#include "params.h"
+#include "consts.h"
 
 #define ntt_avx KYBER_NAMESPACE(_ntt_avx)
-void ntt_avx(int16_t *r, const int16_t *qdata);
+void ntt_avx(int16_t *r, const qdata_t *qdata);
 #define invntt_avx KYBER_NAMESPACE(_invntt_avx)
-void invntt_avx(int16_t *r, const int16_t *qdata);
+void invntt_avx(int16_t *r, const qdata_t *qdata);
 
 #define nttpack_avx KYBER_NAMESPACE(_nttpack_avx)
-void nttpack_avx(int16_t *r, const int16_t *qdata);
+void nttpack_avx(int16_t *r, const qdata_t *qdata);
 #define nttunpack_avx KYBER_NAMESPACE(_nttunpack_avx)
-void nttunpack_avx(int16_t *r, const int16_t *qdata);
+void nttunpack_avx(int16_t *r, const qdata_t *qdata);
 
 #define basemul_avx KYBER_NAMESPACE(_basemul_avx)
 void basemul_avx(int16_t *r,
                  const int16_t *a,
                  const int16_t *b,
-                 const int16_t *qdata);
+                 const qdata_t *qdata);
 
 #define ntttobytes_avx KYBER_NAMESPACE(_ntttobytes_avx)
-void ntttobytes_avx(uint8_t *r, const int16_t *a, const int16_t *qdata);
+void ntttobytes_avx(uint8_t *r, const int16_t *a, const qdata_t *qdata);
 #define nttfrombytes_avx KYBER_NAMESPACE(_nttfrombytes_avx)
-void nttfrombytes_avx(int16_t *r, const uint8_t *a, const int16_t *qdata);
+void nttfrombytes_avx(int16_t *r, const uint8_t *a, const qdata_t *qdata);
 
 #endif

