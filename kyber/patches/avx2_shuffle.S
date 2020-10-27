--- upstream/avx2/shuffle.S
+++ upstream-patched/avx2/shuffle.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "fq.inc"
 .include "shuffle.inc"
 
@@ -92,7 +92,9 @@
 ret
 
 .global cdecl(nttunpack_avx)
+.global _cdecl(nttunpack_avx)
 cdecl(nttunpack_avx):
+_cdecl(nttunpack_avx):
 call		nttunpack128_avx
 add		$256,%rdi
 call		nttunpack128_avx
@@ -169,7 +171,9 @@
 ret
 
 .global cdecl(ntttobytes_avx)
+.global _cdecl(ntttobytes_avx)
 cdecl(ntttobytes_avx):
+_cdecl(ntttobytes_avx):
 #consts
 vmovdqa		_16XQ*2(%rdx),%ymm0
 call		ntttobytes128_avx
@@ -245,7 +249,9 @@
 ret
 
 .global cdecl(nttfrombytes_avx)
+.global _cdecl(nttfrombytes_avx)
 cdecl(nttfrombytes_avx):
+_cdecl(nttfrombytes_avx):
 #consts
 vmovdqa		_16XMASK*2(%rdx),%ymm0
 call		nttfrombytes128_avx

