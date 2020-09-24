--- upstream/Optimized_Implementation/sign/GeMSS128/include/simd_intel.h
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/include/simd_intel.h
@@ -16,7 +16,7 @@
     #define PSHUFFLE_PS(A,B,i) \
                 ((__m128i)_mm_shuffle_ps((__m128)(A),(__m128)(B),i))
 
-    #define PMOVE_PS(A,B) ((__m128i)_mm_move_ss((__m128)A,(__m128)B))
+    #define PMOVE_PS(A,B) ((__m128i)_mm_move_ss((__m128)(A),(__m128)(B)))
 #endif
 
 
@@ -200,67 +200,67 @@
 
     #define PINIT192(x1,x2,A) \
         PINIT128(x1,A);\
-        PINIT64(x2,A+2);
+        PINIT64(x2,(A)+2);
 
     #define PINIT256(x1,x2,A) \
         PINIT128(x1,A);\
-        PINIT128(x2,A+2);
+        PINIT128(x2,(A)+2);
 
     #define PINIT320(x1,x2,x3,A) \
         PINIT256(x1,x2,A);\
-        PINIT64(x3,A+4);
+        PINIT64(x3,(A)+4);
 
     #define PINIT384(x1,x2,x3,A) \
         PINIT256(x1,x2,A);\
-        PINIT128(x3,A+4);
+        PINIT128(x3,(A)+4);
 
     #define PINIT448(x1,x2,x3,x4,A) \
         PINIT256(x1,x2,A);\
-        PINIT192(x3,x4,A+4);
+        PINIT192(x3,x4,(A)+4);
 
     #define PINIT512(x1,x2,x3,x4,A) \
         PINIT256(x1,x2,A);\
-        PINIT256(x3,x4,A+4);
+        PINIT256(x3,x4,(A)+4);
 
     #define PINIT576(x1,x2,x3,x4,x5,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT64(x5,A+8);
+        PINIT64(x5,(A)+8);
 
     #define PINIT640(x1,x2,x3,x4,x5,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT128(x5,A+8);
+        PINIT128(x5,(A)+8);
 
     #define PINIT704(x1,x2,x3,x4,x5,x6,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT192(x5,x6,A+8);
+        PINIT192(x5,x6,(A)+8);
 
     #define PINIT768(x1,x2,x3,x4,x5,x6,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT256(x5,x6,A+8);
+        PINIT256(x5,x6,(A)+8);
 
     #define PINIT832(x1,x2,x3,x4,x5,x6,x7,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT320(x5,x6,x7,A+8);
+        PINIT320(x5,x6,x7,(A)+8);
 
     #define PINIT896(x1,x2,x3,x4,x5,x6,x7,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT384(x5,x6,x7,A+8);
+        PINIT384(x5,x6,x7,(A)+8);
 
     #define PINIT960(x1,x2,x3,x4,x5,x6,x7,x8,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT448(x5,x6,x7,x8,A+8);
+        PINIT448(x5,x6,x7,x8,(A)+8);
 
     #define PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A) \
         PINIT512(x1,x2,x3,x4,A);\
-        PINIT512(x5,x6,x7,x8,A+8);
+        PINIT512(x5,x6,x7,x8,(A)+8);
 
     #define PINIT1088(x1,x2,x3,x4,x5,x6,x7,x8,x9,A) \
         PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A);\
-        PINIT64(x9,A+16);
+        PINIT64(x9,(A)+16);
 
     #define PINIT1152(x1,x2,x3,x4,x5,x6,x7,x8,x9,A) \
         PINIT1024(x1,x2,x3,x4,x5,x6,x7,x8,A);\
-        PINIT128(x9,A+16);
+        PINIT128(x9,(A)+16);
 
 
     /* Store */
@@ -268,67 +268,67 @@
 
     #define PSTORE192(A,x1,x2) \
         PSTORE128(A,x1);\
-        PSTOREL(A+2,x2);
+        PSTOREL((A)+2,x2);
 
     #define PSTORE256(A,x1,x2) \
         PSTORE128(A,x1);\
-        PSTORE128(A+2,x2);
+        PSTORE128((A)+2,x2);
 
     #define PSTORE320(A,x1,x2,x3) \
         PSTORE256(A,x1,x2);\
-        PSTOREL(A+4,x3);
+        PSTOREL((A)+4,x3);
 
     #define PSTORE384(A,x1,x2,x3) \
         PSTORE256(A,x1,x2);\
-        PSTORE128(A+4,x3);
+        PSTORE128((A)+4,x3);
 
     #define PSTORE448(A,x1,x2,x3,x4) \
         PSTORE256(A,x1,x2);\
-        PSTORE192(A+4,x3,x4);
+        PSTORE192((A)+4,x3,x4);
 
     #define PSTORE512(A,x1,x2,x3,x4) \
         PSTORE256(A,x1,x2);\
-        PSTORE256(A+4,x3,x4);
+        PSTORE256((A)+4,x3,x4);
 
     #define PSTORE576(A,x1,x2,x3,x4,x5) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTOREL(A+8,x5);
+        PSTOREL((A)+8,x5);
 
     #define PSTORE640(A,x1,x2,x3,x4,x5) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE128(A+8,x5);
+        PSTORE128((A)+8,x5);
 
     #define PSTORE704(A,x1,x2,x3,x4,x5,x6) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE192(A+8,x5,x6);
+        PSTORE192((A)+8,x5,x6);
 
     #define PSTORE768(A,x1,x2,x3,x4,x5,x6) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE256(A+8,x5,x6);
+        PSTORE256((A)+8,x5,x6);
 
     #define PSTORE832(A,x1,x2,x3,x4,x5,x6,x7) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE320(A+8,x5,x6,x7);
+        PSTORE320((A)+8,x5,x6,x7);
 
     #define PSTORE896(A,x1,x2,x3,x4,x5,x6,x7) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE384(A+8,x5,x6,x7);
+        PSTORE384((A)+8,x5,x6,x7);
 
     #define PSTORE960(A,x1,x2,x3,x4,x5,x6,x7,x8) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE448(A+8,x5,x6,x7,x8);
+        PSTORE448((A)+8,x5,x6,x7,x8);
 
     #define PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8) \
         PSTORE512(A,x1,x2,x3,x4);\
-        PSTORE512(A+8,x5,x6,x7,x8);
+        PSTORE512((A)+8,x5,x6,x7,x8);
 
     #define PSTORE1088(A,x1,x2,x3,x4,x5,x6,x7,x8,x9) \
         PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8);\
-        PSTOREL(A+16,x9);
+        PSTOREL((A)+16,x9);
 
     #define PSTORE1152(A,x1,x2,x3,x4,x5,x6,x7,x8,x9) \
         PSTORE1024(A,x1,x2,x3,x4,x5,x6,x7,x8);\
-        PSTORE128(A+16,x9);
+        PSTORE128((A)+16,x9);
 
 
     /* Bitwise operator */
@@ -566,65 +566,65 @@
         x=PCVT_256(PLOADU(A));
 
     #define VPINIT192(x,A) \
-        x=VPINSERT_128(PCVT_256(PLOADU(A)),PLOADL(A+2));
+        x=VPINSERT_128(PCVT_256(PLOADU(A)),PLOADL((A)+2));
 
     #define VPINIT256(x,A) x=VPLOADU(A);
 
     #define VPINIT320(x1,x2,A) \
         VPINIT256(x1,A);\
-        VPINIT64(x2,A+4);
+        VPINIT64(x2,(A)+4);
 
     #define VPINIT384(x1,x2,A) \
         VPINIT256(x1,A);\
-        VPINIT128(x2,A+4);
+        VPINIT128(x2,(A)+4);
 
     #define VPINIT448(x1,x2,A) \
         VPINIT256(x1,A);\
-        VPINIT192(x2,A+4);
+        VPINIT192(x2,(A)+4);
 
     #define VPINIT512(x1,x2,A) \
         VPINIT256(x1,A);\
-        VPINIT256(x2,A+4);
+        VPINIT256(x2,(A)+4);
 
     #define VPINIT576(x1,x2,x3,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT64(x3,A+8);
+        VPINIT64(x3,(A)+8);
 
     #define VPINIT640(x1,x2,x3,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT128(x3,A+8);
+        VPINIT128(x3,(A)+8);
 
     #define VPINIT704(x1,x2,x3,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT192(x3,A+8);
+        VPINIT192(x3,(A)+8);
 
     #define VPINIT768(x1,x2,x3,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT256(x3,A+8);
+        VPINIT256(x3,(A)+8);
 
     #define VPINIT832(x1,x2,x3,x4,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT320(x3,x4,A+8);
+        VPINIT320(x3,x4,(A)+8);
 
     #define VPINIT896(x1,x2,x3,x4,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT384(x3,x4,A+8);
+        VPINIT384(x3,x4,(A)+8);
 
     #define VPINIT960(x1,x2,x3,x4,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT448(x3,x4,A+8);
+        VPINIT448(x3,x4,(A)+8);
 
     #define VPINIT1024(x1,x2,x3,x4,A) \
         VPINIT512(x1,x2,A);\
-        VPINIT512(x3,x4,A+8);
+        VPINIT512(x3,x4,(A)+8);
 
     #define VPINIT1088(x1,x2,x3,x4,x5,A) \
         VPINIT1024(x1,x2,x3,x4,A);\
-        VPINIT64(x5,A+16);
+        VPINIT64(x5,(A)+16);
 
     #define VPINIT1152(x1,x2,x3,x4,x5,A) \
         VPINIT1024(x1,x2,x3,x4,A);\
-        VPINIT128(x5,A+16);
+        VPINIT128(x5,(A)+16);
 
 
     /* Store */
@@ -636,65 +636,65 @@
 
     #define VPSTORE192(A,x) \
         PSTOREU(A,VPCVT_128(x));\
-        PSTOREL(A+2,VPEXTRACT128(x));
+        PSTOREL((A)+2,VPEXTRACT128(x));
 
     #define VPSTORE256 VPSTOREU
 
     #define VPSTORE320(A,x1,x2) \
         VPSTORE256(A,x1);\
-        VPSTORE64(A+4,x2);
+        VPSTORE64((A)+4,x2);
 
     #define VPSTORE384(A,x1,x2) \
         VPSTORE256(A,x1);\
-        VPSTORE128(A+4,x2);
+        VPSTORE128((A)+4,x2);
 
     #define VPSTORE448(A,x1,x2) \
         VPSTORE256(A,x1);\
-        VPSTORE192(A+4,x2);
+        VPSTORE192((A)+4,x2);
 
     #define VPSTORE512(A,x1,x2) \
         VPSTORE256(A,x1);\
-        VPSTORE256(A+4,x2);
+        VPSTORE256((A)+4,x2);
 
     #define VPSTORE576(A,x1,x2,x3) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE64(A+8,x3);
+        VPSTORE64((A)+8,x3);
 
     #define VPSTORE640(A,x1,x2,x3) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE128(A+8,x3);
+        VPSTORE128((A)+8,x3);
 
     #define VPSTORE704(A,x1,x2,x3) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE192(A+8,x3);
+        VPSTORE192((A)+8,x3);
 
     #define VPSTORE768(A,x1,x2,x3) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE256(A+8,x3);
+        VPSTORE256((A)+8,x3);
 
     #define VPSTORE832(A,x1,x2,x3,x4) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE320(A+8,x3,x4);
+        VPSTORE320((A)+8,x3,x4);
 
     #define VPSTORE896(A,x1,x2,x3,x4) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE384(A+8,x3,x4);
+        VPSTORE384((A)+8,x3,x4);
 
     #define VPSTORE960(A,x1,x2,x3,x4) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE448(A+8,x3,x4);
+        VPSTORE448((A)+8,x3,x4);
 
     #define VPSTORE1024(A,x1,x2,x3,x4) \
         VPSTORE512(A,x1,x2);\
-        VPSTORE512(A+8,x3,x4);
+        VPSTORE512((A)+8,x3,x4);
 
     #define VPSTORE1088(A,x1,x2,x3,x4,x5) \
         VPSTORE1024(A,x1,x2,x3,x4);\
-        VPSTORE64(A+16,x5);
+        VPSTORE64((A)+16,x5);
 
     #define VPSTORE1152(A,x1,x2,x3,x4,x5) \
         VPSTORE1024(A,x1,x2,x3,x4);\
-        VPSTORE128(A+16,x5);
+        VPSTORE128((A)+16,x5);
 #endif
 
 

