--- upstream/avx2/invntt.S
+++ upstream-patched/avx2/invntt.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "shuffle.inc"
 .include "fq.inc"
 
@@ -178,7 +178,9 @@
 
 .text
 .global cdecl(invntt_avx)
+.global _cdecl(invntt_avx)
 cdecl(invntt_avx):
+_cdecl(invntt_avx):
 vmovdqa         _16XQ*2(%rsi),%ymm0
 
 intt_levels0t5	0

