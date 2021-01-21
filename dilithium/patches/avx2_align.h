--- upstream/avx2/align.h
+++ upstream-patched/avx2/align.h
@@ -7,13 +7,13 @@
 #define ALIGNED_UINT8(N)        \
     union {                     \
         uint8_t coeffs[N];      \
-        __m256i vec[(N+31)/32]; \
+        __m256i vec[((N)+31)/32]; \
     }
 
 #define ALIGNED_INT32(N)        \
     union {                     \
         int32_t coeffs[N];      \
-        __m256i vec[(N+7)/8];   \
+        __m256i vec[((N)+7)/8];   \
     }
 
 #endif

