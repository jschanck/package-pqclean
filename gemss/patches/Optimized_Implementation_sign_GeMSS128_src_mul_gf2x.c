--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/src/mul_gf2x.c
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/src/mul_gf2x.c
@@ -45,6 +45,7 @@
     MUL128_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul160_no_simd_gf2x)(uint64_t C[5], const uint64_t A[3],
                                                      const uint64_t B[3])
 {
@@ -52,6 +53,7 @@
     MUL160_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul192_no_simd_gf2x)(uint64_t C[6], const uint64_t A[3],
                                                      const uint64_t B[3])
 {
@@ -59,6 +61,7 @@
     MUL192_NO_SIMD_GF2X(C,A,B,tmp,AA,BB);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul224_no_simd_gf2x)(uint64_t C[7], const uint64_t A[4],
                                                      const uint64_t B[4])
 {
@@ -66,6 +69,7 @@
     MUL224_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul256_no_simd_gf2x)(uint64_t C[8], const uint64_t A[4],
                                                      const uint64_t B[4])
 {
@@ -73,6 +77,7 @@
     MUL256_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul288_no_simd_gf2x)(uint64_t C[9], const uint64_t A[5],
                                                      const uint64_t B[5])
 {
@@ -81,6 +86,7 @@
 }
 
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul320_no_simd_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                       const uint64_t B[5])
 {
@@ -88,6 +94,7 @@
     MUL320_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul352_no_simd_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                       const uint64_t B[6])
 {
@@ -95,6 +102,7 @@
     MUL352_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul384_no_simd_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                       const uint64_t B[6])
 {
@@ -102,6 +110,7 @@
     MUL384_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul416_no_simd_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                       const uint64_t B[7])
 {
@@ -109,6 +118,7 @@
     MUL416_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul448_no_simd_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                       const uint64_t B[7])
 {
@@ -116,6 +126,7 @@
     MUL448_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul480_no_simd_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                       const uint64_t B[8])
 {
@@ -123,6 +134,7 @@
     MUL480_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul512_no_simd_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                       const uint64_t B[8])
 {
@@ -130,6 +142,7 @@
     MUL512_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul544_no_simd_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                       const uint64_t B[9])
 {
@@ -137,6 +150,7 @@
     MUL544_NO_SIMD_GF2X(C,A,B,tmp,AA,BB,tmp3,tmp4,tmp1,tmp2);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(mul576_no_simd_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                       const uint64_t B[9])
 {
@@ -220,6 +234,7 @@
     PSTORE384(C,C1,C2,C3);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul224_gf2x)(uint64_t C[7], const uint64_t A[4],
                                               const uint64_t B[4])
 {
@@ -231,6 +246,7 @@
     PSTORE448(C,C1,C2,C3,C4);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul256_gf2x)(uint64_t C[8], const uint64_t A[4],
                                               const uint64_t B[4])
 {
@@ -242,6 +258,7 @@
     PSTORE512(C,C1,C2,C3,C4);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul288_gf2x)(uint64_t C[9], const uint64_t A[5],
                                               const uint64_t B[5])
 {
@@ -254,6 +271,7 @@
     PSTORE576(C,C1,C2,C3,C4,C5);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul320_gf2x)(uint64_t C[10], const uint64_t A[5],
                                                const uint64_t B[5])
 {
@@ -266,6 +284,7 @@
     PSTORE640(C,C1,C2,C3,C4,C5);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul352_gf2x)(uint64_t C[11], const uint64_t A[6],
                                                const uint64_t B[6])
 {
@@ -279,6 +298,7 @@
 }
 
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul384_gf2x)(uint64_t C[12], const uint64_t A[6],
                                                const uint64_t B[6])
 {
@@ -291,6 +311,7 @@
     PSTORE768(C,C1,C2,C3,C4,C5,C6);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul416_gf2x)(uint64_t C[13], const uint64_t A[7],
                                                const uint64_t B[7])
 {
@@ -304,6 +325,7 @@
     PSTORE832(C,C1,C2,C3,C4,C5,C6,C7);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul448_gf2x)(uint64_t C[14], const uint64_t A[7],
                                                const uint64_t B[7])
 {
@@ -317,6 +339,7 @@
     PSTORE896(C,C1,C2,C3,C4,C5,C6,C7);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul480_gf2x)(uint64_t C[15], const uint64_t A[8],
                                                const uint64_t B[8])
 {
@@ -330,6 +353,7 @@
     PSTORE960(C,C1,C2,C3,C4,C5,C6,C7,C8);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul512_gf2x)(uint64_t C[16], const uint64_t A[8],
                                                const uint64_t B[8])
 {
@@ -343,6 +367,7 @@
     PSTORE1024(C,C1,C2,C3,C4,C5,C6,C7,C8);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul544_gf2x)(uint64_t C[17], const uint64_t A[9],
                                                const uint64_t B[9])
 {
@@ -356,6 +381,7 @@
     PSTORE1088(C,C1,C2,C3,C4,C5,C6,C7,C8,C9);
 }
 
+// NOLINTNEXTLINE(google-readability-function-size)
 void PREFIX_NAME(pmul576_gf2x)(uint64_t C[18], const uint64_t A[9],
                                                const uint64_t B[9])
 {

