--- upstream/avx2/invntt.S
+++ upstream-patched/avx2/invntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 .include "fq.inc"
 
@@ -210,7 +210,9 @@
 ret
 
 .global cdecl(invntt_avx)
+.global _cdecl(invntt_avx)
 cdecl(invntt_avx):
+_cdecl(invntt_avx):
 #consts
 vmovdqa         _16XQ*2(%rsi),%ymm0
 mov		%rsi,%rdx

