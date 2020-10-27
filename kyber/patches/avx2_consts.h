--- upstream/avx2/consts.h
+++ upstream-patched/avx2/consts.h
@@ -1,40 +1,21 @@
 #ifndef CONSTS_H
 #define CONSTS_H
 
+#include "cdecl.h"
+
 #include "params.h"
+#include <immintrin.h>
+#include <stdint.h>
 
-#define _16XQ            0
-#define _16XQINV        16
-#define _16XV           32
-#define _16XFLO         48
-#define _16XFHI         64
-#define _16XMONTSQLO    80
-#define _16XMONTSQHI    96
-#define _16XMASK       112
-#define _ZETAS_EXP     128
-#define _ZETAS_INV_EXP 528
-
-/* The C ABI on MacOS exports all symbols with a leading
- * underscore. This means that any symbols we refer to from
- * C files (functions) can't be found, and all symbols we
- * refer to from ASM also can't be found.
- *
- * This define helps us get around this
- */
-#ifdef __ASSEMBLER__
-#if defined(__WIN32__) || defined(__APPLE__)
-#define decorate(s) _##s
-#define cdecl2(s) decorate(s)
-#define cdecl(s) cdecl2(KYBER_NAMESPACE(_##s))
-#else
-#define cdecl(s) KYBER_NAMESPACE(_##s)
-#endif
-#endif
+#define ALIGNED_UINT16_T(N) \
+    union   {                   \
+        __m256i as_vec;         \
+        uint16_t as_arr[(N)];     \
+    }
 
-#ifndef __ASSEMBLER__
-#include <stdint.h>
-#define qdata KYBER_NAMESPACE(_qdata)
-extern const uint16_t qdata[];
-#endif
+typedef ALIGNED_UINT16_T(928) qdata_t;
+
+#define qdata KYBER_NAMESPACE(qdata)
+extern const qdata_t qdata;
 
 #endif

