--- upstream/avx2/params.h
+++ upstream-patched/avx2/params.h
@@ -1,35 +1,6 @@
 #ifndef PARAMS_H
 #define PARAMS_H
 
-#ifndef KYBER_K
-#define KYBER_K 3	/* Change this for different security strengths */
-#endif
-
-//#define KYBER_90S	/* Uncomment this if you want the 90S variant */
-
-/* Don't change parameters below this line */
-#if   (KYBER_K == 2)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber512_90s_avx2_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber512_avx2_##s
-#endif
-#elif (KYBER_K == 3)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber768_90s_avx2_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber768_avx2_##s
-#endif
-#elif (KYBER_K == 4)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_90s_avx2_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_avx2_##s
-#endif
-#else
-#error "KYBER_K must be in {2,3,4}"
-#endif
-
 #define KYBER_N 256
 #define KYBER_Q 3329
 
@@ -40,14 +11,17 @@
 #define KYBER_POLYVECBYTES	(KYBER_K * KYBER_POLYBYTES)
 
 #if KYBER_K == 2
+#define KYBER_K 2
 #define KYBER_ETA1 3
 #define KYBER_POLYCOMPRESSEDBYTES    128
 #define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)
 #elif KYBER_K == 3
+#define KYBER_K 3
 #define KYBER_ETA1 2
 #define KYBER_POLYCOMPRESSEDBYTES    128
 #define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 320)
 #elif KYBER_K == 4
+#define KYBER_K 4
 #define KYBER_ETA1 2
 #define KYBER_POLYCOMPRESSEDBYTES    160
 #define KYBER_POLYVECCOMPRESSEDBYTES (KYBER_K * 352)

