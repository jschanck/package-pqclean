--- upstream/ref/params.h
+++ upstream-patched/ref/params.h
@@ -5,31 +5,6 @@
 #define KYBER_K 3	/* Change this for different security strengths */
 #endif
 
-//#define KYBER_90S	/* Uncomment this if you want the 90S variant */
-
-/* Don't change parameters below this line */
-#if   (KYBER_K == 2)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber512_90s_ref_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber512_ref_##s
-#endif
-#elif (KYBER_K == 3)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber768_90s_ref_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber768_ref_##s
-#endif
-#elif (KYBER_K == 4)
-#ifdef KYBER_90S
-#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_90s_ref_##s
-#else
-#define KYBER_NAMESPACE(s) pqcrystals_kyber1024_ref_##s
-#endif
-#else
-#error "KYBER_K must be in {2,3,4}"
-#endif
-
 #define KYBER_N 256
 #define KYBER_Q 3329
 
@@ -40,14 +15,17 @@
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

