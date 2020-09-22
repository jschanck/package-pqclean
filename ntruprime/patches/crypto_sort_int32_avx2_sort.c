--- upstream/crypto_sort/int32/avx2/sort.c
+++ upstream-patched/crypto_sort/int32/avx2/sort.c
@@ -1,9 +1,7 @@
-#include "crypto_sort.h"
-#include "crypto_int32.h"
-#define int32 crypto_int32
-#include <immintrin.h>
+#include "crypto_sort_int32.h"
 
-#include "int32_minmax_x86.inc"
+#include <immintrin.h>
+#define int32 int32_t
 
 typedef __m256i int32x8;
 #define int32x8_load(z) _mm256_loadu_si256((__m256i *) (z))
@@ -13,17 +11,26 @@
 
 #define int32x8_MINMAX(a,b) \
 do { \
-  int32x8 c = int32x8_min(a,b); \
-  b = int32x8_max(a,b); \
-  a = c; \
+  int32x8 c = int32x8_min((a),(b)); \
+  (b) = int32x8_max((a),(b)); \
+  (a) = c; \
 } while(0)
 
-__attribute__((noinline))
+static inline void int32_MINMAX(int32 *a, int32 *b) {
+    int32 ab = *b ^ *a;
+    int32 c = (int32)((int64_t)*b - (int64_t)*a);
+    c ^= ab & (c ^ *b);
+    c >>= 31;
+    c &= ab;
+    *a ^= c;
+    *b ^= c;
+}
+
 static void minmax_vector(int32 *x,int32 *y,long long n)
 {
   if (n < 8) {
     while (n > 0) {
-      int32_MINMAX(*x,*y);
+      int32_MINMAX(x,y);
       ++x;
       ++y;
       --n;
@@ -51,7 +58,6 @@
 }
 
 /* stages 8,4,2,1 of size-16 bitonic merging */
-__attribute__((noinline))
 static void merge16_finish(int32 *x,int32x8 x0,int32x8 x1,int flagdown)
 {
   int32x8 b0,b1,c0,c1,mask;
@@ -93,7 +99,6 @@
 }
 
 /* stages 64,32 of bitonic merging; n is multiple of 128 */
-__attribute__((noinline))
 static void int32_twostages_32(int32 *x,long long n)
 {
   long long i;
@@ -121,12 +126,11 @@
 }
 
 /* stages 4q,2q,q of bitonic merging */
-__attribute__((noinline))
 static long long int32_threestages(int32 *x,long long n,long long q)
 {
   long long k,i;
 
-  for (k = 0;k + 8*q <= n;k += 8*q)
+  for (k = 0;k + 8*q <= n;k += 8*q) {
     for (i = k;i < k + q;i += 8) {
       int32x8 x0 = int32x8_load(&x[i]);
       int32x8 x1 = int32x8_load(&x[i+q]);
@@ -159,14 +163,16 @@
       int32x8_store(&x[i+6*q],x6);
       int32x8_store(&x[i+7*q],x7);
     }
+  }
 
   return k;
 }
 
 /* n is a power of 2; n >= 8; if n == 8 then flagdown */
-__attribute__((noinline))
+// NOLINTNEXTLINE(google-readability-function-size)
 static void int32_sort_2power(int32 *x,long long n,int flagdown)
-{ long long p,q,i,j,k;
+{
+  long long p,q,i,j,k;
   int32x8 mask;
 
   if (n == 8) {
@@ -181,29 +187,29 @@
 
     /* odd-even sort instead of bitonic sort */
 
-    int32_MINMAX(x1,x0);
-    int32_MINMAX(x3,x2);
-    int32_MINMAX(x2,x0);
-    int32_MINMAX(x3,x1);
-    int32_MINMAX(x2,x1);
-
-    int32_MINMAX(x5,x4);
-    int32_MINMAX(x7,x6);
-    int32_MINMAX(x6,x4);
-    int32_MINMAX(x7,x5);
-    int32_MINMAX(x6,x5);
-
-    int32_MINMAX(x4,x0);
-    int32_MINMAX(x6,x2);
-    int32_MINMAX(x4,x2);
-
-    int32_MINMAX(x5,x1);
-    int32_MINMAX(x7,x3);
-    int32_MINMAX(x5,x3);
-
-    int32_MINMAX(x2,x1);
-    int32_MINMAX(x4,x3);
-    int32_MINMAX(x6,x5);
+    int32_MINMAX(&x1,&x0);
+    int32_MINMAX(&x3,&x2);
+    int32_MINMAX(&x2,&x0);
+    int32_MINMAX(&x3,&x1);
+    int32_MINMAX(&x2,&x1);
+
+    int32_MINMAX(&x5,&x4);
+    int32_MINMAX(&x7,&x6);
+    int32_MINMAX(&x6,&x4);
+    int32_MINMAX(&x7,&x5);
+    int32_MINMAX(&x6,&x5);
+
+    int32_MINMAX(&x4,&x0);
+    int32_MINMAX(&x6,&x2);
+    int32_MINMAX(&x4,&x2);
+
+    int32_MINMAX(&x5,&x1);
+    int32_MINMAX(&x7,&x3);
+    int32_MINMAX(&x5,&x3);
+
+    int32_MINMAX(&x2,&x1);
+    int32_MINMAX(&x4,&x3);
+    int32_MINMAX(&x6,&x5);
 
     x[0] = x0;
     x[1] = x1;
@@ -387,7 +393,7 @@
       }
       if (q == 32) {
         q = 8;
-        for (k = 0;k < n;k += 8*q)
+        for (k = 0;k < n;k += 8*q) {
           for (i = k;i < k + q;i += 8) {
             int32x8 x0 = int32x8_load(&x[i]);
             int32x8 x1 = int32x8_load(&x[i+q]);
@@ -420,11 +426,12 @@
             int32x8_store(&x[i+6*q],x6);
             int32x8_store(&x[i+7*q],x7);
           }
+        }
         q = 4;
       }
       if (q == 16) {
         q = 8;
-        for (k = 0;k < n;k += 4*q)
+        for (k = 0;k < n;k += 4*q) {
           for (i = k;i < k + q;i += 8) {
             int32x8 x0 = int32x8_load(&x[i]);
             int32x8 x1 = int32x8_load(&x[i+q]);
@@ -441,9 +448,10 @@
             int32x8_store(&x[i+2*q],x2);
             int32x8_store(&x[i+3*q],x3);
           }
+        }
         q = 4;
       }
-      if (q == 8)
+      if (q == 8) {
         for (k = 0;k < n;k += q + q) {
           int32x8 x0 = int32x8_load(&x[k]);
           int32x8 x1 = int32x8_load(&x[k+q]);
@@ -453,10 +461,14 @@
           int32x8_store(&x[k],x0);
           int32x8_store(&x[k+q],x1);
         }
-  
+      }
+
       q = n>>3;
-      flip = (p<<1 == q);
-      flipflip = !flip;
+      flip = 0;
+      if (p << 1 == q) {
+        flip = 1;
+      }
+      flipflip = 1 - flip;
       for (j = 0;j < q;j += p + p) {
         for (k = j;k < j + p + p;k += p) {
           for (i = k;i < k + p;i += 8) {
@@ -572,7 +584,7 @@
     }
     while (q >= 16) {
       q >>= 1;
-      for (j = 0;j < n;j += 4*q)
+      for (j = 0;j < n;j += 4*q) {
         for (k = j;k < j + q;k += 8) {
           int32x8 x0 = int32x8_load(&x[k]);
           int32x8 x1 = int32x8_load(&x[k+q]);
@@ -589,6 +601,7 @@
           int32x8_store(&x[k+2*q],x2);
           int32x8_store(&x[k+3*q],x3);
         }
+      }
       q >>= 1;
     }
     if (q == 8) {
@@ -743,7 +756,7 @@
   q = n>>4;
   while (q >= 128 || q == 32) {
     q >>= 2;
-    for (j = 0;j < n;j += 8*q)
+    for (j = 0;j < n;j += 8*q) {
       for (i = j;i < j + q;i += 8) {
         int32x8 x0 = int32x8_load(&x[i]);
         int32x8 x1 = int32x8_load(&x[i+q]);
@@ -774,11 +787,12 @@
         int32x8_store(&x[i+6*q],x6);
         int32x8_store(&x[i+7*q],x7);
       }
+    }
     q >>= 1;
   }
   while (q >= 16) {
     q >>= 1;
-    for (j = 0;j < n;j += 4*q)
+    for (j = 0;j < n;j += 4*q) {
       for (i = j;i < j + q;i += 8) {
         int32x8 x0 = int32x8_load(&x[i]);
         int32x8 x1 = int32x8_load(&x[i+q]);
@@ -793,9 +807,10 @@
         int32x8_store(&x[i+2*q],x2);
         int32x8_store(&x[i+3*q],x3);
       }
+    }
     q >>= 1;
   }
-  if (q == 8)
+  if (q == 8) {
     for (j = 0;j < n;j += q + q) {
       int32x8 x0 = int32x8_load(&x[j]);
       int32x8 x1 = int32x8_load(&x[j+q]);
@@ -803,6 +818,7 @@
       int32x8_store(&x[j],x0);
       int32x8_store(&x[j+q],x1);
     }
+  }
 
   q = n>>3;
   for (i = 0;i < q;i += 8) {
@@ -878,50 +894,51 @@
 }
 
 static void int32_sort(int32 *x,long long n)
-{ long long q,i,j;
+{
+  long long q,i,j;
 
   if (n <= 8) {
     if (n == 8) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
-      int32_MINMAX(x[2],x[3]);
-      int32_MINMAX(x[3],x[4]);
-      int32_MINMAX(x[4],x[5]);
-      int32_MINMAX(x[5],x[6]);
-      int32_MINMAX(x[6],x[7]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
+      int32_MINMAX(&x[2],&x[3]);
+      int32_MINMAX(&x[3],&x[4]);
+      int32_MINMAX(&x[4],&x[5]);
+      int32_MINMAX(&x[5],&x[6]);
+      int32_MINMAX(&x[6],&x[7]);
     }
     if (n >= 7) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
-      int32_MINMAX(x[2],x[3]);
-      int32_MINMAX(x[3],x[4]);
-      int32_MINMAX(x[4],x[5]);
-      int32_MINMAX(x[5],x[6]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
+      int32_MINMAX(&x[2],&x[3]);
+      int32_MINMAX(&x[3],&x[4]);
+      int32_MINMAX(&x[4],&x[5]);
+      int32_MINMAX(&x[5],&x[6]);
     }
     if (n >= 6) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
-      int32_MINMAX(x[2],x[3]);
-      int32_MINMAX(x[3],x[4]);
-      int32_MINMAX(x[4],x[5]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
+      int32_MINMAX(&x[2],&x[3]);
+      int32_MINMAX(&x[3],&x[4]);
+      int32_MINMAX(&x[4],&x[5]);
     }
     if (n >= 5) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
-      int32_MINMAX(x[2],x[3]);
-      int32_MINMAX(x[3],x[4]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
+      int32_MINMAX(&x[2],&x[3]);
+      int32_MINMAX(&x[3],&x[4]);
     }
     if (n >= 4) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
-      int32_MINMAX(x[2],x[3]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
+      int32_MINMAX(&x[2],&x[3]);
     }
     if (n >= 3) {
-      int32_MINMAX(x[0],x[1]);
-      int32_MINMAX(x[1],x[2]);
+      int32_MINMAX(&x[0],&x[1]);
+      int32_MINMAX(&x[1],&x[2]);
     }
     if (n >= 2) {
-      int32_MINMAX(x[0],x[1]);
+      int32_MINMAX(&x[0],&x[1]);
     }
     return;
   }
@@ -938,9 +955,9 @@
   if (q <= 128) { /* n <= 256 */
     int32x8 y[32];
     for (i = q>>3;i < q>>2;++i) y[i] = _mm256_set1_epi32(0x7fffffff);
-    for (i = 0;i < n;++i) i[(int32 *) y] = x[i];
+    for (i = 0;i < n;++i) ((int32 *) y)[i] = x[i];
     int32_sort_2power((int32 *) y,2*q,0);
-    for (i = 0;i < n;++i) x[i] = i[(int32 *) y];
+    for (i = 0;i < n;++i) x[i] = ((int32 *) y)[i];
     return;
   }
 
@@ -1156,32 +1173,32 @@
   }
   minmax_vector(x + j,x + j + 8,n - 8 - j);
   if (j + 8 <= n) {
-    int32_MINMAX(x[j],x[j+4]);
-    int32_MINMAX(x[j+1],x[j+5]);
-    int32_MINMAX(x[j+2],x[j+6]);
-    int32_MINMAX(x[j+3],x[j+7]);
-    int32_MINMAX(x[j],x[j+2]);
-    int32_MINMAX(x[j+1],x[j+3]);
-    int32_MINMAX(x[j],x[j+1]);
-    int32_MINMAX(x[j+2],x[j+3]);
-    int32_MINMAX(x[j+4],x[j+6]);
-    int32_MINMAX(x[j+5],x[j+7]);
-    int32_MINMAX(x[j+4],x[j+5]);
-    int32_MINMAX(x[j+6],x[j+7]);
+    int32_MINMAX(&x[j],&x[j+4]);
+    int32_MINMAX(&x[j+1],&x[j+5]);
+    int32_MINMAX(&x[j+2],&x[j+6]);
+    int32_MINMAX(&x[j+3],&x[j+7]);
+    int32_MINMAX(&x[j],&x[j+2]);
+    int32_MINMAX(&x[j+1],&x[j+3]);
+    int32_MINMAX(&x[j],&x[j+1]);
+    int32_MINMAX(&x[j+2],&x[j+3]);
+    int32_MINMAX(&x[j+4],&x[j+6]);
+    int32_MINMAX(&x[j+5],&x[j+7]);
+    int32_MINMAX(&x[j+4],&x[j+5]);
+    int32_MINMAX(&x[j+6],&x[j+7]);
     j += 8;
   }
   minmax_vector(x + j,x + j + 4,n - 4 - j);
   if (j + 4 <= n) {
-    int32_MINMAX(x[j],x[j+2]);
-    int32_MINMAX(x[j+1],x[j+3]);
-    int32_MINMAX(x[j],x[j+1]);
-    int32_MINMAX(x[j+2],x[j+3]);
+    int32_MINMAX(&x[j],&x[j+2]);
+    int32_MINMAX(&x[j+1],&x[j+3]);
+    int32_MINMAX(&x[j],&x[j+1]);
+    int32_MINMAX(&x[j+2],&x[j+3]);
     j += 4;
   }
   if (j + 3 <= n)
-    int32_MINMAX(x[j],x[j+2]);
+    int32_MINMAX(&x[j],&x[j+2]);
   if (j + 2 <= n)
-    int32_MINMAX(x[j],x[j+1]);
+    int32_MINMAX(&x[j],&x[j+1]);
 }
 
 void crypto_sort(void *array,long long n)

