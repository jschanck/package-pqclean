--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/include/sqr_gf2x.h
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/include/sqr_gf2x.h
@@ -66,7 +66,7 @@
     SQR64_NO_SIMD_GF2X(C,(A)[0]);
 
 #define SQR128_NO_SIMD_GF2X(C,A) \
-    SQR64_NO_SIMD_GF2X(C+2,(A)[1]);\
+    SQR64_NO_SIMD_GF2X((C)+2,(A)[1]);\
     SQR64_NO_SIMD_GF2X(C,(A)[0]);
 
 #define SQR160_NO_SIMD_GF2X(C,A) \
@@ -74,15 +74,15 @@
     SQR128_NO_SIMD_GF2X(C,A);
 
 #define SQR192_NO_SIMD_GF2X(C,A) \
-    SQR64_NO_SIMD_GF2X(C+4,(A)[2]);\
+    SQR64_NO_SIMD_GF2X((C)+4,(A)[2]);\
     SQR128_NO_SIMD_GF2X(C,A);
 
 #define SQR224_NO_SIMD_GF2X(C,A) \
-    SQR96_NO_SIMD_GF2X(C+4,A+2);\
+    SQR96_NO_SIMD_GF2X((C)+4,(A)+2);\
     SQR128_NO_SIMD_GF2X(C,A);
 
 #define SQR256_NO_SIMD_GF2X(C,A) \
-    SQR128_NO_SIMD_GF2X(C+4,A+2);\
+    SQR128_NO_SIMD_GF2X((C)+4,(A)+2);\
     SQR128_NO_SIMD_GF2X(C,A);
 
 #define SQR288_NO_SIMD_GF2X(C,A) \
@@ -90,31 +90,31 @@
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR320_NO_SIMD_GF2X(C,A) \
-    SQR64_NO_SIMD_GF2X(C+8,(A)[4]);\
+    SQR64_NO_SIMD_GF2X((C)+8,(A)[4]);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR352_NO_SIMD_GF2X(C,A) \
-    SQR96_NO_SIMD_GF2X(C+8,A+4);\
+    SQR96_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR384_NO_SIMD_GF2X(C,A) \
-    SQR128_NO_SIMD_GF2X(C+8,A+4);\
+    SQR128_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR416_NO_SIMD_GF2X(C,A) \
-    SQR160_NO_SIMD_GF2X(C+8,A+4);\
+    SQR160_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR448_NO_SIMD_GF2X(C,A) \
-    SQR192_NO_SIMD_GF2X(C+8,A+4);\
+    SQR192_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR480_NO_SIMD_GF2X(C,A) \
-    SQR224_NO_SIMD_GF2X(C+8,A+4);\
+    SQR224_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR512_NO_SIMD_GF2X(C,A) \
-    SQR256_NO_SIMD_GF2X(C+8,A+4);\
+    SQR256_NO_SIMD_GF2X((C)+8,(A)+4);\
     SQR256_NO_SIMD_GF2X(C,A);
 
 #define SQR544_NO_SIMD_GF2X(C,A) \
@@ -122,7 +122,7 @@
     SQR512_NO_SIMD_GF2X(C,A);
 
 #define SQR576_NO_SIMD_GF2X(C,A) \
-    SQR64_NO_SIMD_GF2X(C+16,(A)[8]);\
+    SQR64_NO_SIMD_GF2X((C)+16,(A)[8]);\
     SQR512_NO_SIMD_GF2X(C,A);
 
 
@@ -177,25 +177,25 @@
 
 /* 11 instructions */
 #define PSQR64_LO_GF2X(C1,A1,RA,R1) \
-    R1=PUNPACKLO_8(A1,RA);\
-    C1=PAND_(R1,PSET1_8(0xF));\
-    R1=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
-    C1=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
+    (R1)=PUNPACKLO_8(A1,RA);\
+    (C1)=PAND_(R1,PSET1_8(0xF));\
+    (R1)=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
+    (C1)=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
 
 /* 11 instructions */
 #define PSQR64_HI_GF2X(C1,A1,RA,R1) \
-    R1=PUNPACKHI_8(A1,RA);\
-    C1=PAND_(R1,PSET1_8(0xF));\
-    R1=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
-    C1=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
+    (R1)=PUNPACKHI_8(A1,RA);\
+    (C1)=PAND_(R1,PSET1_8(0xF));\
+    (R1)=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
+    (C1)=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
 
 /* 12 instructions */
 #define PSQR64_GF2X(C1,A1,RA,R1) \
     RA=PSRLI_16(A1,4);\
-    R1=PUNPACKLO_8(A1,RA);\
-    C1=PAND_(R1,PSET1_8(0xF));\
-    R1=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
-    C1=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
+    (R1)=PUNPACKLO_8(A1,RA);\
+    (C1)=PAND_(R1,PSET1_8(0xF));\
+    (R1)=PAND_(PXOR_(C1,PSLLI_16(C1,2)),PSET1_8(0x33));\
+    (C1)=PAND_(PXOR_(R1,PSLLI_16(R1,1)),PSET1_8(0x55));
 
 #define PSQR128_GF2X(C1,C2,A1,RA,R1) \
     RA=PSRLI_16(A1,4);\
@@ -282,53 +282,53 @@
 
 
 #define PSQR_INIT_SHUFFLE_GF2X(M,T) \
-    M=PSET1_8(0x0F);\
-    T=PSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100);
+    (M)=PSET1_8(0x0F);\
+    (T)=PSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100);
 
 /* 6 instructions */
 #define PSQR64_SHUFFLE_V1_GF2X(E0,A128,M,T) \
     {__m128i C0,C1,D0,D1;\
-    C0=PAND_(A128,M);\
-    C1=PAND_(PSRLI_16(A128,4),M);\
+    (C0)=PAND_(A128,M);\
+    (C1)=PAND_(PSRLI_16(A128,4),M);\
 \
-    D0=PSHUFFLE_8(T,C0);\
-    D1=PSHUFFLE_8(T,C1);\
+    (D0)=PSHUFFLE_8(T,C0);\
+    (D1)=PSHUFFLE_8(T,C1);\
 \
-    E0=PUNPACKLO_8(D0,D1);}
+    (E0)=PUNPACKLO_8(D0,D1);}
 
 /* 4 instructions, faster than PSQR64_SHUFFLE_V1_GF2X */
 #define PSQR64_SHUFFLE_GF2X(E0,A128,M,T) \
     {__m128i C0,D0;\
-    E0=PSRLI_16(A128,4);\
-    C0=PUNPACKLO_8(A128,E0);\
-    D0=PAND_(C0,M);\
-    E0=PSHUFFLE_8(T,D0);}
+    (E0)=PSRLI_16(A128,4);\
+    (C0)=PUNPACKLO_8(A128,E0);\
+    (D0)=PAND_(C0,M);\
+    (E0)=PSHUFFLE_8(T,D0);}
 
 /* 7 instructions */
 #define PSQR128_SHUFFLE_V1_GF2X(E0,E1,A128,M,T) \
     {__m128i C0,C1,D0,D1;\
-    E0=PSRLI_16(A128,4);\
+    (E0)=PSRLI_16(A128,4);\
 \
-    C0=PUNPACKLO_8(A128,E0);\
-    C1=PUNPACKHI_8(A128,E0);\
+    (C0)=PUNPACKLO_8(A128,E0);\
+    (C1)=PUNPACKHI_8(A128,E0);\
 \
-    D0=PAND_(C0,M);\
-    D1=PAND_(C1,M);\
+    (D0)=PAND_(C0,M);\
+    (D1)=PAND_(C1,M);\
 \
-    E0=PSHUFFLE_8(T,D0);\
-    E1=PSHUFFLE_8(T,D1);}
+    (E0)=PSHUFFLE_8(T,D0);\
+    (E1)=PSHUFFLE_8(T,D1);}
 
 /* 7 instructions, faster than PSQR128_SHUFFLE_V1_GF2X */
 #define PSQR128_SHUFFLE_GF2X(E0,E1,A128,M,T) \
     {__m128i C0,C1,D0,D1;\
-    C0=PAND_(A128,M);\
-    C1=PAND_(PSRLI_16(A128,4),M);\
+    (C0)=PAND_(A128,M);\
+    (C1)=PAND_(PSRLI_16(A128,4),M);\
 \
-    D0=PSHUFFLE_8(T,C0);\
-    D1=PSHUFFLE_8(T,C1);\
+    (D0)=PSHUFFLE_8(T,C0);\
+    (D1)=PSHUFFLE_8(T,C1);\
 \
-    E0=PUNPACKLO_8(D0,D1);\
-    E1=PUNPACKHI_8(D0,D1);}
+    (E0)=PUNPACKLO_8(D0,D1);\
+    (E1)=PUNPACKHI_8(D0,D1);}
 
 /* General macros */
 #define PSQR192_SHUFFLE_GF2X(E1,E2,E3,A1,A2,M,T) \
@@ -403,58 +403,58 @@
 
 
 #define VPSQR_INIT_SHUFFLE_GF2X(M,T) \
-    M=VPSET1_8(0x0F);\
-    T=VPSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100,\
+    (M)=VPSET1_8(0x0F);\
+    (T)=VPSET_64((uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100,\
                (uint64_t)0x5554515045444140,(uint64_t)0x1514111005040100);
 
 /* 4 instructions */
 #define VPSQR64_SHUFFLE_GF2X(E0,A256,M,T) \
     {__m256i B1,C0,D0;\
-    B1=VPSRLI_16(A256,4);\
-    C0=VPUNPACKLO_8(A256,B1);\
-    D0=VPAND_(C0,M);\
-    E0=VPSHUFFLE_8(T,D0);}
+    (B1)=VPSRLI_16(A256,4);\
+    (C0)=VPUNPACKLO_8(A256,B1);\
+    (D0)=VPAND_(C0,M);\
+    (E0)=VPSHUFFLE_8(T,D0);}
 
 /* 5 instructions */
 #define VPSQR128_SHUFFLE_GF2X(E0,A256,M,T) \
     {__m256i B0,B1,C0,D0;\
-    B0=VPPERMUTE4x64(A256,0xD8);\
-    B1=VPSRLI_16(B0,4);\
-    C0=VPUNPACKLO_8(B0,B1);\
-    D0=VPAND_(C0,M);\
-    E0=VPSHUFFLE_8(T,D0);}
+    (B0)=VPPERMUTE4x64(A256,0xD8);\
+    (B1)=VPSRLI_16(B0,4);\
+    (C0)=VPUNPACKLO_8(B0,B1);\
+    (D0)=VPAND_(C0,M);\
+    (E0)=VPSHUFFLE_8(T,D0);}
 
 /* unpack after */
 /* 9 instructions */
 #define VPSQR256_SHUFFLE_V1_GF2X(E0,E1,A256,M,T) \
     {__m256i B0,B1,C0,C1,D0,D1;\
-    B0=VPAND_(A256,M);\
-    B1=VPAND_(VPSRLI_16(A256,4),M);\
+    (B0)=VPAND_(A256,M);\
+    (B1)=VPAND_(VPSRLI_16(A256,4),M);\
 \
-    C0=VPSHUFFLE_8(T,B0);\
-    C1=VPSHUFFLE_8(T,B1);\
+    (C0)=VPSHUFFLE_8(T,B0);\
+    (C1)=VPSHUFFLE_8(T,B1);\
 \
-    D0=VPUNPACKLO_8(C0,C1);\
-    D1=VPUNPACKHI_8(C0,C1);\
+    (D0)=VPUNPACKLO_8(C0,C1);\
+    (D1)=VPUNPACKHI_8(C0,C1);\
 \
-    E0=VPPERMUTE2x128(D0,D1,0x20);\
-    E1=VPPERMUTE2x128(D0,D1,0x31);}
+    (E0)=VPPERMUTE2x128(D0,D1,0x20);\
+    (E1)=VPPERMUTE2x128(D0,D1,0x31);}
 
 /* unpack before */
 /* 8 instructions, faster than VPSQR256_SHUFFLE_V1_GF2X */
 #define VPSQR256_SHUFFLE_GF2X(E0,E1,A256,M,T) \
     {__m256i B0,B1,C0,C1,D0,D1;\
-    B0=VPPERMUTE4x64(A256,0xD8);\
-    B1=VPSRLI_16(B0,4);\
+    (B0)=VPPERMUTE4x64(A256,0xD8);\
+    (B1)=VPSRLI_16(B0,4);\
 \
-    C0=VPUNPACKLO_8(B0,B1);\
-    C1=VPUNPACKHI_8(B0,B1);\
+    (C0)=VPUNPACKLO_8(B0,B1);\
+    (C1)=VPUNPACKHI_8(B0,B1);\
 \
-    D0=VPAND_(C0,M);\
-    D1=VPAND_(C1,M);\
+    (D0)=VPAND_(C0,M);\
+    (D1)=VPAND_(C1,M);\
 \
-    E0=VPSHUFFLE_8(T,D0);\
-    E1=VPSHUFFLE_8(T,D1);}
+    (E0)=VPSHUFFLE_8(T,D0);\
+    (E1)=VPSHUFFLE_8(T,D1);}
 
 #define VPSQR192_SHUFFLE_GF2X VPSQR256_SHUFFLE_GF2X
 
@@ -615,74 +615,74 @@
 /* 2 pclmul */
 #define SQR96_PCLMUL_GF2X(C,x,z) \
     SQR64_PCLMUL_GF2X(C,x,z,0);\
-    SQR64LOW_TAB_PCLMUL_GF2X(C+2,x,17);
+    SQR64LOW_TAB_PCLMUL_GF2X((C)+2,x,17);
 
 #define SQR128_PCLMUL_GF2X(C,x,z) \
     SQR64_PCLMUL_GF2X(C,x,z,0);\
-    SQR64_PCLMUL_GF2X(C+2,x,z,17);
+    SQR64_PCLMUL_GF2X((C)+2,x,z,17);
 
 /* 3 pclmul */
 #define SQR160_PCLMUL_GF2X(C,x1,x2,z) \
     SQR128_PCLMUL_GF2X(C,x1,z);\
-    SQR64LOW_TAB_PCLMUL_GF2X(C+4,x2,0);
+    SQR64LOW_TAB_PCLMUL_GF2X((C)+4,x2,0);
 
 #define SQR192_PCLMUL_GF2X(C,x1,x2,z) \
     SQR128_PCLMUL_GF2X(C,x1,z);\
-    SQR64_PCLMUL_GF2X(C+4,x2,z,0);
+    SQR64_PCLMUL_GF2X((C)+4,x2,z,0);
 
 /* 4 pclmul */
 #define SQR224_PCLMUL_GF2X(C,x1,x2,z) \
     SQR128_PCLMUL_GF2X(C,x1,z);\
-    SQR96_PCLMUL_GF2X(C+4,x2,z);
+    SQR96_PCLMUL_GF2X((C)+4,x2,z);
 
 #define SQR256_PCLMUL_GF2X(C,x1,x2,z) \
     SQR128_PCLMUL_GF2X(C,x1,z);\
-    SQR128_PCLMUL_GF2X(C+4,x2,z);
+    SQR128_PCLMUL_GF2X((C)+4,x2,z);
 
 /* 5 pclmul */
 #define SQR288_PCLMUL_GF2X(C,x1,x2,x3,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR64LOW_TAB_PCLMUL_GF2X(C+8,x3,0);
+    SQR64LOW_TAB_PCLMUL_GF2X((C)+8,x3,0);
 
 #define SQR320_PCLMUL_GF2X(C,x1,x2,x3,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR64_PCLMUL_GF2X(C+8,x3,z,0);
+    SQR64_PCLMUL_GF2X((C)+8,x3,z,0);
 
 /* 6 pclmul */
 #define SQR352_PCLMUL_GF2X(C,x1,x2,x3,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR96_PCLMUL_GF2X(C+8,x3,z);
+    SQR96_PCLMUL_GF2X((C)+8,x3,z);
 
 #define SQR384_PCLMUL_GF2X(C,x1,x2,x3,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR128_PCLMUL_GF2X(C+8,x3,z);
+    SQR128_PCLMUL_GF2X((C)+8,x3,z);
 
 /* 7 pclmul */
 #define SQR416_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR160_PCLMUL_GF2X(C+8,x3,x4,z);
+    SQR160_PCLMUL_GF2X((C)+8,x3,x4,z);
 
 #define SQR448_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR192_PCLMUL_GF2X(C+8,x3,x4,z);
+    SQR192_PCLMUL_GF2X((C)+8,x3,x4,z);
 
 /* 8 pclmul */
 #define SQR480_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR224_PCLMUL_GF2X(C+8,x3,x4,z);
+    SQR224_PCLMUL_GF2X((C)+8,x3,x4,z);
 
 #define SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z) \
     SQR256_PCLMUL_GF2X(C,x1,x2,z);\
-    SQR256_PCLMUL_GF2X(C+8,x3,x4,z);
+    SQR256_PCLMUL_GF2X((C)+8,x3,x4,z);
 
 /* 9 pclmul */
 #define SQR544_PCLMUL_GF2X(C,x1,x2,x3,x4,x5,z) \
     SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z);\
-    SQR64LOW_TAB_PCLMUL_GF2X(C+16,x5,0);
+    SQR64LOW_TAB_PCLMUL_GF2X((C)+16,x5,0);
 
 #define SQR576_PCLMUL_GF2X(C,x1,x2,x3,x4,x5,z) \
     SQR512_PCLMUL_GF2X(C,x1,x2,x3,x4,z);\
-    SQR64_PCLMUL_GF2X(C+16,x5,z,0);
+    SQR64_PCLMUL_GF2X((C)+16,x5,z,0);
 
 
 

