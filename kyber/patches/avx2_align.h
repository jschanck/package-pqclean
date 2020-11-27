--- upstream/avx2/align.h
+++ upstream-patched/avx2/align.h
@@ -6,14 +6,14 @@
 
 #define ALIGNED_UINT8(N)        \
     union {                     \
-        uint8_t coeffs[N];      \
-        __m256i vec[(N+31)/32]; \
+        uint8_t coeffs[(N)];      \
+        __m256i vec[((N)+31)/32]; \
     }
 
 #define ALIGNED_INT16(N)        \
     union {                     \
-        int16_t coeffs[N];      \
-        __m256i vec[(N+15)/16]; \
+        int16_t coeffs[(N)];      \
+        __m256i vec[((N)+15)/16]; \
     }
 
 #endif

