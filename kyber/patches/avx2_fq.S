--- upstream/avx2/fq.S
+++ upstream-patched/avx2/fq.S
@@ -1,4 +1,4 @@
-#include "consts.h"
+#include "cdecl.h"
 .include "fq.inc"
 
 .text
@@ -35,7 +35,9 @@
 ret
 
 .global cdecl(reduce_avx)
+.global _cdecl(reduce_avx)
 cdecl(reduce_avx):
+_cdecl(reduce_avx):
 #consts
 vmovdqa		_16XQ*2(%rsi),%ymm0
 vmovdqa		_16XV*2(%rsi),%ymm1
@@ -77,7 +79,9 @@
 ret
 
 .global cdecl(tomont_avx)
+.global _cdecl(tomont_avx)
 cdecl(tomont_avx):
+_cdecl(tomont_avx):
 #consts
 vmovdqa		_16XQ*2(%rsi),%ymm0
 vmovdqa		_16XMONTSQLO*2(%rsi),%ymm1

