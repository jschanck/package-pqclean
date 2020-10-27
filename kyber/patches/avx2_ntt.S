--- upstream/avx2/ntt.S
+++ upstream-patched/avx2/ntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 .include "fq.inc"
 
@@ -203,7 +203,9 @@
 ret
 
 .global cdecl(ntt_avx)
+.global _cdecl(ntt_avx)
 cdecl(ntt_avx):
+_cdecl(ntt_avx):
 #consts
 vmovdqa		_16XQ*2(%rsi),%ymm0
 mov		%rsi,%rdx

