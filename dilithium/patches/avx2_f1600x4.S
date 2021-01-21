--- upstream/avx2/f1600x4.S
+++ upstream-patched/avx2/f1600x4.S
@@ -2,7 +2,7 @@
  * for Sphincs+ (https://github.com/sphincs/sphincsplus/pull/14/),
  * but uses vpshufb for byte-granular rotations as in the Keccak Code Package. */
 
-#include "fips202x4.h"
+#include "cdecl.h"
 
 .data
 .p2align 5
@@ -13,7 +13,9 @@
 
 .text
 .global cdecl(f1600x4)
+.global _cdecl(f1600x4)
 cdecl(f1600x4):
+_cdecl(f1600x4):
 vmovdqa		rho8(%rip), %ymm0
 movq		$6, %rax
 looptop:

