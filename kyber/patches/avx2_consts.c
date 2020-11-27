--- upstream/avx2/consts.c
+++ upstream-patched/avx2/consts.c
@@ -3,59 +3,59 @@
 #include "consts.h"
 
 #define Q KYBER_Q
-#define MONT -1044 // 2^16 mod q
-#define QINV -3327 // q^-1 mod 2^16
+#define MONT (-1044) // 2^16 mod q
+#define QINV (-3327) // q^-1 mod 2^16
 #define V 20159 // floor(2^26/q + 0.5)
 #define FHI 1441 // mont^2/128
-#define FLO -10079 // qinv*FHI
+#define FLO (-10079) // qinv*FHI
 #define MONTSQHI 1353 // mont^2
 #define MONTSQLO 20553 // qinv*MONTSQHI
 #define MASK 4095
 #define SHIFT 32
 
-const qdata_t qdata = {{
-#define _16XQ 0
+const qdata_t qdata = {.coeffs={
+//#define _16XQ 0
   Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q,
 
-#define _16XQINV 16
+//#define _16XQINV 16
   QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
   QINV, QINV, QINV, QINV, QINV, QINV, QINV, QINV,
 
-#define _16XV 32
+//#define _16XV 32
   V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V,
 
-#define _16XFLO 48
+//#define _16XFLO 48
   FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
   FLO, FLO, FLO, FLO, FLO, FLO, FLO, FLO,
 
-#define _16XFHI 64
+//#define _16XFHI 64
   FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
   FHI, FHI, FHI, FHI, FHI, FHI, FHI, FHI,
 
-#define _16XMONTSQLO 80
+//#define _16XMONTSQLO 80
   MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
   MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
   MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
   MONTSQLO, MONTSQLO, MONTSQLO, MONTSQLO,
 
-#define _16XMONTSQHI 96
+//#define _16XMONTSQHI 96
   MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
   MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
   MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
   MONTSQHI, MONTSQHI, MONTSQHI, MONTSQHI,
 
-#define _16XMASK 112
+//#define _16XMASK 112
   MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
   MASK, MASK, MASK, MASK, MASK, MASK, MASK, MASK,
 
-#define _REVIDXB 128
+//#define _REVIDXB 128
   3854, 3340, 2826, 2312, 1798, 1284, 770, 256,
   3854, 3340, 2826, 2312, 1798, 1284, 770, 256,
 
-#define _REVIDXD 144
+//#define _REVIDXD 144
   7, 0, 6, 0, 5, 0, 4, 0, 3, 0, 2, 0, 1, 0, 0, 0,
 
-#define _ZETAS_EXP 160
+//#define _ZETAS_EXP 160
    31498,  31498,  31498,  31498,   -758,   -758,   -758,   -758,
     5237,   5237,   5237,   5237,   1397,   1397,   1397,   1397,
    14745,  14745,  14745,  14745,  14745,  14745,  14745,  14745,
@@ -115,7 +115,7 @@
     1097,    610,  -1285,    384,   -136,  -1335,    220,  -1659,
    -1530,    794,   -854,    478,   -308,    991,  -1460,   1628,
 
-#define _16XSHIFT 624
+//#define _16XSHIFT 624
   SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT,
   SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT
 }};

