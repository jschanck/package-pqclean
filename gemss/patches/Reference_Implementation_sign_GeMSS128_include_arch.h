--- upstream/Reference_Implementation/sign/GeMSS128/include/arch.h
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/include/arch.h
@@ -26,18 +26,6 @@
 #define ZERO8 ((uint8_t)0)
 #define ONE8  ((uint8_t)1)
 
-/* 0x... */
-#define PRINT_X64(a) printf("0x%"PRIx64,a);
-#define PRINT_X32(a) printf("0x%"PRIx32,a);
-#define PRINT_X16(a) printf("0x%"PRIx16,a);
-#define PRINT_X8(a) printf("0x%"PRIx8,a);
-/* ... */
-#define PRINT_U64(a) printf("%"PRIx64,a);
-#define PRINT_U32(a) printf("%"PRIx32,a);
-#define PRINT_U16(a) printf("%"PRIx16,a);
-#define PRINT_U8(a) printf("%"PRIx8,a);
-
-
 /****************** Definition of an UINT  ******************/
 
 /* XXX For the moment, this parameter cannot be modified. XXX */
@@ -81,9 +69,6 @@
 /** Print an UINT. */
 #define PRINT_UINT(a) CONCAT(PRINT_X,NB_BITS_UINT)(a);
 
-
-
-
 /** A reserved variable to do a for loop on a buffer of UINT. */
 #define RESERVED_VARIABLE reserved_variable
 
@@ -103,6 +88,35 @@
         } \
     }
 
+/** Load a UINT from unsigned char * **/
+
+#define LOAD_UINT(a, p) \
+  (a) = (p)[7]; (a) <<= 8;\
+  (a) |= (p)[6]; (a) <<= 8;\
+  (a) |= (p)[5]; (a) <<= 8;\
+  (a) |= (p)[4]; (a) <<= 8;\
+  (a) |= (p)[3]; (a) <<= 8;\
+  (a) |= (p)[2]; (a) <<= 8;\
+  (a) |= (p)[1]; (a) <<= 8;\
+  (a) |= (p)[0];
+
+#define LOAD_UINT_ARRAY(a, p, N) \
+  FOR_LOOP(LOAD_UINT((a)[RESERVED_VARIABLE], &(p)[8*RESERVED_VARIABLE]), (N))
+
+/** Store a UINT to an unsigned char * **/
+#define STORE_UINT(p, a) \
+  (p)[0] = ((a) >> 0x00) & 0xff; \
+  (p)[1] = ((a) >> 0x08) & 0xff; \
+  (p)[2] = ((a) >> 0x10) & 0xff; \
+  (p)[3] = ((a) >> 0x18) & 0xff; \
+  (p)[4] = ((a) >> 0x20) & 0xff; \
+  (p)[5] = ((a) >> 0x28) & 0xff; \
+  (p)[6] = ((a) >> 0x30) & 0xff; \
+  (p)[7] = ((a) >> 0x38) & 0xff;
+
+#define STORE_UINT_ARRAY(a, p, N) \
+  FOR_LOOP(STORE_UINT(&(p)[8*RESERVED_VARIABLE], (a)[RESERVED_VARIABLE]), (N))
+
 
 
 /****************** C++ compatibility ******************/
@@ -226,7 +240,7 @@
 /* Only when set to 1, the installation of gf2x is required */
 /* Be careful because this library can be in variable-time and so vulnerable 
    to the timing attacks. */
-#define ENABLED_GF2X 1
+#define ENABLED_GF2X 0
 
 
 /********************* Allocation *********************/
@@ -237,7 +251,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Exit in the failure case. */
 #define VERIFY_ALLOC(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         exit(ERROR_ALLOC);\
     }
@@ -245,7 +259,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Return ERROR_ALLOC in the failure case. */
 #define VERIFY_ALLOC_RET(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         return(ERROR_ALLOC);\
     }
@@ -272,7 +286,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),16);
 #else
     #define ALIGNED16_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),16,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),16,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -280,7 +294,7 @@
 
 #define ALIGNED16_CALLOC(p,type,nmemb,size) \
             ALIGNED16_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size))
+            memset((void*)(p),0,(nmemb)*(size))
 
 
 /** Align the data on 32 bytes, useful for avx. */
@@ -291,7 +305,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),32);
 #else
     #define ALIGNED32_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),32,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),32,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -299,7 +313,7 @@
 
 #define ALIGNED32_CALLOC(p,type,nmemb,size) \
             ALIGNED32_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size));
+            memset((void*)(p),0,(nmemb)*(size));
 
 
 #define NO_ALIGNED_MALLOC(p,type,nmemb,size) p=(type)malloc((nmemb)*(size));

