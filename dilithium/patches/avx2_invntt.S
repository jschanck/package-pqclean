--- upstream/avx2/invntt.S
+++ upstream-patched/avx2/invntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 
 .macro butterfly l,h,zl0=1,zl1=1,zh0=2,zh1=2
@@ -222,7 +222,9 @@
 
 .text
 .global cdecl(invntt_avx)
+.global _cdecl(invntt_avx)
 cdecl(invntt_avx):
+_cdecl(invntt_avx):
 vmovdqa		_8XQ*4(%rsi),%ymm0
 
 levels0t5	0

