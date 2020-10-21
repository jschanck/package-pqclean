--- upstream/crypto_sign/falcon512dyn/ref/inner.h
+++ upstream-patched/crypto_sign/falcon512dyn/ref/inner.h
@@ -73,127 +73,12 @@
  *    function does nothing, so it can be called systematically.
  */
 
-#define FALCON_FPEMU          1
-#define FALCON_FPNATIVE       0
-#define FALCON_ASM_CORTEXM4   0
-#define FALCON_AVX2           0
-#define FALCON_LE             0
-#define FALCON_UNALIGNED      0
 
 #include <stdint.h>
 #include <stdlib.h>
 #include <string.h>
 
 
-/*
- * On MSVC, disable warning about applying unary minus on an unsigned
- * type: this is perfectly defined standard behaviour and we do it
- * quite often.
- */
-#if defined _MSC_VER && _MSC_VER
-#pragma warning( disable : 4146 )
-#endif
-
-
-#if defined __i386__ || defined _M_IX86 \
-	|| defined __x86_64__ || defined _M_X64 || \
-	(defined _ARCH_PWR8 && \
-		(defined __LITTLE_ENDIAN || defined __LITTLE_ENDIAN__))
-
-#ifndef FALCON_LE
-#define FALCON_LE     1
-#endif
-#ifndef FALCON_UNALIGNED
-#define FALCON_UNALIGNED   1
-#endif
-
-#elif defined FALCON_ASM_CORTEXM4 && FALCON_ASM_CORTEXM4
-
-#ifndef FALCON_LE
-#define FALCON_LE     1
-#endif
-#ifndef FALCON_UNALIGNED
-#define FALCON_UNALIGNED   0
-#endif
-
-#elif (defined __LITTLE_ENDIAN__ && __LITTLE_ENDIAN__) \
-	|| (defined __BYTE_ORDER__ && defined __ORDER_LITTLE_ENDIAN__ \
-		&& __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
-
-#ifndef FALCON_LE
-#define FALCON_LE     1
-#endif
-#ifndef FALCON_UNALIGNED
-#define FALCON_UNALIGNED   0
-#endif
-
-#else
-
-#ifndef FALCON_LE
-#define FALCON_LE     0
-#endif
-#ifndef FALCON_UNALIGNED
-#define FALCON_UNALIGNED   0
-#endif
-
-#endif
-
-/*
- * We ensure that both FALCON_FPEMU and FALCON_FPNATIVE are defined,
- * with compatible values (exactly one of them must be non-zero).
- * If none is defined, then default FP implementation is 'native'
- * except on ARM Cortex M4.
- */
-#if !defined FALCON_FPEMU && !defined FALCON_FPNATIVE
-
-#if (defined __ARM_FP && ((__ARM_FP & 0x08) == 0x08)) \
-	|| (!defined __ARM_FP && defined __ARM_VFPV2__)
-#define FALCON_FPEMU      0
-#define FALCON_FPNATIVE   1
-#elif defined FALCON_ASM_CORTEXM4 && FALCON_ASM_CORTEXM4
-#define FALCON_FPEMU      1
-#define FALCON_FPNATIVE   0
-#else
-#define FALCON_FPEMU      0
-#define FALCON_FPNATIVE   1
-#endif
-
-#elif defined FALCON_FPEMU && !defined FALCON_FPNATIVE
-
-#if FALCON_FPEMU
-#define FALCON_FPNATIVE   0
-#else
-#define FALCON_FPNATIVE   1
-#endif
-
-#elif defined FALCON_FPNATIVE && !defined FALCON_FPEMU
-
-#if FALCON_FPNATIVE
-#define FALCON_FPEMU   0
-#else
-#define FALCON_FPEMU   1
-#endif
-
-#endif
-
-#if (FALCON_FPEMU && FALCON_FPNATIVE) || (!FALCON_FPEMU && !FALCON_FPNATIVE)
-#error Exactly one of FALCON_FPEMU and FALCON_FPNATIVE must be selected
-#endif
-
-
-/*
- * For still undefined compile-time macros, define them to 0 to avoid
- * warnings with -Wundef.
- */
-#ifndef FALCON_AVX2
-#define FALCON_AVX2   0
-#endif
-#ifndef FALCON_FMA
-#define FALCON_FMA   0
-#endif
-#ifndef FALCON_KG_CHACHA20
-#define FALCON_KG_CHACHA20   0
-#endif
 
 
 
@@ -221,14 +106,6 @@
 
 
 
-/*
- * MSVC 2015 does not know the C99 keyword 'restrict'.
- */
-#if defined _MSC_VER && _MSC_VER
-#ifndef restrict
-#define restrict   __restrict
-#endif
-#endif
 
 /* ==================================================================== */
 /*
@@ -238,30 +115,16 @@
  * as part of PQClean.
  */
 
-typedef struct {
-	union {
-		uint64_t A[25];
-		uint8_t dbuf[200];
-	} st;
-	uint64_t dptr;
-} inner_shake256_context;
-
-#define inner_shake256_init      falcon512dyn_ref_i_shake256_init
-#define inner_shake256_inject    falcon512dyn_ref_i_shake256_inject
-#define inner_shake256_flip      falcon512dyn_ref_i_shake256_flip
-#define inner_shake256_extract   falcon512dyn_ref_i_shake256_extract
-
-void falcon512dyn_ref_i_shake256_init(
-	inner_shake256_context *sc);
-void falcon512dyn_ref_i_shake256_inject(
-	inner_shake256_context *sc, const uint8_t *in, size_t len);
-void falcon512dyn_ref_i_shake256_flip(
-	inner_shake256_context *sc);
-void falcon512dyn_ref_i_shake256_extract(
-	inner_shake256_context *sc, uint8_t *out, size_t len);
 
-/*
- */
+#include "fips202.h"
+
+#define inner_shake256_context                shake256incctx
+#define inner_shake256_init(sc)               shake256_inc_init(sc)
+#define inner_shake256_inject(sc, in, len)    shake256_inc_absorb(sc, in, len)
+#define inner_shake256_flip(sc)               shake256_inc_finalize(sc)
+#define inner_shake256_extract(sc, out, len)  shake256_inc_squeeze(out, len, sc)
+#define inner_shake256_ctx_release(sc)        shake256_inc_ctx_release(sc)
+
 
 /* ==================================================================== */
 /*
@@ -450,7 +313,7 @@
  *
  * tmp[] must have 16-bit alignment.
  */
-int falcon512dyn_ref_count_nttzero(int16_t *sig, unsigned logn, uint8_t *tmp);
+int falcon512dyn_ref_count_nttzero(const int16_t *sig, unsigned logn, uint8_t *tmp);
 
 /*
  * Internal signature verification with public key recovery:
@@ -653,10 +516,6 @@
 	}
 	p->ptr = u + 8;
 
-	/*
-	 * On systems that use little-endian encoding and allow
-	 * unaligned accesses, we can simply read the data where it is.
-	 */
 	return (uint64_t)p->buf.d[u + 0]
 		| ((uint64_t)p->buf.d[u + 1] << 8)
 		| ((uint64_t)p->buf.d[u + 2] << 16)

