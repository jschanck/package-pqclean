--- upstream/avx2/pointwise.S
+++ upstream-patched/avx2/pointwise.S
@@ -1,9 +1,11 @@
 #include "params.h"
-#include "consts.h"
+#include "cdecl.h"
 
 .text
 .global cdecl(pointwise_avx)
+.global _cdecl(pointwise_avx)
 cdecl(pointwise_avx):
+_cdecl(pointwise_avx):
 #consts
 vmovdqa		_8XQINV*4(%rcx),%ymm0
 vmovdqa		_8XQ*4(%rcx),%ymm1
@@ -135,7 +137,9 @@
 .endm
 
 .global cdecl(pointwise_acc_avx)
+.global _cdecl(pointwise_acc_avx)
 cdecl(pointwise_acc_avx):
+_cdecl(pointwise_acc_avx):
 #consts
 vmovdqa		_8XQINV*4(%rcx),%ymm0
 vmovdqa		_8XQ*4(%rcx),%ymm1

