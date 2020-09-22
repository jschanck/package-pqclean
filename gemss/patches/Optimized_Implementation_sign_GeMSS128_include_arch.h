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
@@ -237,7 +223,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Exit in the failure case. */
 #define VERIFY_ALLOC(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         exit(ERROR_ALLOC);\
     }
@@ -245,7 +231,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Return ERROR_ALLOC in the failure case. */
 #define VERIFY_ALLOC_RET(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         return(ERROR_ALLOC);\
     }
@@ -272,7 +258,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),16);
 #else
     #define ALIGNED16_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),16,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),16,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -280,7 +266,7 @@
 
 #define ALIGNED16_CALLOC(p,type,nmemb,size) \
             ALIGNED16_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size))
+            memset((void*)(p),0,(nmemb)*(size))
 
 
 /** Align the data on 32 bytes, useful for avx. */
@@ -291,7 +277,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),32);
 #else
     #define ALIGNED32_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),32,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),32,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -299,7 +285,7 @@
 
 #define ALIGNED32_CALLOC(p,type,nmemb,size) \
             ALIGNED32_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size));
+            memset((void*)(p),0,(nmemb)*(size));
 
 
 #define NO_ALIGNED_MALLOC(p,type,nmemb,size) p=(type)malloc((nmemb)*(size));

