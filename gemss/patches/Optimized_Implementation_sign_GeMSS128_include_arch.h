--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/include/arch.h
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/include/arch.h
@@ -6,6 +6,8 @@
 #include <inttypes.h>
 #include "macro.h"
 
+#include <immintrin.h>
+
 
 /****************** uintXX_t for compatibility  ******************/
 
@@ -160,60 +162,44 @@
 
 
 #ifdef __SSE__
-    #include <xmmintrin.h>
-    /** To use sse. */
     #define ENABLED_SSE
 #endif
 
 #ifdef __SSE2__
-    #include <emmintrin.h>
-    /** To use sse2. */
     #define ENABLED_SSE2
 #endif
 
 #ifdef __SSSE3__
-    #include <tmmintrin.h>
-    /** To use ssse3. */
     #define ENABLED_SSSE3
 #endif
 
 #ifdef __SSE4_1__
-    #include <smmintrin.h>
-    /** To use sse4.1. */
     #define ENABLED_SSE4_1
 #endif
 
 #ifdef __AVX__
-    #include <immintrin.h>
-    /** To use avx. */
     #define ENABLED_AVX
 #endif
 
 #ifdef __AVX2__
-    /** To use avx2. */
     #define ENABLED_AVX2
 #endif
 
 #if (defined(__PCLMUL__) && defined(ENABLED_SSE))
-    #include <wmmintrin.h>
-    /** To use multiplication in binary field with PCLMULQDQ and sse. */
     #define ENABLED_PCLMUL
 #endif
 
 #if (defined(ENABLED_PCLMUL) && defined(ENABLED_SSE2))
-    #include <wmmintrin.h>
     /** To use multiplication in binary field with PCLMULQDQ and sse2. */
     #define ENABLED_PCLMUL_SSE2
 #endif
 
 #if (defined(ENABLED_PCLMUL) && defined(ENABLED_AVX2))
-    #include <wmmintrin.h>
     /** To use multiplication in binary field with PCLMULQDQ and avx2. */
     #define ENABLED_PCLMUL_AVX2
 #endif
 
 #ifdef __POPCNT__
-    #include <nmmintrin.h>
     /** Improve the computation of the number of bits set to 1 in a 64-bit 
      *  or 32-bit integer. */
     #define ENABLED_POPCNT

