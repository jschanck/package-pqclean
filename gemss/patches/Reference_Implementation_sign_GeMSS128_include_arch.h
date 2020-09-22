--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/arch.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/arch.h
@@ -237,7 +237,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Exit in the failure case. */
 #define VERIFY_ALLOC(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         exit(ERROR_ALLOC);\
     }
@@ -245,7 +245,7 @@
 /** Verify if the allocation by malloc or calloc succeeds. 
  *  Return ERROR_ALLOC in the failure case. */
 #define VERIFY_ALLOC_RET(p) \
-    if(!p) \
+    if(!(p)) \
     {\
         return(ERROR_ALLOC);\
     }
@@ -272,7 +272,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),16);
 #else
     #define ALIGNED16_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),16,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),16,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -280,7 +280,7 @@
 
 #define ALIGNED16_CALLOC(p,type,nmemb,size) \
             ALIGNED16_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size))
+            memset((void*)(p),0,(nmemb)*(size))
 
 
 /** Align the data on 32 bytes, useful for avx. */
@@ -291,7 +291,7 @@
                 p=(type)_mm_malloc((nmemb)*(size),32);
 #else
     #define ALIGNED32_MALLOC(p,type,nmemb,size) \
-                if(posix_memalign((void**)(&p),32,(nmemb)*(size)))\
+                if(posix_memalign((void**)(&(p)),32,(nmemb)*(size)))\
                 {\
                     exit(1);\
                 }
@@ -299,7 +299,7 @@
 
 #define ALIGNED32_CALLOC(p,type,nmemb,size) \
             ALIGNED32_MALLOC(p,type,nmemb,size);\
-            memset((void*)p,0,(nmemb)*(size));
+            memset((void*)(p),0,(nmemb)*(size));
 
 
 #define NO_ALIGNED_MALLOC(p,type,nmemb,size) p=(type)malloc((nmemb)*(size));

