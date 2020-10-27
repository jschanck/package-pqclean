--- upstream/avx2/basemul.S
+++ upstream-patched/avx2/basemul.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 
 .macro schoolbook off
 vmovdqa		_16XQINV*2(%rcx),%ymm0
@@ -84,7 +84,9 @@
 
 .text
 .global cdecl(basemul_avx)
+.global _cdecl(basemul_avx)
 cdecl(basemul_avx):
+_cdecl(basemul_avx):
 mov		%rsp,%r8
 and		$-32,%rsp
 sub		$32,%rsp

