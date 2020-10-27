--- upstream/avx2/basemul.S
+++ upstream-patched/avx2/basemul.S
@@ -1,5 +1,5 @@
+#include "cdecl.h"
 #include "params.h"
-#include "consts.h"
 
 .macro schoolbook off,sign
 #load
@@ -173,7 +173,9 @@
 ret
 
 .global cdecl(basemul_acc_avx)
+.global _cdecl(basemul_acc_avx)
 cdecl(basemul_acc_avx):
+_cdecl(basemul_acc_avx):
 #consts
 vmovdqa		_16XQ*2(%rcx),%ymm0
 vmovdqa		_16XQINV*2(%rcx),%ymm1
@@ -223,7 +225,9 @@
 ret
 
 .global cdecl(basemul_avx)
+.global _cdecl(basemul_avx)
 cdecl(basemul_avx):
+_cdecl(basemul_avx):
 #consts
 vmovdqa		_16XQ*2(%rcx),%ymm0
 vmovdqa		_16XQINV*2(%rcx),%ymm1

