--- upstream/avx2/ntt.S
+++ upstream-patched/avx2/ntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 
 .macro mul rh0,rh1,rh2,rh3,zl0=15,zl1=15,zh0=2,zh1=2
@@ -177,7 +177,9 @@
 
 .text
 .global cdecl(ntt_avx)
+.global _cdecl(ntt_avx)
 cdecl(ntt_avx):
+_cdecl(ntt_avx):
 vmovdqa		_16XQ*2(%rsi),%ymm0
 
 level0		0

