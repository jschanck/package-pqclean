--- upstream/avx2/shuffle.S
+++ upstream-patched/avx2/shuffle.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 
 .text
@@ -41,7 +41,9 @@
 ret
 
 .global cdecl(nttunpack_avx)
+.global _cdecl(nttunpack_avx)
 cdecl(nttunpack_avx):
+_cdecl(nttunpack_avx):
 call		nttunpack128_avx
 add		$256,%rdi
 call		nttunpack128_avx

