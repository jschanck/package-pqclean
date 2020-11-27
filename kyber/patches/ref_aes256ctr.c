--- upstream/ref/aes256ctr.c
+++ upstream-patched/ref/aes256ctr.c
@@ -246,8 +246,8 @@
 		uint64_t a, b; \
 		a = (x); \
 		b = (y); \
-		(x) = (a & (uint64_t)cl) | ((b & (uint64_t)cl) << (s)); \
-		(y) = ((a & (uint64_t)ch) >> (s)) | (b & (uint64_t)ch); \
+		(x) = (a & (uint64_t)(cl)) | ((b & (uint64_t)(cl)) << (s)); \
+		(y) = ((a & (uint64_t)(ch)) >> (s)) | (b & (uint64_t)(ch)); \
 	} while (0)
 
 #define SWAP2(x, y)    SWAPN(0x5555555555555555, 0xAAAAAAAAAAAAAAAA,  1, x, y)
@@ -584,3 +584,4 @@
     nblocks--;
   }
 }
+

