--- upstream/avx2/ntt.S
+++ upstream-patched/avx2/ntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 
 .macro butterfly l,h,zl0=1,zl1=1,zh0=2,zh1=2
@@ -180,7 +180,9 @@
 
 .text
 .global cdecl(ntt_avx)
+.global _cdecl(ntt_avx)
 cdecl(ntt_avx):
+_cdecl(ntt_avx):
 vmovdqa		_8XQ*4(%rsi),%ymm0
 
 levels0t1	0

