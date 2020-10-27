--- upstream/avx2/fips202x4.h
+++ upstream-patched/avx2/fips202x4.h
@@ -5,8 +5,6 @@
 #include <stdint.h>
 #include <immintrin.h>
 
-#define FIPS202X4_NAMESPACE(s) pqcrystals_fips202x4_avx2##s
-
 typedef struct {
   __m256i s[25];
 } keccakx4_state;

