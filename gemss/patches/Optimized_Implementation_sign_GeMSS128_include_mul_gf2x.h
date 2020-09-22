--- GeMSS-Round2_V2.a/Optimized_Implementation/sign/GeMSS128/include/mul_gf2x.h
+++ GeMSS-Round2_V2.a-patched/Optimized_Implementation/sign/GeMSS128/include/mul_gf2x.h
@@ -76,9 +76,9 @@
 /* Classical, 189 = 31×6+3 instructions */
 #define MUL32_NO_UNROLLED_NO_SIMD_GF2X(C,A,B,i) \
     (C)=(-((B)&ONE64))&(A);\
-    for(i=1;i<32;++i)\
+    for((i)=1;(i)<32;++(i))\
     {\
-        (C)^=((-(((B)>>i)&ONE64))&(A))<<i;\
+        (C)^=((-(((B)>>(i))&ONE64))&(A))<<(i);\
     }
 
 
@@ -123,9 +123,9 @@
     (C)=(-((B)&ONE64))&(A);\
     /* Optimization: the '&1' is removed */\
     (C)^=((-((B)>>63))&(A))<<63;\
-    for(i=1;i<63;++i)\
+    for((i)=1;(i)<63;++(i))\
     {\
-        (C)^=((-(((B)>>i)&ONE64))&(A))<<i;\
+        (C)^=((-(((B)>>(i))&ONE64))&(A))<<(i);\
     }
 
 
@@ -203,14 +203,14 @@
 #define MUL64_NO_UNROLLED_NO_SIMD_GF2X(C,A,B,i,tmp) \
     (C)[0]=(-((B)&ONE64))&(A);\
     /* Optimization: the '&1' is removed */\
-    tmp=((-((B)>>63))&(A));\
-    (C)[0]^=tmp<<63;\
-    (C)[1]=tmp>>1;\
-    for(i=1;i<63;++i)\
+    (tmp)=((-((B)>>63))&(A));\
+    (C)[0]^=(tmp)<<63;\
+    (C)[1]=(tmp)>>1;\
+    for((i)=1;(i)<63;++(i))\
     {\
-        tmp=((-(((B)>>i)&ONE64))&(A));\
-        (C)[0]^=tmp<<i;\
-        (C)[1]^=tmp>>(64-i);\
+        (tmp)=((-(((B)>>(i))&ONE64))&(A));\
+        (C)[0]^=(tmp)<<(i);\
+        (C)[1]^=(tmp)>>(64-(i));\
     }
 
 
@@ -218,197 +218,197 @@
 #define MUL64_NO_SIMD_GF2X(C,A,B,tmp) \
     (C)[0]=(-((B)&ONE64))&(A);\
     /* Optimization: the '&1' is removed */\
-    tmp=((-((B)>>63))&(A));\
-    (C)[0]^=tmp<<63;\
-    (C)[1]=tmp>>1;\
-\
-    tmp=((-(((B)>>1)&ONE64))&(A));\
-    (C)[0]^=tmp<<1;\
-    (C)[1]^=tmp>>63;\
-    tmp=((-(((B)>>2)&ONE64))&(A));\
-    (C)[0]^=tmp<<2;\
-    (C)[1]^=tmp>>62;\
-    tmp=((-(((B)>>3)&ONE64))&(A));\
-    (C)[0]^=tmp<<3;\
-    (C)[1]^=tmp>>61;\
-    tmp=((-(((B)>>4)&ONE64))&(A));\
-    (C)[0]^=tmp<<4;\
-    (C)[1]^=tmp>>60;\
-    tmp=((-(((B)>>5)&ONE64))&(A));\
-    (C)[0]^=tmp<<5;\
-    (C)[1]^=tmp>>59;\
-    tmp=((-(((B)>>6)&ONE64))&(A));\
-    (C)[0]^=tmp<<6;\
-    (C)[1]^=tmp>>58;\
-    tmp=((-(((B)>>7)&ONE64))&(A));\
-    (C)[0]^=tmp<<7;\
-    (C)[1]^=tmp>>57;\
-    tmp=((-(((B)>>8)&ONE64))&(A));\
-    (C)[0]^=tmp<<8;\
-    (C)[1]^=tmp>>56;\
-    tmp=((-(((B)>>9)&ONE64))&(A));\
-    (C)[0]^=tmp<<9;\
-    (C)[1]^=tmp>>55;\
-    tmp=((-(((B)>>10)&ONE64))&(A));\
-    (C)[0]^=tmp<<10;\
-    (C)[1]^=tmp>>54;\
-    tmp=((-(((B)>>11)&ONE64))&(A));\
-    (C)[0]^=tmp<<11;\
-    (C)[1]^=tmp>>53;\
-    tmp=((-(((B)>>12)&ONE64))&(A));\
-    (C)[0]^=tmp<<12;\
-    (C)[1]^=tmp>>52;\
-    tmp=((-(((B)>>13)&ONE64))&(A));\
-    (C)[0]^=tmp<<13;\
-    (C)[1]^=tmp>>51;\
-    tmp=((-(((B)>>14)&ONE64))&(A));\
-    (C)[0]^=tmp<<14;\
-    (C)[1]^=tmp>>50;\
-    tmp=((-(((B)>>15)&ONE64))&(A));\
-    (C)[0]^=tmp<<15;\
-    (C)[1]^=tmp>>49;\
-    tmp=((-(((B)>>16)&ONE64))&(A));\
-    (C)[0]^=tmp<<16;\
-    (C)[1]^=tmp>>48;\
-    tmp=((-(((B)>>17)&ONE64))&(A));\
-    (C)[0]^=tmp<<17;\
-    (C)[1]^=tmp>>47;\
-    tmp=((-(((B)>>18)&ONE64))&(A));\
-    (C)[0]^=tmp<<18;\
-    (C)[1]^=tmp>>46;\
-    tmp=((-(((B)>>19)&ONE64))&(A));\
-    (C)[0]^=tmp<<19;\
-    (C)[1]^=tmp>>45;\
-    tmp=((-(((B)>>20)&ONE64))&(A));\
-    (C)[0]^=tmp<<20;\
-    (C)[1]^=tmp>>44;\
-    tmp=((-(((B)>>21)&ONE64))&(A));\
-    (C)[0]^=tmp<<21;\
-    (C)[1]^=tmp>>43;\
-    tmp=((-(((B)>>22)&ONE64))&(A));\
-    (C)[0]^=tmp<<22;\
-    (C)[1]^=tmp>>42;\
-    tmp=((-(((B)>>23)&ONE64))&(A));\
-    (C)[0]^=tmp<<23;\
-    (C)[1]^=tmp>>41;\
-    tmp=((-(((B)>>24)&ONE64))&(A));\
-    (C)[0]^=tmp<<24;\
-    (C)[1]^=tmp>>40;\
-    tmp=((-(((B)>>25)&ONE64))&(A));\
-    (C)[0]^=tmp<<25;\
-    (C)[1]^=tmp>>39;\
-    tmp=((-(((B)>>26)&ONE64))&(A));\
-    (C)[0]^=tmp<<26;\
-    (C)[1]^=tmp>>38;\
-    tmp=((-(((B)>>27)&ONE64))&(A));\
-    (C)[0]^=tmp<<27;\
-    (C)[1]^=tmp>>37;\
-    tmp=((-(((B)>>28)&ONE64))&(A));\
-    (C)[0]^=tmp<<28;\
-    (C)[1]^=tmp>>36;\
-    tmp=((-(((B)>>29)&ONE64))&(A));\
-    (C)[0]^=tmp<<29;\
-    (C)[1]^=tmp>>35;\
-    tmp=((-(((B)>>30)&ONE64))&(A));\
-    (C)[0]^=tmp<<30;\
-    (C)[1]^=tmp>>34;\
-    tmp=((-(((B)>>31)&ONE64))&(A));\
-    (C)[0]^=tmp<<31;\
-    (C)[1]^=tmp>>33;\
-\
-    tmp=((-(((B)>>32)&ONE64))&(A));\
-    (C)[0]^=tmp<<32;\
-    (C)[1]^=tmp>>32;\
-    tmp=((-(((B)>>33)&ONE64))&(A));\
-    (C)[0]^=tmp<<33;\
-    (C)[1]^=tmp>>31;\
-    tmp=((-(((B)>>34)&ONE64))&(A));\
-    (C)[0]^=tmp<<34;\
-    (C)[1]^=tmp>>30;\
-    tmp=((-(((B)>>35)&ONE64))&(A));\
-    (C)[0]^=tmp<<35;\
-    (C)[1]^=tmp>>29;\
-    tmp=((-(((B)>>36)&ONE64))&(A));\
-    (C)[0]^=tmp<<36;\
-    (C)[1]^=tmp>>28;\
-    tmp=((-(((B)>>37)&ONE64))&(A));\
-    (C)[0]^=tmp<<37;\
-    (C)[1]^=tmp>>27;\
-    tmp=((-(((B)>>38)&ONE64))&(A));\
-    (C)[0]^=tmp<<38;\
-    (C)[1]^=tmp>>26;\
-    tmp=((-(((B)>>39)&ONE64))&(A));\
-    (C)[0]^=tmp<<39;\
-    (C)[1]^=tmp>>25;\
-    tmp=((-(((B)>>40)&ONE64))&(A));\
-    (C)[0]^=tmp<<40;\
-    (C)[1]^=tmp>>24;\
-    tmp=((-(((B)>>41)&ONE64))&(A));\
-    (C)[0]^=tmp<<41;\
-    (C)[1]^=tmp>>23;\
-    tmp=((-(((B)>>42)&ONE64))&(A));\
-    (C)[0]^=tmp<<42;\
-    (C)[1]^=tmp>>22;\
-    tmp=((-(((B)>>43)&ONE64))&(A));\
-    (C)[0]^=tmp<<43;\
-    (C)[1]^=tmp>>21;\
-    tmp=((-(((B)>>44)&ONE64))&(A));\
-    (C)[0]^=tmp<<44;\
-    (C)[1]^=tmp>>20;\
-    tmp=((-(((B)>>45)&ONE64))&(A));\
-    (C)[0]^=tmp<<45;\
-    (C)[1]^=tmp>>19;\
-    tmp=((-(((B)>>46)&ONE64))&(A));\
-    (C)[0]^=tmp<<46;\
-    (C)[1]^=tmp>>18;\
-    tmp=((-(((B)>>47)&ONE64))&(A));\
-    (C)[0]^=tmp<<47;\
-    (C)[1]^=tmp>>17;\
-    tmp=((-(((B)>>48)&ONE64))&(A));\
-    (C)[0]^=tmp<<48;\
-    (C)[1]^=tmp>>16;\
-    tmp=((-(((B)>>49)&ONE64))&(A));\
-    (C)[0]^=tmp<<49;\
-    (C)[1]^=tmp>>15;\
-    tmp=((-(((B)>>50)&ONE64))&(A));\
-    (C)[0]^=tmp<<50;\
-    (C)[1]^=tmp>>14;\
-    tmp=((-(((B)>>51)&ONE64))&(A));\
-    (C)[0]^=tmp<<51;\
-    (C)[1]^=tmp>>13;\
-    tmp=((-(((B)>>52)&ONE64))&(A));\
-    (C)[0]^=tmp<<52;\
-    (C)[1]^=tmp>>12;\
-    tmp=((-(((B)>>53)&ONE64))&(A));\
-    (C)[0]^=tmp<<53;\
-    (C)[1]^=tmp>>11;\
-    tmp=((-(((B)>>54)&ONE64))&(A));\
-    (C)[0]^=tmp<<54;\
-    (C)[1]^=tmp>>10;\
-    tmp=((-(((B)>>55)&ONE64))&(A));\
-    (C)[0]^=tmp<<55;\
-    (C)[1]^=tmp>>9;\
-    tmp=((-(((B)>>56)&ONE64))&(A));\
-    (C)[0]^=tmp<<56;\
-    (C)[1]^=tmp>>8;\
-    tmp=((-(((B)>>57)&ONE64))&(A));\
-    (C)[0]^=tmp<<57;\
-    (C)[1]^=tmp>>7;\
-    tmp=((-(((B)>>58)&ONE64))&(A));\
-    (C)[0]^=tmp<<58;\
-    (C)[1]^=tmp>>6;\
-    tmp=((-(((B)>>59)&ONE64))&(A));\
-    (C)[0]^=tmp<<59;\
-    (C)[1]^=tmp>>5;\
-    tmp=((-(((B)>>60)&ONE64))&(A));\
-    (C)[0]^=tmp<<60;\
-    (C)[1]^=tmp>>4;\
-    tmp=((-(((B)>>61)&ONE64))&(A));\
-    (C)[0]^=tmp<<61;\
-    (C)[1]^=tmp>>3;\
-    tmp=((-(((B)>>62)&ONE64))&(A));\
-    (C)[0]^=tmp<<62;\
-    (C)[1]^=tmp>>2;
+    (tmp)=((-((B)>>63))&(A));\
+    (C)[0]^=(tmp)<<63;\
+    (C)[1]=(tmp)>>1;\
+\
+    (tmp)=((-(((B)>>1)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<1;\
+    (C)[1]^=(tmp)>>63;\
+    (tmp)=((-(((B)>>2)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<2;\
+    (C)[1]^=(tmp)>>62;\
+    (tmp)=((-(((B)>>3)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<3;\
+    (C)[1]^=(tmp)>>61;\
+    (tmp)=((-(((B)>>4)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<4;\
+    (C)[1]^=(tmp)>>60;\
+    (tmp)=((-(((B)>>5)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<5;\
+    (C)[1]^=(tmp)>>59;\
+    (tmp)=((-(((B)>>6)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<6;\
+    (C)[1]^=(tmp)>>58;\
+    (tmp)=((-(((B)>>7)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<7;\
+    (C)[1]^=(tmp)>>57;\
+    (tmp)=((-(((B)>>8)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<8;\
+    (C)[1]^=(tmp)>>56;\
+    (tmp)=((-(((B)>>9)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<9;\
+    (C)[1]^=(tmp)>>55;\
+    (tmp)=((-(((B)>>10)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<10;\
+    (C)[1]^=(tmp)>>54;\
+    (tmp)=((-(((B)>>11)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<11;\
+    (C)[1]^=(tmp)>>53;\
+    (tmp)=((-(((B)>>12)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<12;\
+    (C)[1]^=(tmp)>>52;\
+    (tmp)=((-(((B)>>13)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<13;\
+    (C)[1]^=(tmp)>>51;\
+    (tmp)=((-(((B)>>14)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<14;\
+    (C)[1]^=(tmp)>>50;\
+    (tmp)=((-(((B)>>15)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<15;\
+    (C)[1]^=(tmp)>>49;\
+    (tmp)=((-(((B)>>16)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<16;\
+    (C)[1]^=(tmp)>>48;\
+    (tmp)=((-(((B)>>17)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<17;\
+    (C)[1]^=(tmp)>>47;\
+    (tmp)=((-(((B)>>18)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<18;\
+    (C)[1]^=(tmp)>>46;\
+    (tmp)=((-(((B)>>19)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<19;\
+    (C)[1]^=(tmp)>>45;\
+    (tmp)=((-(((B)>>20)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<20;\
+    (C)[1]^=(tmp)>>44;\
+    (tmp)=((-(((B)>>21)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<21;\
+    (C)[1]^=(tmp)>>43;\
+    (tmp)=((-(((B)>>22)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<22;\
+    (C)[1]^=(tmp)>>42;\
+    (tmp)=((-(((B)>>23)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<23;\
+    (C)[1]^=(tmp)>>41;\
+    (tmp)=((-(((B)>>24)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<24;\
+    (C)[1]^=(tmp)>>40;\
+    (tmp)=((-(((B)>>25)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<25;\
+    (C)[1]^=(tmp)>>39;\
+    (tmp)=((-(((B)>>26)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<26;\
+    (C)[1]^=(tmp)>>38;\
+    (tmp)=((-(((B)>>27)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<27;\
+    (C)[1]^=(tmp)>>37;\
+    (tmp)=((-(((B)>>28)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<28;\
+    (C)[1]^=(tmp)>>36;\
+    (tmp)=((-(((B)>>29)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<29;\
+    (C)[1]^=(tmp)>>35;\
+    (tmp)=((-(((B)>>30)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<30;\
+    (C)[1]^=(tmp)>>34;\
+    (tmp)=((-(((B)>>31)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<31;\
+    (C)[1]^=(tmp)>>33;\
+\
+    (tmp)=((-(((B)>>32)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<32;\
+    (C)[1]^=(tmp)>>32;\
+    (tmp)=((-(((B)>>33)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<33;\
+    (C)[1]^=(tmp)>>31;\
+    (tmp)=((-(((B)>>34)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<34;\
+    (C)[1]^=(tmp)>>30;\
+    (tmp)=((-(((B)>>35)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<35;\
+    (C)[1]^=(tmp)>>29;\
+    (tmp)=((-(((B)>>36)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<36;\
+    (C)[1]^=(tmp)>>28;\
+    (tmp)=((-(((B)>>37)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<37;\
+    (C)[1]^=(tmp)>>27;\
+    (tmp)=((-(((B)>>38)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<38;\
+    (C)[1]^=(tmp)>>26;\
+    (tmp)=((-(((B)>>39)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<39;\
+    (C)[1]^=(tmp)>>25;\
+    (tmp)=((-(((B)>>40)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<40;\
+    (C)[1]^=(tmp)>>24;\
+    (tmp)=((-(((B)>>41)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<41;\
+    (C)[1]^=(tmp)>>23;\
+    (tmp)=((-(((B)>>42)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<42;\
+    (C)[1]^=(tmp)>>22;\
+    (tmp)=((-(((B)>>43)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<43;\
+    (C)[1]^=(tmp)>>21;\
+    (tmp)=((-(((B)>>44)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<44;\
+    (C)[1]^=(tmp)>>20;\
+    (tmp)=((-(((B)>>45)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<45;\
+    (C)[1]^=(tmp)>>19;\
+    (tmp)=((-(((B)>>46)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<46;\
+    (C)[1]^=(tmp)>>18;\
+    (tmp)=((-(((B)>>47)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<47;\
+    (C)[1]^=(tmp)>>17;\
+    (tmp)=((-(((B)>>48)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<48;\
+    (C)[1]^=(tmp)>>16;\
+    (tmp)=((-(((B)>>49)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<49;\
+    (C)[1]^=(tmp)>>15;\
+    (tmp)=((-(((B)>>50)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<50;\
+    (C)[1]^=(tmp)>>14;\
+    (tmp)=((-(((B)>>51)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<51;\
+    (C)[1]^=(tmp)>>13;\
+    (tmp)=((-(((B)>>52)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<52;\
+    (C)[1]^=(tmp)>>12;\
+    (tmp)=((-(((B)>>53)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<53;\
+    (C)[1]^=(tmp)>>11;\
+    (tmp)=((-(((B)>>54)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<54;\
+    (C)[1]^=(tmp)>>10;\
+    (tmp)=((-(((B)>>55)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<55;\
+    (C)[1]^=(tmp)>>9;\
+    (tmp)=((-(((B)>>56)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<56;\
+    (C)[1]^=(tmp)>>8;\
+    (tmp)=((-(((B)>>57)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<57;\
+    (C)[1]^=(tmp)>>7;\
+    (tmp)=((-(((B)>>58)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<58;\
+    (C)[1]^=(tmp)>>6;\
+    (tmp)=((-(((B)>>59)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<59;\
+    (C)[1]^=(tmp)>>5;\
+    (tmp)=((-(((B)>>60)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<60;\
+    (C)[1]^=(tmp)>>4;\
+    (tmp)=((-(((B)>>61)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<61;\
+    (C)[1]^=(tmp)>>3;\
+    (tmp)=((-(((B)>>62)&ONE64))&(A));\
+    (C)[0]^=(tmp)<<62;\
+    (C)[1]^=(tmp)>>2;
 
 
 /* Karatsuba, 1205 = 505*2+189+6 instructions */
@@ -422,8 +422,8 @@
     /*  C[0] = C0
         C[1] = C0^C1^C2
         C[2] = C1^C2 */\
-    AA=(A)[0]^(A)[1];\
-    BB=(B)[0]^(B)[1];\
+    (AA)=(A)[0]^(A)[1];\
+    (BB)=(B)[0]^(B)[1];\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[1]^=RESERVED_BUF2[0];\
     (C)[2]^=RESERVED_BUF2[1];}
@@ -442,8 +442,8 @@
         C[1] = C0^C1^C2
         C[2] = C1^C2^C3
         C[3] = C3 */\
-    AA=(A)[0]^(A)[1];\
-    BB=(B)[0]^(B)[1];\
+    (AA)=(A)[0]^(A)[1];\
+    (BB)=(B)[0]^(B)[1];\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[1]^=RESERVED_BUF2[0];\
     (C)[2]^=RESERVED_BUF2[1];}
@@ -475,20 +475,20 @@
         C[2] = (C0^C1^C2)^(C3^C4)
         C[3] = (C1^C2)^(C3^C4)
         C[4] = C3^C4 */\
-    AA=(A)[0]^(A)[1];\
-    BB=(B)[0]^(B)[1];\
+    (AA)=(A)[0]^(A)[1];\
+    (BB)=(B)[0]^(B)[1];\
     /* (A0+A1)*(B0+B1) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[1]^=RESERVED_BUF2[0];\
     (C)[2]^=RESERVED_BUF2[1];\
-    AA=(A)[1]^(A)[2];\
-    BB=(B)[1]^(B)[2];\
+    (AA)=(A)[1]^(A)[2];\
+    (BB)=(B)[1]^(B)[2];\
     /* (A1+A2)*(B1+B2) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[3]^=RESERVED_BUF2[0];\
     (C)[4]^=RESERVED_BUF2[1];\
-    AA=(A)[0]^(A)[2];\
-    BB=(B)[0]^(B)[2];\
+    (AA)=(A)[0]^(A)[2];\
+    (BB)=(B)[0]^(B)[2];\
     /* (A0+A2)*(B0+B2) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[2]^=RESERVED_BUF2[0];\
@@ -524,20 +524,20 @@
         C[3] = (C1^C2)^(C3^C4^C5)
         C[4] = (C3^C4)^C5
         C[5] = C5 */\
-    AA=(A)[0]^(A)[1];\
-    BB=(B)[0]^(B)[1];\
+    (AA)=(A)[0]^(A)[1];\
+    (BB)=(B)[0]^(B)[1];\
     /* (A0+A1)*(B0+B1) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[1]^=RESERVED_BUF2[0];\
     (C)[2]^=RESERVED_BUF2[1];\
-    AA=(A)[1]^(A)[2];\
-    BB=(B)[1]^(B)[2];\
+    (AA)=(A)[1]^(A)[2];\
+    (BB)=(B)[1]^(B)[2];\
     /* (A1+A2)*(B1+B2) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[3]^=RESERVED_BUF2[0];\
     (C)[4]^=RESERVED_BUF2[1];\
-    AA=(A)[0]^(A)[2];\
-    BB=(B)[0]^(B)[2];\
+    (AA)=(A)[0]^(A)[2];\
+    (BB)=(B)[0]^(B)[2];\
     /* (A0+A2)*(B0+B2) */\
     MUL64_NO_SIMD_GF2X(RESERVED_BUF2,AA,BB,tmp);\
     (C)[2]^=RESERVED_BUF2[0];\
@@ -998,15 +998,15 @@
 /* ~ 2*8 = 16 instructions */
 /* Classical, 31 = 9+10+12 instructions */
 #define PMUL16_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one16) \
-    RA=PSET1_16(A0);\
-    RB=PSET_16((B0)>>14,(B0)>>10,(B0)>>6,(B0)>>2,(B0)>>12,(B0)>>8,(B0)>>4,B0);\
+    (RA)=PSET1_16(A0);\
+    (RB)=PSET_16((B0)>>14,(B0)>>10,(B0)>>6,(B0)>>2,(B0)>>12,(B0)>>8,(B0)>>4,B0);\
 \
-    CL=PAND_(RA,PMASK16_ONE(PAND_(RB,one16),one16));\
-    M=PAND_(RA,PMASK16_ONE(PAND_(PSRLI_16(RB,1),one16),one16));\
+    (CL)=PAND_(RA,PMASK16_ONE(PAND_(RB,one16),one16));\
+    (M)=PAND_(RA,PMASK16_ONE(PAND_(PSRLI_16(RB,1),one16),one16));\
     PXOR1_2(CL,PSLLI_16(M,1));\
-    CH=PSRLI_16(M,15);\
+    (CH)=PSRLI_16(M,15);\
 \
-    C1=PXOR_(PUNPACKLO_16(CL,CH),PSLLI_32(PUNPACKHI_16(CL,CH),2));\
+    (C1)=PXOR_(PUNPACKLO_16(CL,CH),PSLLI_32(PUNPACKHI_16(CL,CH),2));\
     PXOR1_2(C1,PSRLI_128(C1,7));\
     PXOR1_2(C1,PSLLI_32(PSRLI_128(C1,4),4));\
     PAND1_2(C1,PSET_32(0,0,0,MONE32));
@@ -1015,37 +1015,37 @@
 /* ~ 4*6 = 24 instructions */
 /* Classical, 33 = 5+21+7 instructions */
 #define PMUL16_WS_CLAS0_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32) \
-    RA=PSET1_32(A0);\
-    RB=PSET_32((B0)>>12,(B0)>>4,(B0)>>8,B0);\
+    (RA)=PSET1_32(A0);\
+    (RB)=PSET_32((B0)>>12,(B0)>>4,(B0)>>8,B0);\
 \
-    CL=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32));\
+    (CL)=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,1));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,2));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,3));\
 \
-    CH=PXOR_(CL,PSRLI_128(PSLLI_32(CL,4),8));\
-    C1=PXOR_(CH,PSRLI_128(CH,3));\
+    (CH)=PXOR_(CL,PSRLI_128(PSLLI_32(CL,4),8));\
+    (C1)=PXOR_(CH,PSRLI_128(CH,3));\
     PAND1_2(C1,PSET_32(0,0,0,MONE32));
 
 
 /* ~ 8*8 = 64 instructions */
 /* Classical, 72 = 5+59+8 instructions */
 #define PMUL32_NO_UNROLLED_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32,i) \
-    RA=PSET1_32(A0);\
-    RB=PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
+    (RA)=PSET1_32(A0);\
+    (RB)=PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
 \
-    CL=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
-    CH=PSETZERO();\
-    for(i=1;i<8;++i)\
+    (CL)=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
+    (CH)=PSETZERO();\
+    for((i)=1;(i)<8;++(i))\
     {\
-        M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,i),one32),one32));\
+        (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,i),one32),one32));\
         PXOR1_2(CL,PSLLI_32(M,i));\
-        PXOR1_2(CH,PSRLI_32(M,32-i));\
+        PXOR1_2(CH,PSRLI_32(M,32-(i)));\
     }\
-    C1=PXOR_(PUNPACKLO_32(CL,CH),PSLLI_128(PUNPACKHI_32(CL,CH),1));\
+    (C1)=PXOR_(PUNPACKLO_32(CL,CH),PSLLI_128(PUNPACKHI_32(CL,CH),1));\
     PXOR1_2(C1,PSRLI_128(C1,6));\
     PAND1_2(C1,PSET_64(0,MONE64));
 
@@ -1054,34 +1054,34 @@
 /* Classical, 71 = 5+58+8 instructions */
 /* The fastest method */
 #define PMUL32_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32) \
-    RA=PSET1_32(A0);\
-    RB=PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
+    (RA)=PSET1_32(A0);\
+    (RB)=PSET_32((B0)>>24,(B0)>>8,(B0)>>16,B0);\
 \
-    CL=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32));\
+    (CL)=PAND_(RA,PMASK32_ONE(PAND_(RB,one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,1));\
-    CH=PSRLI_32(M,31);\
+    (CH)=PSRLI_32(M,31);\
 \
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,2));\
     PXOR1_2(CH,PSRLI_32(M,30));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,3));\
     PXOR1_2(CH,PSRLI_32(M,29));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,4),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,4),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,4));\
     PXOR1_2(CH,PSRLI_32(M,28));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,5),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,5),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,5));\
     PXOR1_2(CH,PSRLI_32(M,27));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,6),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,6),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,6));\
     PXOR1_2(CH,PSRLI_32(M,26));\
-    M=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,7),one32),one32));\
+    (M)=PAND_(RA,PMASK32_ONE(PAND_(PSRLI_32(RB,7),one32),one32));\
     PXOR1_2(CL,PSLLI_32(M,7));\
     PXOR1_2(CH,PSRLI_32(M,25));\
 \
-    C1=PXOR_(PUNPACKLO_32(CL,CH),PSLLI_128(PUNPACKHI_32(CL,CH),1));\
+    (C1)=PXOR_(PUNPACKLO_32(CL,CH),PSLLI_128(PUNPACKHI_32(CL,CH),1));\
     PXOR1_2(C1,PSRLI_128(C1,6));\
     PAND1_2(C1,PSET_64(0,MONE64));
 
@@ -1091,11 +1091,11 @@
 #define PMUL32_WS_KAR_CLAS16_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one16) \
     PMUL16_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one16);\
     PMUL16_WS_CLAS_GF2X(M,(A0)>>16,(B0)>>16,RA,RB,CL,CH,M,one16);\
-    CM=PXOR_(C1,M);\
+    (CM)=PXOR_(C1,M);\
     PXOR1_2(C1,PSLLI_128(M,4));\
     PMUL16_WS_CLAS_GF2X(M,(A0)^((A0)>>16),(B0)^((B0)>>16),RA,RB,CL,CH,M,one16);\
 \
-    M=PXOR_(CM,M);\
+    (M)=PXOR_(CM,M);\
     PXOR1_2(C1,PSLLI_128(M,2));
 
 
@@ -1104,165 +1104,165 @@
 #define PMUL32_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one32) \
     PMUL16_WS_CLAS0_GF2X(C1,(A0)&MONE16,B0,RA,RB,CL,CH,M,one32);\
     PMUL16_WS_CLAS0_GF2X(M,((A0)>>16)&MONE16,(B0)>>16,RA,RB,CL,CH,M,one32);\
-    CM=PXOR_(C1,M);\
+    (CM)=PXOR_(C1,M);\
     PXOR1_2(C1,PSLLI_128(M,4));\
     PMUL16_WS_CLAS0_GF2X(M,((A0)^((A0)>>16))&MONE16,(B0)^((B0)>>16),\
                          RA,RB,CL,CH,M,one32);\
 \
-    M=PXOR_(CM,M);\
+    (M)=PXOR_(CM,M);\
     PXOR1_2(C1,PSLLI_128(M,2));
 
 
 /* ~ 32*8 = 256 instructions */
 /* Classical, 258 = 3+251+4 instructions */
 #define PMUL64_NO_UNROLLED_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one64,i) \
-    RA=PSET1_64(A0);\
-    RB=PSET_64((B0)>>32,B0);\
+    (RA)=PSET1_64(A0);\
+    (RB)=PSET_64((B0)>>32,B0);\
 \
-    CL=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
-    CH=PSETZERO();\
-    for(i=1;i<32;++i)\
+    (CL)=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
+    (CH)=PSETZERO();\
+    for((i)=1;(i)<32;++(i))\
     {\
-        M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64));\
+        (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64));\
         PXOR1_2(CL,PSLLI_64(M,i));\
-        PXOR1_2(CH,PSRLI_64(M,64-i));\
+        PXOR1_2(CH,PSRLI_64(M,64-(i)));\
     }\
-    C1=PXOR_(PUNPACKLO_64(CL,CH),PSLLI_128(PUNPACKHI_64(CL,CH),4));
+    (C1)=PXOR_(PUNPACKLO_64(CL,CH),PSLLI_128(PUNPACKHI_64(CL,CH),4));
 
 
 /* ~ 32*8 = 256 instructions */
 /* Classical, 257 = 3+250+4 instructions */
 #define PMUL64_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one64) \
-    RA=PSET1_64(A0);\
-    RB=PSET_64((B0)>>32,B0);\
+    (RA)=PSET1_64(A0);\
+    (RB)=PSET_64((B0)>>32,B0);\
 \
-    CL=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64));\
+    (CL)=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,1));\
-    CH=PSRLI_64(M,63);\
+    (CH)=PSRLI_64(M,63);\
 \
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,2));\
     PXOR1_2(CH,PSRLI_64(M,62));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,3));\
     PXOR1_2(CH,PSRLI_64(M,61));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,4));\
     PXOR1_2(CH,PSRLI_64(M,60));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,5));\
     PXOR1_2(CH,PSRLI_64(M,59));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,6));\
     PXOR1_2(CH,PSRLI_64(M,58));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,7));\
     PXOR1_2(CH,PSRLI_64(M,57));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,8));\
     PXOR1_2(CH,PSRLI_64(M,56));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,9));\
     PXOR1_2(CH,PSRLI_64(M,55));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,10));\
     PXOR1_2(CH,PSRLI_64(M,54));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,11));\
     PXOR1_2(CH,PSRLI_64(M,53));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,12));\
     PXOR1_2(CH,PSRLI_64(M,52));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,13));\
     PXOR1_2(CH,PSRLI_64(M,51));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,14));\
     PXOR1_2(CH,PSRLI_64(M,50));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,15));\
     PXOR1_2(CH,PSRLI_64(M,49));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,16));\
     PXOR1_2(CH,PSRLI_64(M,48));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,17));\
     PXOR1_2(CH,PSRLI_64(M,47));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,18));\
     PXOR1_2(CH,PSRLI_64(M,46));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,19));\
     PXOR1_2(CH,PSRLI_64(M,45));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,20));\
     PXOR1_2(CH,PSRLI_64(M,44));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,21));\
     PXOR1_2(CH,PSRLI_64(M,43));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,22));\
     PXOR1_2(CH,PSRLI_64(M,42));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,23));\
     PXOR1_2(CH,PSRLI_64(M,41));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,24));\
     PXOR1_2(CH,PSRLI_64(M,40));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,25));\
     PXOR1_2(CH,PSRLI_64(M,39));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,26));\
     PXOR1_2(CH,PSRLI_64(M,38));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,27));\
     PXOR1_2(CH,PSRLI_64(M,37));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,28));\
     PXOR1_2(CH,PSRLI_64(M,36));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,29));\
     PXOR1_2(CH,PSRLI_64(M,35));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,30));\
     PXOR1_2(CH,PSRLI_64(M,34));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,31));\
     PXOR1_2(CH,PSRLI_64(M,33));\
 \
-    C1=PXOR_(PUNPACKLO_64(CL,CH),PSLLI_128(PUNPACKHI_64(CL,CH),4));
+    (C1)=PXOR_(PUNPACKLO_64(CL,CH),PSLLI_128(PUNPACKHI_64(CL,CH),4));
 
 
 /* ~ 16*13 = 208 instructions */
 /* Classical, 220 = 7+199+14 instructions */
 #define PMUL64_NO_UNROLLED_WS_CLAS2_GF2X(C1,A0,B0,RA,RAM,RB,CL,CH,CLM,CHM,M,\
                                          one32,i) \
-    RA=PSET_32((A0)>>32,(A0)>>32,A0,A0);\
-    RAM=PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
-    RB=PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
-\
-    C1=PMASK32_ONE(PAND_(RB,one32),one32);\
-    CL=PAND_(RA,C1);\
-    CH=PSETZERO();\
-    CLM=PAND_(RAM,C1);\
-    CHM=PSETZERO();\
-    for(i=1;i<16;++i)\
+    (RA)=PSET_32((A0)>>32,(A0)>>32,A0,A0);\
+    (RAM)=PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
+    (RB)=PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
+\
+    (C1)=PMASK32_ONE(PAND_(RB,one32),one32);\
+    (CL)=PAND_(RA,C1);\
+    (CH)=PSETZERO();\
+    (CLM)=PAND_(RAM,C1);\
+    (CHM)=PSETZERO();\
+    for((i)=1;(i)<16;++(i))\
     {\
-        C1=PMASK32_ONE(PAND_(PSRLI_32(RB,i),one32),one32);\
-        M=PAND_(RA,C1);\
+        (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,i),one32),one32);\
+        (M)=PAND_(RA,C1);\
         PXOR1_2(CL,PSLLI_32(M,i));\
-        PXOR1_2(CH,PSRLI_32(M,32-i));\
-        M=PAND_(RAM,C1);\
+        PXOR1_2(CH,PSRLI_32(M,32-(i)));\
+        (M)=PAND_(RAM,C1);\
         PXOR1_2(CLM,PSLLI_32(M,i));\
-        PXOR1_2(CHM,PSRLI_32(M,32-i));\
+        PXOR1_2(CHM,PSRLI_32(M,32-(i)));\
     }\
 \
-    RAM=PXOR_(PUNPACKLO_32(CLM,CHM),PUNPACKHI_32(CLM,CHM));\
-    CLM=PUNPACKLO_32(CL,CH);\
-    CHM=PUNPACKHI_32(CL,CH);\
-    C1=PXOR_(PUNPACKLO_64(CLM,CHM),PSLLI_128(PUNPACKHI_64(CLM,CHM),2));\
+    (RAM)=PXOR_(PUNPACKLO_32(CLM,CHM),PUNPACKHI_32(CLM,CHM));\
+    (CLM)=PUNPACKLO_32(CL,CH);\
+    (CHM)=PUNPACKHI_32(CL,CH);\
+    (C1)=PXOR_(PUNPACKLO_64(CLM,CHM),PSLLI_128(PUNPACKHI_64(CLM,CHM),2));\
     PXOR1_2(C1,\
             PSLLI_128(PAND_(PXOR_(RAM,PSRLI_128(RAM,6)),PSET_64(0,MONE64)),4));
 
@@ -1271,124 +1271,124 @@
 /* Classical, 219 = 7+198+14 instructions */
 /* The fastest method */
 #define PMUL64_WS_CLAS2_GF2X(C1,A0,B0,RA,RAM,RB,CL,CH,CLM,CHM,M,one32) \
-    RA=PSET_32((A0)>>32,(A0)>>32,A0,A0);\
-    RAM=PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
-    RB=PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
-\
-    C1=PMASK32_ONE(PAND_(RB,one32),one32);\
-    CL=PAND_(RA,C1);\
-    CLM=PAND_(RAM,C1);\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32);\
-    M=PAND_(RA,C1);\
+    (RA)=PSET_32((A0)>>32,(A0)>>32,A0,A0);\
+    (RAM)=PSET_32(A0,A0,(A0)>>32,(A0)>>32);\
+    (RB)=PSET_32((B0)>>48,(B0)>>32,(B0)>>16,B0);\
+\
+    (C1)=PMASK32_ONE(PAND_(RB,one32),one32);\
+    (CL)=PAND_(RA,C1);\
+    (CLM)=PAND_(RAM,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,1),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,1));\
-    CH=PSRLI_32(M,31);\
-    M=PAND_(RAM,C1);\
+    (CH)=PSRLI_32(M,31);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,1));\
-    CHM=PSRLI_32(M,31);\
+    (CHM)=PSRLI_32(M,31);\
 \
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,2),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,2));\
     PXOR1_2(CH,PSRLI_32(M,30));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,2));\
     PXOR1_2(CHM,PSRLI_32(M,30));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,3),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,3));\
     PXOR1_2(CH,PSRLI_32(M,29));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,3));\
     PXOR1_2(CHM,PSRLI_32(M,29));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,4),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,4),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,4));\
     PXOR1_2(CH,PSRLI_32(M,28));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,4));\
     PXOR1_2(CHM,PSRLI_32(M,28));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,5),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,5),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,5));\
     PXOR1_2(CH,PSRLI_32(M,27));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,5));\
     PXOR1_2(CHM,PSRLI_32(M,27));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,6),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,6),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,6));\
     PXOR1_2(CH,PSRLI_32(M,26));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,6));\
     PXOR1_2(CHM,PSRLI_32(M,26));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,7),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,7),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,7));\
     PXOR1_2(CH,PSRLI_32(M,25));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,7));\
     PXOR1_2(CHM,PSRLI_32(M,25));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,8),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,8),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,8));\
     PXOR1_2(CH,PSRLI_32(M,24));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,8));\
     PXOR1_2(CHM,PSRLI_32(M,24));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,9),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,9),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,9));\
     PXOR1_2(CH,PSRLI_32(M,23));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,9));\
     PXOR1_2(CHM,PSRLI_32(M,23));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,10),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,10),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,10));\
     PXOR1_2(CH,PSRLI_32(M,22));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,10));\
     PXOR1_2(CHM,PSRLI_32(M,22));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,11),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,11),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,11));\
     PXOR1_2(CH,PSRLI_32(M,21));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,11));\
     PXOR1_2(CHM,PSRLI_32(M,21));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,12),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,12),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,12));\
     PXOR1_2(CH,PSRLI_32(M,20));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,12));\
     PXOR1_2(CHM,PSRLI_32(M,20));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,13),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,13),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,13));\
     PXOR1_2(CH,PSRLI_32(M,19));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,13));\
     PXOR1_2(CHM,PSRLI_32(M,19));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,14),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,14),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,14));\
     PXOR1_2(CH,PSRLI_32(M,18));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,14));\
     PXOR1_2(CHM,PSRLI_32(M,18));\
-    C1=PMASK32_ONE(PAND_(PSRLI_32(RB,15),one32),one32);\
-    M=PAND_(RA,C1);\
+    (C1)=PMASK32_ONE(PAND_(PSRLI_32(RB,15),one32),one32);\
+    (M)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_32(M,15));\
     PXOR1_2(CH,PSRLI_32(M,17));\
-    M=PAND_(RAM,C1);\
+    (M)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_32(M,15));\
     PXOR1_2(CHM,PSRLI_32(M,17));\
 \
-    RAM=PXOR_(PUNPACKLO_32(CLM,CHM),PUNPACKHI_32(CLM,CHM));\
-    CLM=PUNPACKLO_32(CL,CH);\
-    CHM=PUNPACKHI_32(CL,CH);\
-    C1=PXOR_(PUNPACKLO_64(CLM,CHM),PSLLI_128(PUNPACKHI_64(CLM,CHM),2));\
+    (RAM)=PXOR_(PUNPACKLO_32(CLM,CHM),PUNPACKHI_32(CLM,CHM));\
+    (CLM)=PUNPACKLO_32(CL,CH);\
+    (CHM)=PUNPACKHI_32(CL,CH);\
+    (C1)=PXOR_(PUNPACKLO_64(CLM,CHM),PSLLI_128(PUNPACKHI_64(CLM,CHM),2));\
     PXOR1_2(C1,\
             PSLLI_128(PAND_(PXOR_(RAM,PSRLI_128(RAM,6)),PSET_64(0,MONE64)),4));
 
@@ -1397,12 +1397,12 @@
 #define PMUL64_WS_KAR_KAR32_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,CM1,CM2,one32) \
     PMUL32_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM1,one32);\
     PMUL32_WS_KAR_GF2X(M,(A0)>>32,(B0)>>32,RA,RB,CL,CH,CM1,CM2,one32);\
-    CM=PXOR_(C1,M);\
+    (CM)=PXOR_(C1,M);\
     PXOR1_2(C1,PSLLI_128(M,8));\
     PMUL32_WS_KAR_GF2X(M,(A0)^((A0)>>32),(B0)^((B0)>>32),\
                        RA,RB,CL,CH,CM1,CM2,one32);\
 \
-    M=PXOR_(CM,M);\
+    (M)=PXOR_(CM,M);\
     PXOR1_2(C1,PSLLI_128(M,4));
 
 
@@ -1411,11 +1411,11 @@
 #define PMUL64_WS_KAR_GF2X(C1,A0,B0,RA,RB,CL,CH,M,CM,one32) \
     PMUL32_WS_CLAS_GF2X(C1,A0,B0,RA,RB,CL,CH,M,one32);\
     PMUL32_WS_CLAS_GF2X(M,(A0)>>32,(B0)>>32,RA,RB,CL,CH,M,one32);\
-    CM=PXOR_(C1,M);\
+    (CM)=PXOR_(C1,M);\
     PXOR1_2(C1,PSLLI_128(M,8));\
     PMUL32_WS_CLAS_GF2X(M,(A0)^((A0)>>32),(B0)^((B0)>>32),RA,RB,CL,CH,M,one32);\
 \
-    M=PXOR_(CM,M);\
+    (M)=PXOR_(CM,M);\
     PXOR1_2(C1,PSLLI_128(M,4));
 
 
@@ -1424,223 +1424,223 @@
 /* Classical, 511 = 2+507+2 instructions */
 #define PMUL64x2_NO_UNROLLED_WS_CLAS_GF2X(C1,C2,A0,A1,B0,B1,RA,RB,CL,CH,M,\
                                           one64,i) \
-    RA=PSET_64(A1,A0);\
-    RB=PSET_64(B1,B0);\
+    (RA)=PSET_64(A1,A0);\
+    (RB)=PSET_64(B1,B0);\
 \
-    CL=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
-    CH=PSETZERO();\
-    for(i=1;i<64;++i)\
+    (CL)=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
+    (CH)=PSETZERO();\
+    for((i)=1;(i)<64;++(i))\
     {\
-        M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64));\
+        (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64));\
         PXOR1_2(CL,PSLLI_64(M,i));\
-        PXOR1_2(CH,PSRLI_64(M,64-i));\
+        PXOR1_2(CH,PSRLI_64(M,64-(i)));\
     }\
-    C1=PUNPACKLO_64(CL,CH);\
-    C2=PUNPACKHI_64(CL,CH);
+    (C1)=PUNPACKLO_64(CL,CH);\
+    (C2)=PUNPACKHI_64(CL,CH);
 
 
 /* ~ 64*8 = 512 instructions */
 /* Classical, 509 = 2+505+2 instructions */
 #define PMUL64x2_WS_CLAS_GF2X(C1,C2,A0,A1,B0,B1,RA,RB,M,one64) \
-    RA=PSET_64(A1,A0);\
-    RB=PSET_64(B1,B0);\
+    (RA)=PSET_64(A1,A0);\
+    (RB)=PSET_64(B1,B0);\
 \
-    CL=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64));\
+    (CL)=PAND_(RA,PMASK64_ONE(PAND_(RB,one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,1));\
-    CH=PSRLI_64(M,63);\
+    (CH)=PSRLI_64(M,63);\
 \
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,2));\
     PXOR1_2(CH,PSRLI_64(M,62));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,3));\
     PXOR1_2(CH,PSRLI_64(M,61));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,4));\
     PXOR1_2(CH,PSRLI_64(M,60));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,5));\
     PXOR1_2(CH,PSRLI_64(M,59));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,6));\
     PXOR1_2(CH,PSRLI_64(M,58));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,7));\
     PXOR1_2(CH,PSRLI_64(M,57));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,8));\
     PXOR1_2(CH,PSRLI_64(M,56));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,9));\
     PXOR1_2(CH,PSRLI_64(M,55));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,10));\
     PXOR1_2(CH,PSRLI_64(M,54));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,11));\
     PXOR1_2(CH,PSRLI_64(M,53));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,12));\
     PXOR1_2(CH,PSRLI_64(M,52));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,13));\
     PXOR1_2(CH,PSRLI_64(M,51));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,14));\
     PXOR1_2(CH,PSRLI_64(M,50));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,15));\
     PXOR1_2(CH,PSRLI_64(M,49));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,16));\
     PXOR1_2(CH,PSRLI_64(M,48));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,17));\
     PXOR1_2(CH,PSRLI_64(M,47));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,18));\
     PXOR1_2(CH,PSRLI_64(M,46));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,19));\
     PXOR1_2(CH,PSRLI_64(M,45));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,20));\
     PXOR1_2(CH,PSRLI_64(M,44));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,21));\
     PXOR1_2(CH,PSRLI_64(M,43));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,22));\
     PXOR1_2(CH,PSRLI_64(M,42));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,23));\
     PXOR1_2(CH,PSRLI_64(M,41));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,24));\
     PXOR1_2(CH,PSRLI_64(M,40));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,25));\
     PXOR1_2(CH,PSRLI_64(M,39));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,26));\
     PXOR1_2(CH,PSRLI_64(M,38));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,27));\
     PXOR1_2(CH,PSRLI_64(M,37));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,28));\
     PXOR1_2(CH,PSRLI_64(M,36));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,29));\
     PXOR1_2(CH,PSRLI_64(M,35));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,30));\
     PXOR1_2(CH,PSRLI_64(M,34));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,31));\
     PXOR1_2(CH,PSRLI_64(M,33));\
 \
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,32),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,32),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,32));\
     PXOR1_2(CH,PSRLI_64(M,32));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,33),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,33),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,33));\
     PXOR1_2(CH,PSRLI_64(M,31));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,34),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,34),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,34));\
     PXOR1_2(CH,PSRLI_64(M,30));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,35),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,35),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,35));\
     PXOR1_2(CH,PSRLI_64(M,29));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,36),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,36),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,36));\
     PXOR1_2(CH,PSRLI_64(M,28));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,37),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,37),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,37));\
     PXOR1_2(CH,PSRLI_64(M,27));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,38),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,38),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,38));\
     PXOR1_2(CH,PSRLI_64(M,26));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,39),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,39),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,39));\
     PXOR1_2(CH,PSRLI_64(M,25));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,40),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,40),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,40));\
     PXOR1_2(CH,PSRLI_64(M,24));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,41),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,41),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,41));\
     PXOR1_2(CH,PSRLI_64(M,23));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,42),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,42),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,42));\
     PXOR1_2(CH,PSRLI_64(M,22));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,43),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,43),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,43));\
     PXOR1_2(CH,PSRLI_64(M,21));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,44),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,44),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,44));\
     PXOR1_2(CH,PSRLI_64(M,20));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,45),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,45),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,45));\
     PXOR1_2(CH,PSRLI_64(M,19));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,46),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,46),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,46));\
     PXOR1_2(CH,PSRLI_64(M,18));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,47),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,47),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,47));\
     PXOR1_2(CH,PSRLI_64(M,17));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,48),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,48),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,48));\
     PXOR1_2(CH,PSRLI_64(M,16));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,49),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,49),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,49));\
     PXOR1_2(CH,PSRLI_64(M,15));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,50),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,50),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,50));\
     PXOR1_2(CH,PSRLI_64(M,14));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,51),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,51),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,51));\
     PXOR1_2(CH,PSRLI_64(M,13));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,52),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,52),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,52));\
     PXOR1_2(CH,PSRLI_64(M,12));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,53),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,53),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,53));\
     PXOR1_2(CH,PSRLI_64(M,11));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,54),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,54),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,54));\
     PXOR1_2(CH,PSRLI_64(M,10));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,55),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,55),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,55));\
     PXOR1_2(CH,PSRLI_64(M,9));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,56),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,56),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,56));\
     PXOR1_2(CH,PSRLI_64(M,8));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,57),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,57),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,57));\
     PXOR1_2(CH,PSRLI_64(M,7));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,58),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,58),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,58));\
     PXOR1_2(CH,PSRLI_64(M,6));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,59),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,59),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,59));\
     PXOR1_2(CH,PSRLI_64(M,5));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,60),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,60),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,60));\
     PXOR1_2(CH,PSRLI_64(M,4));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,61),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,61),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,61));\
     PXOR1_2(CH,PSRLI_64(M,3));\
-    M=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,62),one64),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PAND_(PSRLI_64(RB,62),one64),one64));\
     PXOR1_2(CL,PSLLI_64(M,62));\
     PXOR1_2(CH,PSRLI_64(M,2));\
     /* Optimization: the '&1' is removed */\
-    M=PAND_(RA,PMASK64_ONE(PSRLI_64(RB,63),one64));\
+    (M)=PAND_(RA,PMASK64_ONE(PSRLI_64(RB,63),one64));\
     PXOR1_2(CL,PSLLI_64(M,63));\
     PXOR1_2(CH,PSRLI_64(M,1));\
 \
-    C1=PUNPACKLO_64(CL,CH);\
-    C2=PUNPACKHI_64(CL,CH);\
+    (C1)=PUNPACKLO_64(CL,CH);\
+    (C2)=PUNPACKHI_64(CL,CH);\
 
 
 /* Karatsuba, 525 = 223*2+71*1+8 instructions */
@@ -1660,29 +1660,29 @@
 /* The fastest classical method */
 #define PMUL128_NO_UNROLLED_WS_CLAS_GF2X(C1,C2,A,B,RA,RAM,RB,CL,CH,CLM,CHM,\
                                          one64,i) \
-    RA=PSET_64((A)[1],(A)[0]);\
-    RAM=PSET_64((A)[0],(A)[1]);\
-    RB=PSET_64((B)[1],(B)[0]);\
-\
-    C1=PMASK64_ONE(PAND_(RB,one64),one64);\
-    CL=PAND_(RA,C1);\
-    CH=PSETZERO();\
-    CLM=PAND_(RAM,C1);\
-    CHM=PSETZERO();\
-    for(i=1;i<64;++i)\
+    (RA)=PSET_64((A)[1],(A)[0]);\
+    (RAM)=PSET_64((A)[0],(A)[1]);\
+    (RB)=PSET_64((B)[1],(B)[0]);\
+\
+    (C1)=PMASK64_ONE(PAND_(RB,one64),one64);\
+    (CL)=PAND_(RA,C1);\
+    (CH)=PSETZERO();\
+    (CLM)=PAND_(RAM,C1);\
+    (CHM)=PSETZERO();\
+    for((i)=1;(i)<64;++(i))\
     {\
-        C1=PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64);\
-        C2=PAND_(RA,C1);\
+        (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,i),one64),one64);\
+        (C2)=PAND_(RA,C1);\
         PXOR1_2(CL,PSLLI_64(C2,i));\
-        PXOR1_2(CH,PSRLI_64(C2,64-i));\
-        C2=PAND_(RAM,C1);\
+        PXOR1_2(CH,PSRLI_64(C2,64-(i)));\
+        (C2)=PAND_(RAM,C1);\
         PXOR1_2(CLM,PSLLI_64(C2,i));\
-        PXOR1_2(CHM,PSRLI_64(C2,64-i));\
+        PXOR1_2(CHM,PSRLI_64(C2,64-(i)));\
     }\
-    C1=PUNPACKLO_64(CL,CH);\
-    C2=PUNPACKHI_64(CL,CH);\
+    (C1)=PUNPACKLO_64(CL,CH);\
+    (C2)=PUNPACKHI_64(CL,CH);\
 \
-    RAM=PXOR_(PUNPACKLO_64(CLM,CHM),PUNPACKHI_64(CLM,CHM));\
+    (RAM)=PXOR_(PUNPACKLO_64(CLM,CHM),PUNPACKHI_64(CLM,CHM));\
     PXOR1_2(C1,PLSHIFT64(RAM));\
     PXOR1_2(C2,PRSHIFT64(RAM));
 
@@ -1690,462 +1690,462 @@
 /* ~ 64*13 = 832 instructions */
 /* Classical, 832 = 3+820+9 instructions */
 #define PMUL128_WS_CLAS_GF2X(C1,C2,A,B,RA,RAM,RB,CL,CH,CLM,CHM,one64) \
-    RA=PSET_64((A)[1],(A)[0]);\
-    RAM=PSET_64((A)[0],(A)[1]);\
-    RB=PSET_64((B)[1],(B)[0]);\
-\
-    C1=PMASK64_ONE(PAND_(RB,one64),one64);\
-    CL=PAND_(RA,C1);\
-    CLM=PAND_(RAM,C1);\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (RA)=PSET_64((A)[1],(A)[0]);\
+    (RAM)=PSET_64((A)[0],(A)[1]);\
+    (RB)=PSET_64((B)[1],(B)[0]);\
+\
+    (C1)=PMASK64_ONE(PAND_(RB,one64),one64);\
+    (CL)=PAND_(RA,C1);\
+    (CLM)=PAND_(RAM,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,1),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,1));\
-    CH=PSRLI_64(C2,63);\
-    C2=PAND_(RAM,C1);\
+    (CH)=PSRLI_64(C2,63);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,1));\
-    CHM=PSRLI_64(C2,63);\
+    (CHM)=PSRLI_64(C2,63);\
 \
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,2),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,2));\
     PXOR1_2(CH,PSRLI_64(C2,62));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,2));\
     PXOR1_2(CHM,PSRLI_64(C2,62));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,3),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,3));\
     PXOR1_2(CH,PSRLI_64(C2,61));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,3));\
     PXOR1_2(CHM,PSRLI_64(C2,61));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,4),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,4));\
     PXOR1_2(CH,PSRLI_64(C2,60));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,4));\
     PXOR1_2(CHM,PSRLI_64(C2,60));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,5),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,5));\
     PXOR1_2(CH,PSRLI_64(C2,59));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,5));\
     PXOR1_2(CHM,PSRLI_64(C2,59));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,6),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,6));\
     PXOR1_2(CH,PSRLI_64(C2,58));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,6));\
     PXOR1_2(CHM,PSRLI_64(C2,58));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,7),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,7));\
     PXOR1_2(CH,PSRLI_64(C2,57));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,7));\
     PXOR1_2(CHM,PSRLI_64(C2,57));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,8),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,8));\
     PXOR1_2(CH,PSRLI_64(C2,56));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,8));\
     PXOR1_2(CHM,PSRLI_64(C2,56));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,9),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,9));\
     PXOR1_2(CH,PSRLI_64(C2,55));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,9));\
     PXOR1_2(CHM,PSRLI_64(C2,55));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,10),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,10));\
     PXOR1_2(CH,PSRLI_64(C2,54));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,10));\
     PXOR1_2(CHM,PSRLI_64(C2,54));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,11),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,11));\
     PXOR1_2(CH,PSRLI_64(C2,53));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,11));\
     PXOR1_2(CHM,PSRLI_64(C2,53));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,12),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,12));\
     PXOR1_2(CH,PSRLI_64(C2,52));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,12));\
     PXOR1_2(CHM,PSRLI_64(C2,52));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,13),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,13));\
     PXOR1_2(CH,PSRLI_64(C2,51));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,13));\
     PXOR1_2(CHM,PSRLI_64(C2,51));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,14),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,14));\
     PXOR1_2(CH,PSRLI_64(C2,50));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,14));\
     PXOR1_2(CHM,PSRLI_64(C2,50));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,15),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,15));\
     PXOR1_2(CH,PSRLI_64(C2,49));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,15));\
     PXOR1_2(CHM,PSRLI_64(C2,49));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,16),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,16));\
     PXOR1_2(CH,PSRLI_64(C2,48));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,16));\
     PXOR1_2(CHM,PSRLI_64(C2,48));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,17),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,17));\
     PXOR1_2(CH,PSRLI_64(C2,47));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,17));\
     PXOR1_2(CHM,PSRLI_64(C2,47));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,18),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,18));\
     PXOR1_2(CH,PSRLI_64(C2,46));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,18));\
     PXOR1_2(CHM,PSRLI_64(C2,46));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,19),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,19));\
     PXOR1_2(CH,PSRLI_64(C2,45));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,19));\
     PXOR1_2(CHM,PSRLI_64(C2,45));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,20),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,20));\
     PXOR1_2(CH,PSRLI_64(C2,44));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,20));\
     PXOR1_2(CHM,PSRLI_64(C2,44));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,21),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,21));\
     PXOR1_2(CH,PSRLI_64(C2,43));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,21));\
     PXOR1_2(CHM,PSRLI_64(C2,43));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,22),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,22));\
     PXOR1_2(CH,PSRLI_64(C2,42));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,22));\
     PXOR1_2(CHM,PSRLI_64(C2,42));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,23),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,23));\
     PXOR1_2(CH,PSRLI_64(C2,41));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,23));\
     PXOR1_2(CHM,PSRLI_64(C2,41));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,24),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,24));\
     PXOR1_2(CH,PSRLI_64(C2,40));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,24));\
     PXOR1_2(CHM,PSRLI_64(C2,40));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,25),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,25));\
     PXOR1_2(CH,PSRLI_64(C2,39));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,25));\
     PXOR1_2(CHM,PSRLI_64(C2,39));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,26),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,26));\
     PXOR1_2(CH,PSRLI_64(C2,38));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,26));\
     PXOR1_2(CHM,PSRLI_64(C2,38));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,27),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,27));\
     PXOR1_2(CH,PSRLI_64(C2,37));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,27));\
     PXOR1_2(CHM,PSRLI_64(C2,37));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,28),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,28));\
     PXOR1_2(CH,PSRLI_64(C2,36));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,28));\
     PXOR1_2(CHM,PSRLI_64(C2,36));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,29),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,29));\
     PXOR1_2(CH,PSRLI_64(C2,35));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,29));\
     PXOR1_2(CHM,PSRLI_64(C2,35));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,30),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,30));\
     PXOR1_2(CH,PSRLI_64(C2,34));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,30));\
     PXOR1_2(CHM,PSRLI_64(C2,34));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,31),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,31));\
     PXOR1_2(CH,PSRLI_64(C2,33));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,31));\
     PXOR1_2(CHM,PSRLI_64(C2,33));\
 \
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,32),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,32),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,32));\
     PXOR1_2(CH,PSRLI_64(C2,32));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,32));\
     PXOR1_2(CHM,PSRLI_64(C2,32));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,33),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,33),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,33));\
     PXOR1_2(CH,PSRLI_64(C2,31));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,33));\
     PXOR1_2(CHM,PSRLI_64(C2,31));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,34),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,34),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,34));\
     PXOR1_2(CH,PSRLI_64(C2,30));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,34));\
     PXOR1_2(CHM,PSRLI_64(C2,30));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,35),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,35),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,35));\
     PXOR1_2(CH,PSRLI_64(C2,29));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,35));\
     PXOR1_2(CHM,PSRLI_64(C2,29));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,36),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,36),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,36));\
     PXOR1_2(CH,PSRLI_64(C2,28));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,36));\
     PXOR1_2(CHM,PSRLI_64(C2,28));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,37),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,37),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,37));\
     PXOR1_2(CH,PSRLI_64(C2,27));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,37));\
     PXOR1_2(CHM,PSRLI_64(C2,27));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,38),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,38),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,38));\
     PXOR1_2(CH,PSRLI_64(C2,26));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,38));\
     PXOR1_2(CHM,PSRLI_64(C2,26));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,39),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,39),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,39));\
     PXOR1_2(CH,PSRLI_64(C2,25));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,39));\
     PXOR1_2(CHM,PSRLI_64(C2,25));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,40),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,40),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,40));\
     PXOR1_2(CH,PSRLI_64(C2,24));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,40));\
     PXOR1_2(CHM,PSRLI_64(C2,24));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,41),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,41),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,41));\
     PXOR1_2(CH,PSRLI_64(C2,23));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,41));\
     PXOR1_2(CHM,PSRLI_64(C2,23));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,42),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,42),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,42));\
     PXOR1_2(CH,PSRLI_64(C2,22));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,42));\
     PXOR1_2(CHM,PSRLI_64(C2,22));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,43),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,43),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,43));\
     PXOR1_2(CH,PSRLI_64(C2,21));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,43));\
     PXOR1_2(CHM,PSRLI_64(C2,21));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,44),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,44),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,44));\
     PXOR1_2(CH,PSRLI_64(C2,20));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,44));\
     PXOR1_2(CHM,PSRLI_64(C2,20));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,45),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,45),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,45));\
     PXOR1_2(CH,PSRLI_64(C2,19));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,45));\
     PXOR1_2(CHM,PSRLI_64(C2,19));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,46),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,46),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,46));\
     PXOR1_2(CH,PSRLI_64(C2,18));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,46));\
     PXOR1_2(CHM,PSRLI_64(C2,18));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,47),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,47),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,47));\
     PXOR1_2(CH,PSRLI_64(C2,17));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,47));\
     PXOR1_2(CHM,PSRLI_64(C2,17));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,48),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,48),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,48));\
     PXOR1_2(CH,PSRLI_64(C2,16));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,48));\
     PXOR1_2(CHM,PSRLI_64(C2,16));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,49),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,49),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,49));\
     PXOR1_2(CH,PSRLI_64(C2,15));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,49));\
     PXOR1_2(CHM,PSRLI_64(C2,15));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,50),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,50),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,50));\
     PXOR1_2(CH,PSRLI_64(C2,14));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,50));\
     PXOR1_2(CHM,PSRLI_64(C2,14));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,51),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,51),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,51));\
     PXOR1_2(CH,PSRLI_64(C2,13));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,51));\
     PXOR1_2(CHM,PSRLI_64(C2,13));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,52),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,52),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,52));\
     PXOR1_2(CH,PSRLI_64(C2,12));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,52));\
     PXOR1_2(CHM,PSRLI_64(C2,12));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,53),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,53),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,53));\
     PXOR1_2(CH,PSRLI_64(C2,11));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,53));\
     PXOR1_2(CHM,PSRLI_64(C2,11));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,54),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,54),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,54));\
     PXOR1_2(CH,PSRLI_64(C2,10));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,54));\
     PXOR1_2(CHM,PSRLI_64(C2,10));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,55),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,55),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,55));\
     PXOR1_2(CH,PSRLI_64(C2,9));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,55));\
     PXOR1_2(CHM,PSRLI_64(C2,9));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,56),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,56),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,56));\
     PXOR1_2(CH,PSRLI_64(C2,8));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,56));\
     PXOR1_2(CHM,PSRLI_64(C2,8));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,57),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,57),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,57));\
     PXOR1_2(CH,PSRLI_64(C2,7));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,57));\
     PXOR1_2(CHM,PSRLI_64(C2,7));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,58),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,58),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,58));\
     PXOR1_2(CH,PSRLI_64(C2,6));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,58));\
     PXOR1_2(CHM,PSRLI_64(C2,6));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,59),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,59),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,59));\
     PXOR1_2(CH,PSRLI_64(C2,5));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,59));\
     PXOR1_2(CHM,PSRLI_64(C2,5));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,60),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,60),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,60));\
     PXOR1_2(CH,PSRLI_64(C2,4));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,60));\
     PXOR1_2(CHM,PSRLI_64(C2,4));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,61),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,61),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,61));\
     PXOR1_2(CH,PSRLI_64(C2,3));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,61));\
     PXOR1_2(CHM,PSRLI_64(C2,3));\
-    C1=PMASK64_ONE(PAND_(PSRLI_64(RB,62),one64),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PAND_(PSRLI_64(RB,62),one64),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,62));\
     PXOR1_2(CH,PSRLI_64(C2,2));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,62));\
     PXOR1_2(CHM,PSRLI_64(C2,2));\
     /* Optimization: the '&1' is removed */\
-    C1=PMASK64_ONE(PSRLI_64(RB,63),one64);\
-    C2=PAND_(RA,C1);\
+    (C1)=PMASK64_ONE(PSRLI_64(RB,63),one64);\
+    (C2)=PAND_(RA,C1);\
     PXOR1_2(CL,PSLLI_64(C2,63));\
     PXOR1_2(CH,PSRLI_64(C2,1));\
-    C2=PAND_(RAM,C1);\
+    (C2)=PAND_(RAM,C1);\
     PXOR1_2(CLM,PSLLI_64(C2,63));\
     PXOR1_2(CHM,PSRLI_64(C2,1));\
 \
-    C1=PUNPACKLO_64(CL,CH);\
-    C2=PUNPACKHI_64(CL,CH);\
+    (C1)=PUNPACKLO_64(CL,CH);\
+    (C2)=PUNPACKHI_64(CL,CH);\
 \
-    RAM=PXOR_(PUNPACKLO_64(CLM,CHM),PUNPACKHI_64(CLM,CHM));\
+    (RAM)=PXOR_(PUNPACKLO_64(CLM,CHM),PUNPACKHI_64(CLM,CHM));\
     PXOR1_2(C1,PLSHIFT64(RAM));\
     PXOR1_2(C2,PRSHIFT64(RAM));
 
@@ -2197,9 +2197,9 @@
     /* A2*B2 */\
     PMUL32_WS_CLAS_GF2X(z3,(A)[2],(B)[2],RA,RB,CL,CH,M,one32);\
 \
-    res1=PXOR_(z1,z2);\
-    res2=PXOR_(z3,z2);\
-    z2=PXOR_(res1,z3);\
+    (res1)=PXOR_(z1,z2);\
+    (res2)=PXOR_(z3,z2);\
+    (z2)=PXOR_(res1,z3);\
     /*  C[0] = C0
         C[1] = C1^(C0^C2)
         C[2] = C2^(C1^C3)^C0^C4
@@ -2233,9 +2233,9 @@
     /* A2*B2 */\
     PMUL64_WS_KAR_GF2X(z3,(A)[2],(B)[2],RA,RB,CL,CH,M,CM,one32);\
 \
-    res1=PXOR_(z1,z2);\
-    res2=PXOR_(z3,z2);\
-    z2=PXOR_(res1,z3);\
+    (res1)=PXOR_(z1,z2);\
+    (res2)=PXOR_(z3,z2);\
+    (z2)=PXOR_(res1,z3);\
     /*  C[0] = C0
         C[1] = C1^(C0^C2)
         C[2] = C2^(C1^C3)^C0^C4
@@ -2287,7 +2287,7 @@
     PMUL128_WS_KAR_GF2X(C3,C4,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,one32);\
 \
     PXOR1_2(C3,C2);\
-    C2=PXOR_(C3,C1);\
+    (C2)=PXOR_(C3,C1);\
     PXOR1_2(C3,C4);\
 \
     RESERVED_BUF4[0]=(A)[0]^(A)[2];\
@@ -2309,7 +2309,7 @@
     PMUL160_WS_KAR6_GF2X(C3,C4,C5,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,\
                          res1,res2,one32)\
     PXOR1_2(C3,C2);\
-    C2=PXOR_(C3,C1);\
+    (C2)=PXOR_(C3,C1);\
     PXOR1_2(C3,C4);\
     PXOR1_2(C4,C5);\
 \
@@ -2335,7 +2335,7 @@
     PMUL192_WS_KAR6_GF2X(C3,C4,C5,(A)+2,(B)+2,RA,RB,CL,CH,M,MM,CM,\
                          res1,res2,one32)\
     PXOR1_2(C3,C2);\
-    C2=PXOR_(C3,C1);\
+    (C2)=PXOR_(C3,C1);\
     PXOR1_2(C3,C4);\
     PXOR1_2(C4,C5);\
 \
@@ -2418,11 +2418,11 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
     PMUL160_WS_KAR6_GF2X(C5,C6,C7,(A)+4,(B)+4,RA,RB,CL,CH,M,M2,CM,\
                          CM1,CM2,one32)\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
 \
     RESERVED_BUF8[0]=(A)[0]^(A)[4];\
     RESERVED_BUF8[1]=(A)[1]^(A)[5];\
@@ -2481,11 +2481,11 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
     PMUL192_WS_KAR6_GF2X(C5,C6,C7,(A)+4,(B)+4,RA,RB,CL,CH,M,M2,CM,\
                          CM1,CM2,one32)\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
 \
     RESERVED_BUF8[0]=(A)[0]^(A)[4];\
     RESERVED_BUF8[1]=(A)[1]^(A)[5];\
@@ -2511,12 +2511,12 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);\
     PMUL224_WS_KAR_GF2X(C5,C6,C7,C8,(A)+4,(B)+4,\
                         RA,RB,CL,CH,M,MM,CM,M3,M4,one32);\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
-    C6=PXOR_(C6,C8);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
+    (C6)=PXOR_(C6,C8);\
 \
     RESERVED_BUF8[0]=(A)[0]^(A)[4];\
     RESERVED_BUF8[1]=(A)[1]^(A)[5];\
@@ -2542,12 +2542,12 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32);\
     PMUL256_WS_KAR_GF2X(C5,C6,C7,C8,(A)+4,(B)+4,\
                         RA,RB,CL,CH,M,MM,CM,M3,M4,one32);\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
-    C6=PXOR_(C6,C8);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
+    (C6)=PXOR_(C6,C8);\
 \
     RESERVED_BUF8[0]=(A)[0]^(A)[4];\
     RESERVED_BUF8[1]=(A)[1]^(A)[5];\
@@ -2573,13 +2573,13 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
     PMUL288_WS_KAR_GF2X(C5,C6,C7,C8,C9,(A)+4,(B)+4,RA,RB,CL,CH,M,MM,CM,\
                         M1,M2,M3,res1,res2,one32)\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
-    C6=PXOR_(C6,C8);\
-    C7=PXOR_(C7,C9);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
+    (C6)=PXOR_(C6,C8);\
+    (C7)=PXOR_(C7,C9);\
 \
     RESERVED_BUF10[0]=(A)[0]^(A)[4];\
     RESERVED_BUF10[1]=(A)[1]^(A)[5];\
@@ -2608,13 +2608,13 @@
     PMUL256_WS_KAR_GF2X(C1,C2,C3,C4,A,B,RA,RB,CL,CH,M,MM,CM,M1,M2,one32)\
     PMUL320_WS_KAR_GF2X(C5,C6,C7,C8,C9,(A)+4,(B)+4,RA,RB,CL,CH,M,MM,CM,\
                         M1,M2,M3,res1,res2,one32)\
-    C5=PXOR_(C3,C5);\
-    C6=PXOR_(C4,C6);\
-    C3=PXOR_(C5,C1);\
-    C4=PXOR_(C6,C2);\
-    C5=PXOR_(C5,C7);\
-    C6=PXOR_(C6,C8);\
-    C7=PXOR_(C7,C9);\
+    (C5)=PXOR_(C3,C5);\
+    (C6)=PXOR_(C4,C6);\
+    (C3)=PXOR_(C5,C1);\
+    (C4)=PXOR_(C6,C2);\
+    (C5)=PXOR_(C5,C7);\
+    (C6)=PXOR_(C6,C8);\
+    (C7)=PXOR_(C7,C9);\
 \
     RESERVED_BUF10[0]=(A)[0]^(A)[4];\
     RESERVED_BUF10[1]=(A)[1]^(A)[5];\
@@ -2729,62 +2729,62 @@
 /* Classical: 4 mul64, 5 other instructions */
 #define PCLMUL128_WS_CLAS_GF2X(z1,z2,x,y,sum,res_low,res_high) \
     /* X^0 */\
-    res_low=PCLMUL(x,y,0);\
+    (res_low)=PCLMUL(x,y,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x, y, 1);\
-    z2=PCLMUL(x, y, 0x10);\
-    res_high=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x, y, 1);\
+    (z2)=PCLMUL(x, y, 0x10);\
+    (res_high)=PXOR_(z1,z2);\
 \
     /* mid2_low: x^64 ... x^127 */\
-    sum=PLSHIFT64(res_high);\
+    (sum)=PLSHIFT64(res_high);\
     /* mid2_low + L */\
-    z1=PXOR_(res_low,sum);\
+    (z1)=PXOR_(res_low,sum);\
 \
     /* X^128 */\
-    res_low=PCLMUL(x,y,0x11);\
+    (res_low)=PCLMUL(x,y,0x11);\
 \
     /* mid2_high: x^128 ... x^191 */\
-    sum=PRSHIFT64(res_high);\
+    (sum)=PRSHIFT64(res_high);\
     /* mid2_high + H */\
-    z2=PXOR_(res_low,sum);
+    (z2)=PXOR_(res_low,sum);
 
 
 /* Classical: 4 mul64, 7 other instructions */
 #define PCLMUL128_ADD_CLAS_GF2X(z3,z4,z1,z2,x,y,sum,res_low,res_high) \
     /* X^0 */\
-    res_low=PCLMUL(x,y,0);\
+    (res_low)=PCLMUL(x,y,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x, y, 1);\
-    z2=PCLMUL(x, y, 0x10);\
-    res_high=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x, y, 1);\
+    (z2)=PCLMUL(x, y, 0x10);\
+    (res_high)=PXOR_(z1,z2);\
 \
     /* mid2_low: x^64 ... x^127 */\
-    sum=PLSHIFT64(res_high);\
+    (sum)=PLSHIFT64(res_high);\
     /* mid2_low + L */\
-    z3^=PXOR_(res_low,sum);\
+    (z3)^=PXOR_(res_low,sum);\
 \
     /* X^128 */\
-    res_low=PCLMUL(x,y,0x11);\
+    (res_low)=PCLMUL(x,y,0x11);\
 \
     /* mid2_high: x^128 ... x^191 */\
-    sum=PRSHIFT64(res_high);\
+    (sum)=PRSHIFT64(res_high);\
     /* mid2_high + H */\
-    z4^=PXOR_(res_low,sum);
+    (z4)^=PXOR_(res_low,sum);
 
 
 /* Karatsuba: 3 mul64, 10 other instructions */
 #define PCLMUL128_WS_KAR_GF2X(z1,z2,x,y,sum,res_low,res_high) \
     /* X^0 */\
-    z1=PCLMUL(x,y,0);\
+    (z1)=PCLMUL(x,y,0);\
     /* X^128 */\
-    z2=PCLMUL(x,y,0x11);\
+    (z2)=PCLMUL(x,y,0x11);\
 \
-    res_low=PXOR_(x,PRSHIFT64(x));\
-    res_high=PXOR_(y,PRSHIFT64(y));\
+    (res_low)=PXOR_(x,PRSHIFT64(x));\
+    (res_high)=PXOR_(y,PRSHIFT64(y));\
 \
-    sum=PCLMUL(res_low,res_high,0);\
+    (sum)=PCLMUL(res_low,res_high,0);\
     PXOR1_2(sum,z1);\
     PXOR1_2(sum,z2);\
 \
@@ -2795,14 +2795,14 @@
 /* Karatsuba: 3 mul64, 12 other instructions */
 #define PCLMUL128_ADD_KAR_GF2X(z3,z4,z1,z2,x,y,sum,res_low,res_high) \
     /* X^0 */\
-    z1=PCLMUL(x,y,0);\
+    (z1)=PCLMUL(x,y,0);\
     /* X^128 */\
-    z2=PCLMUL(x,y,0x11);\
+    (z2)=PCLMUL(x,y,0x11);\
 \
-    res_low=PXOR_(x,PRSHIFT64(x));\
-    res_high=PXOR_(y,PRSHIFT64(y));\
+    (res_low)=PXOR_(x,PRSHIFT64(x));\
+    (res_high)=PXOR_(y,PRSHIFT64(y));\
 \
-    sum=PCLMUL(res_low,res_high,0);\
+    (sum)=PCLMUL(res_low,res_high,0);\
     PXOR1_2(sum,z1);\
     PXOR1_2(sum,z2);\
 \
@@ -2815,50 +2815,50 @@
 /* Classical: 9 mul64, 1 PMIDDLE, 9 other instructions */
 #define PCLMUL192_WS_CLAS_GF2X(z3,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PCLMUL(x1, y2, 1);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PCLMUL(x1, y2, 1);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    res1=PCLMUL(x2,y2,0);\
-    res2=PRSHIFT64(sum);\
-    z2=PXOR_(res1,res2);
+    (res1)=PCLMUL(x2,y2,0);\
+    (res2)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,res2);
 
 
 /* Karatsuba: 6 mul64, 1 PMIDDLE, 19 other instructions */
 #define PCLMUL192_WS_KAR_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2) \
     {__m128i u31;\
     /* A0*B0 */\
-    z1=PCLMUL(x1,y1,0);\
+    (z1)=PCLMUL(x1,y1,0);\
     /* A1*B1 */\
-    z2=PCLMUL(x1,y1,0x11);\
+    (z2)=PCLMUL(x1,y1,0x11);\
     /* A2*B2 */\
-    z3=PCLMUL(x2,y2,0);\
+    (z3)=PCLMUL(x2,y2,0);\
 \
-    res1=PXOR_(z1,z2);\
-    res2=PXOR_(z3,z2);\
-    z2=PXOR_(res1,z3);\
+    (res1)=PXOR_(z1,z2);\
+    (res2)=PXOR_(z3,z2);\
+    (z2)=PXOR_(res1,z3);\
     /*  C[0] = C0
         C[1] = C1^(C0^C2)
         C[2] = C2^(C1^C3)^C0^C4
@@ -2866,9 +2866,9 @@
         C[4] = C4^(C5^C3)
         C[5] = C5 */\
     /* (A2 A2) */\
-    u31=PSHUFFLE_32_1010(x2);\
+    (u31)=PSHUFFLE_32_1010(x2);\
     /* (B2 B2) */\
-    sum=PSHUFFLE_32_1010(y2);\
+    (sum)=PSHUFFLE_32_1010(y2);\
     /* (A2 A2) ^ (A0 A1) */\
     PXOR1_2(u31,x1);\
     /* (B2 B2) ^ (B0 B1) */\
@@ -2890,13 +2890,13 @@
 #define PCLMUL192_WS_KAR256_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2) \
     {__m128i x,y,u31,u32;\
     PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
-    z3=PCLMUL(x2,y2,0);\
+    (z3)=PCLMUL(x2,y2,0);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(z3,z2);\
-    z2=PXOR_(z3,z1);\
+    (z2)=PXOR_(z3,z1);\
 \
     PCLMUL128_ADD_GF2X(z2,z3,u31,u32,x,y,sum,res1,res2);}
 
@@ -2904,108 +2904,108 @@
 /* Classical: 16 mul64, 2 PMIDDLE, 15 other instructions */
 #define PCLMUL256_WS_CLAS_GF2X(z3,z4,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(y1, x2, 0x11);\
-    z2=PCLMUL(y2, x2, 0);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0x11);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(y1, x2, 0x11);\
+    (z2)=PCLMUL(y2, x2, 0);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0x11);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^320 */\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    res1=PCLMUL(x2,y2,0x11);\
-    sum=PRSHIFT64(res2);\
-    z2=PXOR_(res1,sum);
+    (res1)=PCLMUL(x2,y2,0x11);\
+    (sum)=PRSHIFT64(res2);\
+    (z2)=PXOR_(res1,sum);
 
 
 /* Classical: 16 mul64, 2 PMIDDLE, 19 other instructions */
 /* xor the res to z3,z4,z5,z6 */
 #define PCLMUL256_ADD_CLAS_GF2X(z3,z4,z5,z6,z1,z2,x1,x2,y1,y2,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3^=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)^=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4^=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)^=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(y1, x2, 0x11);\
-    z2=PCLMUL(y2, x2, 0);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0x11);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(y1, x2, 0x11);\
+    (z2)=PCLMUL(y2, x2, 0);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0x11);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^320 */\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z5^=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z5)^=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    res1=PCLMUL(x2,y2,0x11);\
-    sum=PRSHIFT64(res2);\
-    z6^=PXOR_(res1,sum);
+    (res1)=PCLMUL(x2,y2,0x11);\
+    (sum)=PRSHIFT64(res2);\
+    (z6)^=PXOR_(res1,sum);
 
 
 /* Karatsuba: 3 mul128, 5 other instructions */
@@ -3014,11 +3014,11 @@
     PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
     PCLMUL128_WS_GF2X(z3,z4,x2,y2,sum,res1,res2);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(z3,z2);\
-    z2=PXOR_(z3,z1);\
+    (z2)=PXOR_(z3,z1);\
     PXOR1_2(z3,z4);\
 \
     PCLMUL128_ADD_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}
@@ -3030,8 +3030,8 @@
     PCLMUL128_WS_GF2X(u41,u42,x1,y1,sum,res1,res2);\
     PCLMUL128_WS_GF2X(z5,z6,x2,y2,sum,res1,res2);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(z1,u41);\
     PXOR1_2(z4,z6);\
@@ -3049,11 +3049,11 @@
     PCLMUL128_WS_KAR_GF2X(z1,z2,x1,y1,sum,res1,res2);\
     PCLMUL128_WS_KAR_GF2X(z3,z4,x2,y2,sum,res1,res2);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(z3,z2);\
-    z2=PXOR_(z3,z1);\
+    (z2)=PXOR_(z3,z1);\
     PXOR1_2(z3,z4);\
 \
     PCLMUL128_ADD_KAR_GF2X(z2,z3,u41,u42,x,y,sum,res1,res2);}
@@ -3065,8 +3065,8 @@
     PCLMUL128_WS_KAR_GF2X(u41,u42,x1,y1,sum,res1,res2);\
     PCLMUL128_WS_KAR_GF2X(z5,z6,x2,y2,sum,res1,res2);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(z1,u41);\
     PXOR1_2(z4,z6);\
@@ -3081,77 +3081,77 @@
 /* Classical: 25 mul64, 3 PMIDDLE, 23 other instructions */
 #define PCLMUL320_WS_CLAS_GF2X(z3,z4,z5,z1,z2,x1,x2,x3,y1,y2,y3,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y3, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z5=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z5)=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    z1=PCLMUL(x2, y3, 0);\
-    z2=PCLMUL(x2, y2, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y2, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x2, y3, 0);\
+    (z2)=PCLMUL(x2, y2, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y2, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x2, y3, 1);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y3, 1);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
 \
     /* X^512 */\
-    res1=PCLMUL(x3,y3,0);\
-    res2=PRSHIFT64(sum);\
-    z2=PXOR_(res1,res2);
+    (res1)=PCLMUL(x3,y3,0);\
+    (res2)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,res2);
 
 
 /* Classical: 25 mul64, 3 PMIDDLE, 28 other instructions */
@@ -3159,77 +3159,77 @@
 #define PCLMUL320_ADD_CLAS_GF2X(z3,z4,z5,z6,z7,z1,z2,x1,x2,x3,y1,y2,y3,\
                                 sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3^=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)^=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4^=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)^=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y3, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z5^=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z5)^=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    z1=PCLMUL(x2, y3, 0);\
-    z2=PCLMUL(x2, y2, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y2, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x2, y3, 0);\
+    (z2)=PCLMUL(x2, y2, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y2, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x2, y3, 1);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y3, 1);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z6^=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z6)^=PXOR_(res1,z2);\
 \
     /* X^512 */\
-    res1=PCLMUL(x3,y3,0);\
-    res2=PRSHIFT64(sum);\
-    z7^=PXOR_(res1,res2);
+    (res1)=PCLMUL(x3,y3,0);\
+    (res2)=PRSHIFT64(sum);\
+    (z7)^=PXOR_(res1,res2);
 
 
 /* Karatsuba: 2 mul192, 1 mul128, 9 other instructions */
@@ -3238,11 +3238,11 @@
     PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
     PCLMUL192_WS_GF2X(z3,z4,z5,x2,x3,y2,y3,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x2);\
-    y1m=PXOR_(y1,y2);\
+    (x1m)=PXOR_(x1,x2);\
+    (y1m)=PXOR_(y1,y2);\
 \
     PXOR1_2(z3,z2);\
-    z2=PXOR_(z3,z1);\
+    (z2)=PXOR_(z3,z1);\
     PXOR1_2(z3,z4);\
     PXOR1_2(z4,z5);\
 \
@@ -3261,11 +3261,11 @@
     PCLMUL128_WS_GF2X(z6,z7,x1,y1,sum,res1,res2);\
     PCLMUL192_WS_GF2X(R1,R2,R3,x2,x3,y2,y3,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x2);\
-    y1m=PXOR_(y1,y2);\
+    (x1m)=PXOR_(x1,x2);\
+    (y1m)=PXOR_(y1,y2);\
 \
     PXOR1_2(R1,z7);\
-    z7=PXOR_(R1,z6);\
+    (z7)=PXOR_(R1,z6);\
     PXOR1_2(R1,R2);\
     PXOR1_2(R2,R3);\
 \
@@ -3286,104 +3286,104 @@
 #define PCLMUL384_WS_CLAS_GF2X(z3,z4,z5,z6,z1,z2,x1,x2,x3,y1,y2,y3,\
                                sum,res1,res2)\
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 0x10);\
-    z2=PCLMUL(x1, y3, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y2, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 1);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y3, 0x10);\
+    (z2)=PCLMUL(x1, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 1);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z5=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z5)=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    z1=PCLMUL(x1, y3, 0x11);\
-    z2=PCLMUL(x2, y3, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x11);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x3, y2, 0);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x3, y1, 0x11);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x1, y3, 0x11);\
+    (z2)=PCLMUL(x2, y3, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x11);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x3, y2, 0);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x11);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x2, y3, 0x10);\
-    z2=PCLMUL(x2, y3, 1);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x3, y2, 1);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y3, 0x10);\
+    (z2)=PCLMUL(x2, y3, 1);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x3, y2, 1);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z6=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z6)=PXOR_(res1,z2);\
 \
     /* X^512 */\
-    z1=PCLMUL(x2, y3, 0x11);\
-    z2=PCLMUL(x3, y3, 0);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y2, 0x11);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y3, 0x11);\
+    (z2)=PCLMUL(x3, y3, 0);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y2, 0x11);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^576 */\
-    z1=PCLMUL(x3, y3, 0x10);\
-    z2=PCLMUL(x3, y3, 1);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y3, 0x10);\
+    (z2)=PCLMUL(x3, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
 \
     /* X^640 */\
-    res1=PCLMUL(x3,y3,0x11);\
-    sum=PRSHIFT64(res2);\
-    z2=PXOR_(res1,sum);
+    (res1)=PCLMUL(x3,y3,0x11);\
+    (sum)=PRSHIFT64(res2);\
+    (z2)=PXOR_(res1,sum);
 
 
 /* Karatsuba: 3 mul192, 4 PMIDDLE, 18 other instructions */
@@ -3392,10 +3392,10 @@
     {__m128i x1m,x2m,y1m,y2m,R1,R2,R3;\
     PCLMUL192_WS_GF2X(z1,z2,z3,x1,x2,y1,y2,sum,res1,res2);\
 \
-    x1m=PMIDDLE(x2,x3);\
-    x2m=PRSHIFT64(x3);\
-    y1m=PMIDDLE(y2,y3);\
-    y2m=PRSHIFT64(y3);\
+    (x1m)=PMIDDLE(x2,x3);\
+    (x2m)=PRSHIFT64(x3);\
+    (y1m)=PMIDDLE(y2,y3);\
+    (y2m)=PRSHIFT64(y3);\
 \
     PCLMUL192_WS_GF2X(z4,z5,z6,x1m,x2m,y1m,y2m,sum,res1,res2);\
 \
@@ -3419,135 +3419,135 @@
 #define PCLMUL448_WS_CLAS_GF2X(z3,z4,z5,z6,z7,z1,z2,x1,x2,x3,x4,y1,y2,y3,y4,\
                                sum,res1,res2)\
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z3=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z3)=PXOR_(res1,sum);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z4=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z4)=PXOR_(res1,z2);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 0x10);\
-    z2=PCLMUL(x1, y3, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y2, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 1);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y3, 0x10);\
+    (z2)=PCLMUL(x1, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 1);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z5=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z5)=PXOR_(res1,z2);\
 \
     /* X^384 */\
-    z1=PCLMUL(x1, y4, 0);\
-    z2=PCLMUL(x1, y3, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y3, 0);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x2, y2, 0x11);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x3, y2, 0);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x3, y1, 0x11);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x4, y1, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x1, y4, 0);\
+    (z2)=PCLMUL(x1, y3, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y3, 0);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x2, y2, 0x11);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x3, y2, 0);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x3, y1, 0x11);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x4, y1, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x1, y4, 1);\
-    z2=PCLMUL(x2, y3, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x2, y3, 1);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x3, y2, 1);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x4, y1, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y4, 1);\
+    (z2)=PCLMUL(x2, y3, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x2, y3, 1);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x3, y2, 1);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x4, y1, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z6=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z6)=PXOR_(res1,z2);\
 \
     /* X^512 */\
-    z1=PCLMUL(x2, y4, 0);\
-    z2=PCLMUL(x2, y3, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y3, 0);\
-    res1=PXOR_(res2,z1);\
-    z2=PCLMUL(x3, y2, 0x11);\
-    res2=PXOR_(res1,z2);\
-    z1=PCLMUL(x4, y2, 0);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y4, 0);\
+    (z2)=PCLMUL(x2, y3, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y3, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z2)=PCLMUL(x3, y2, 0x11);\
+    (res2)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x4, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^576 */\
-    z1=PCLMUL(x2, y4, 1);\
-    z2=PCLMUL(x3, y3, 0x10);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y3, 1);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x4, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y4, 1);\
+    (z2)=PCLMUL(x3, y3, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y3, 1);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x4, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(sum,res2);\
-    z7=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(sum,res2);\
+    (z7)=PXOR_(res1,z2);\
 \
     /* X^640 */\
-    z1=PCLMUL(x3, y4, 0);\
-    z2=PCLMUL(x3, y3, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x4, y3, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x3, y4, 0);\
+    (z2)=PCLMUL(x3, y3, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x4, y3, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^704 */\
-    z1=PCLMUL(x3, y4, 1);\
-    z2=PCLMUL(x4, y3, 0x10);\
-    sum=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y4, 1);\
+    (z2)=PCLMUL(x4, y3, 0x10);\
+    (sum)=PXOR_(z1,z2);\
 \
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
 \
     /* X^768 */\
-    res1=PCLMUL(x4,y4,0);\
-    res2=PRSHIFT64(sum);\
-    z2=PXOR_(res1,res2);
+    (res1)=PCLMUL(x4,y4,0);\
+    (res2)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,res2);
 
 
 /* Karatsuba: 2 mul256, 1 mul192, 9 other instructions */
@@ -3557,16 +3557,16 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL192_WS_GF2X(z5,z6,z7,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
 \
     PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}
 
@@ -3578,17 +3578,17 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL256_WS_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
 \
     PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}
 
@@ -3600,17 +3600,17 @@
     PCLMUL256_WS_KAR2_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL256_WS_KAR2_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
 \
     PCLMUL256_ADD_KAR2_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);}
 
@@ -3622,18 +3622,18 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL320_WS_GF2X(z5,z6,z7,z8,z9,x3,x4,x5,y3,y4,y5,sum,res1,res2);\
 \
-    x11m=PXOR_(x1,x3);\
-    x22m=PXOR_(x2,x4);\
-    y11m=PXOR_(y1,y3);\
-    y22m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
-    z7=PXOR_(z7,z9);\
+    (x11m)=PXOR_(x1,x3);\
+    (x22m)=PXOR_(x2,x4);\
+    (y11m)=PXOR_(y1,y3);\
+    (y22m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
+    (z7)=PXOR_(z7,z9);\
 \
     PCLMUL320_ADD_GF2X(z3,z4,z5,z6,z7,t1,t2,x11m,x22m,x5,y11m,y22m,y5,\
                        sum,res1,res2);}
@@ -3683,54 +3683,54 @@
 
 /* 1 mul64 */
 #define PCLMUL64_GF2X(C,x,y,z,pos) \
-    z=PCLMUL(x, y, pos);\
+    (z)=PCLMUL(x, y, pos);\
     PSTORE128(C,z);
 
 
 /* Classical: 4 mul64, 5 other instructions */
 #define PCLMUL128_CLAS_FINAL(FINAL_STORE,C,x,y,z1,z2,sum,res_low,res_high) \
     /* X^0 */\
-    res_low=PCLMUL(x,y,0);\
+    (res_low)=PCLMUL(x,y,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x, y, 1);\
-    z2=PCLMUL(x, y, 0x10);\
-    res_high=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x, y, 1);\
+    (z2)=PCLMUL(x, y, 0x10);\
+    (res_high)=PXOR_(z1,z2);\
 \
     /* mid2_low: x^64 ... x^127 */\
-    sum=PLSHIFT64(res_high);\
+    (sum)=PLSHIFT64(res_high);\
     /* mid2_low + L */\
-    z1=PXOR_(res_low,sum);\
+    (z1)=PXOR_(res_low,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    res_low=PCLMUL(x,y,0x11);\
+    (res_low)=PCLMUL(x,y,0x11);\
 \
     /* mid2_high: x^128 ... x^191 */\
-    sum=PRSHIFT64(res_high);\
+    (sum)=PRSHIFT64(res_high);\
     /* mid2_high + H */\
-    z2=PXOR_(res_low,sum);\
+    (z2)=PXOR_(res_low,sum);\
     FINAL_STORE;
 
 
 #define PCLMUL96_CLAS_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
-        PCLMUL128_CLAS_FINAL(PSTOREL(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
+        PCLMUL128_CLAS_FINAL(PSTOREL((C)+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
 #define PCLMUL128_CLAS_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
-        PCLMUL128_CLAS_FINAL(PSTORE128(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
+        PCLMUL128_CLAS_FINAL(PSTORE128((C)+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
 
 
 /* Karatsuba: 3 mul64, 10 other instructions */
 #define PCLMUL128_KAR_FINAL(FINAL_STORE,C,x,y,z1,z2,sum,res_low,res_high) \
     /* X^0 */\
-    z1=PCLMUL(x,y,0);\
+    (z1)=PCLMUL(x,y,0);\
     /* X^128 */\
-    z2=PCLMUL(x,y,0x11);\
+    (z2)=PCLMUL(x,y,0x11);\
 \
-    res_low=PXOR_(x,PRSHIFT64(x));\
-    res_high=PXOR_(y,PRSHIFT64(y));\
+    (res_low)=PXOR_(x,PRSHIFT64(x));\
+    (res_high)=PXOR_(y,PRSHIFT64(y));\
 \
     /* X^64 */\
-    sum=PCLMUL(res_low,res_high,0);\
+    (sum)=PCLMUL(res_low,res_high,0);\
     PXOR1_2(sum,z1);\
     PXOR1_2(sum,z2);\
 \
@@ -3742,52 +3742,52 @@
 
 
 #define PCLMUL96_KAR_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
-        PCLMUL128_KAR_FINAL(PSTOREL(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
+        PCLMUL128_KAR_FINAL(PSTOREL((C)+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
 #define PCLMUL128_KAR_GF2X(C,x,y,z1,z2,sum,res_low,res_high) \
-        PCLMUL128_KAR_FINAL(PSTORE128(C+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
+        PCLMUL128_KAR_FINAL(PSTORE128((C)+2,z2),C,x,y,z1,z2,sum,res_low,res_high)
 
 
 /* Classical: 9 mul64, 1 PMIDDLE, 9 other instructions */
 #define PCLMUL192_CLAS_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z1=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z1)=PXOR_(res1,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PCLMUL(x1, y2, 1);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+2,z1);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PCLMUL(x1, y2, 1);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+2,z1);\
 \
     /* X^256 */\
-    res1=PCLMUL(x2,y2,0);\
-    z1=PRSHIFT64(sum);\
-    z2=PXOR_(res1,z1);\
+    (res1)=PCLMUL(x2,y2,0);\
+    (z1)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,z1);\
     FINAL_STORE;
 
 
 #define PCLMUL160_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL192_CLAS_FINAL(PSTOREL(C+4,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
+        PCLMUL192_CLAS_FINAL(PSTOREL((C)+4,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
 #define PCLMUL192_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL192_CLAS_FINAL(PSTORE128(C+4,z2),C,x1,x2,y1,y2,\
+        PCLMUL192_CLAS_FINAL(PSTORE128((C)+4,z2),C,x1,x2,y1,y2,\
                              z1,z2,sum,res1,res2)
 
 
@@ -3795,15 +3795,15 @@
 #define PCLMUL192_KAR_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
     {__m128i u31,u333;\
     /* A0*B0 */\
-    z1=PCLMUL(x1,y1,0);\
+    (z1)=PCLMUL(x1,y1,0);\
     /* A1*B1 */\
-    z2=PCLMUL(x1,y1,0x11);\
+    (z2)=PCLMUL(x1,y1,0x11);\
     /* A2*B2 */\
-    u333=PCLMUL(x2,y2,0);\
+    (u333)=PCLMUL(x2,y2,0);\
 \
-    res1=PXOR_(z1,z2);\
-    res2=PXOR_(u333,z2);\
-    z2=PXOR_(res1,u333);\
+    (res1)=PXOR_(z1,z2);\
+    (res2)=PXOR_(u333,z2);\
+    (z2)=PXOR_(res1,u333);\
     /*  C[0] = C0
         C[1] = C1^(C0^C2)
         C[2] = C2^(C1^C3)^C0^C4
@@ -3811,9 +3811,9 @@
         C[4] = C4^(C5^C3)
         C[5] = C5 */\
     /* (A2 A2) */\
-    u31=PSHUFFLE_32_1010(x2);\
+    (u31)=PSHUFFLE_32_1010(x2);\
     /* (B2 B2) */\
-    sum=PSHUFFLE_32_1010(y2);\
+    (sum)=PSHUFFLE_32_1010(y2);\
     /* (A2 A2) ^ (A0 A1) */\
     PXOR1_2(u31,x1);\
     /* (B2 B2) ^ (B0 B1) */\
@@ -3832,77 +3832,77 @@
 \
     PSTORE128(C,z1);\
     FINAL_STORE;\
-    PSTORE128(C+2,z2);}
+    PSTORE128((C)+2,z2);}
 
 
 #define PCLMUL160_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL192_KAR_FINAL(PSTOREL(C+4,u333),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
+        PCLMUL192_KAR_FINAL(PSTOREL((C)+4,u333),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
 #define PCLMUL192_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL192_KAR_FINAL(PSTORE128(C+4,u333),C,x1,x2,y1,y2,\
+        PCLMUL192_KAR_FINAL(PSTORE128((C)+4,u333),C,x1,x2,y1,y2,\
                             z1,z2,sum,res1,res2)
 
 
 /* Classical: 16 mul64, 2 PMIDDLE, 15 other instructions */
 #define PCLMUL256_CLAS_FINAL(FINAL_STORE,C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z1=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z1)=PXOR_(res1,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+2,z1);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+2,z1);\
 \
     /* X^256 */\
-    z1=PCLMUL(y1, x2, 0x11);\
-    z2=PCLMUL(y2, x2, 0);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0x11);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(y1, x2, 0x11);\
+    (z2)=PCLMUL(y2, x2, 0);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0x11);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^320 */\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+4,z1);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+4,z1);\
 \
     /* X^384 */\
-    res1=PCLMUL(x2,y2,0x11);\
-    z1=PRSHIFT64(res2);\
-    z2=PXOR_(res1,z1);\
+    (res1)=PCLMUL(x2,y2,0x11);\
+    (z1)=PRSHIFT64(res2);\
+    (z2)=PXOR_(res1,z1);\
     FINAL_STORE;
 
 
 #define PCLMUL224_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL256_CLAS_FINAL(PSTOREL(C+6,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
+        PCLMUL256_CLAS_FINAL(PSTOREL((C)+6,z2),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
 #define PCLMUL256_CLAS_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL256_CLAS_FINAL(PSTORE128(C+6,z2),C,x1,x2,y1,y2,\
+        PCLMUL256_CLAS_FINAL(PSTORE128((C)+6,z2),C,x1,x2,y1,y2,\
                              z1,z2,sum,res1,res2)
 
 
@@ -3912,25 +3912,25 @@
     PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
     PCLMUL128_WS_GF2X(u43,u44,x2,y2,sum,res1,res2);\
 \
-    x=PXOR_(x1,x2);\
-    y=PXOR_(y1,y2);\
+    (x)=PXOR_(x1,x2);\
+    (y)=PXOR_(y1,y2);\
 \
     PXOR1_2(u43,z2);\
-    z2=PXOR_(u43,z1);\
+    (z2)=PXOR_(u43,z1);\
     PXOR1_2(u43,u44);\
 \
     PCLMUL128_ADD_GF2X(z2,u43,u41,u42,x,y,sum,res1,res2);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,u43);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,u43);\
     FINAL_STORE;}
 
 
 #define PCLMUL224_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL256_KAR_FINAL(PSTOREL(C+6,u44),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
+        PCLMUL256_KAR_FINAL(PSTOREL((C)+6,u44),C,x1,x2,y1,y2,z1,z2,sum,res1,res2)
 #define PCLMUL256_KAR_GF2X(C,x1,x2,y1,y2,z1,z2,sum,res1,res2) \
-        PCLMUL256_KAR_FINAL(PSTORE128(C+6,u44),C,x1,x2,y1,y2,z1,z2,\
+        PCLMUL256_KAR_FINAL(PSTORE128((C)+6,u44),C,x1,x2,y1,y2,z1,z2,\
                             sum,res1,res2)
 
 
@@ -3938,89 +3938,89 @@
 #define PCLMUL320_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z1=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z1)=PXOR_(res1,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+2,z1);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+2,z1);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 1);\
-    z2=PCLMUL(x2, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 1);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+4,z1);\
+    (z1)=PCLMUL(x1, y3, 1);\
+    (z2)=PCLMUL(x2, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+4,z1);\
 \
     /* X^384 */\
-    z1=PCLMUL(x2, y3, 0);\
-    z2=PCLMUL(x2, y2, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y2, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x2, y3, 0);\
+    (z2)=PCLMUL(x2, y2, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y2, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x2, y3, 1);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+6,z1);\
+    (z1)=PCLMUL(x2, y3, 1);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+6,z1);\
 \
     /* X^512 */\
-    res1=PCLMUL(x3,y3,0);\
-    z1=PRSHIFT64(sum);\
-    z2=PXOR_(res1,z1);\
+    (res1)=PCLMUL(x3,y3,0);\
+    (z1)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,z1);\
     FINAL_STORE;
 
 
 #define PCLMUL288_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL320_CLAS_FINAL(PSTOREL(C+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL320_CLAS_FINAL(PSTOREL((C)+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2)
 #define PCLMUL320_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL320_CLAS_FINAL(PSTORE128(C+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL320_CLAS_FINAL(PSTORE128((C)+8,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2)
 
 
@@ -4031,11 +4031,11 @@
     PCLMUL128_WS_GF2X(z1,z2,x1,y1,sum,res1,res2);\
     PCLMUL192_WS_GF2X(u53,u54,u55,x2,x3,y2,y3,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x2);\
-    y1m=PXOR_(y1,y2);\
+    (x1m)=PXOR_(x1,x2);\
+    (y1m)=PXOR_(y1,y2);\
 \
     PXOR1_2(u53,z2);\
-    z2=PXOR_(u53,z1);\
+    (z2)=PXOR_(u53,z1);\
     PXOR1_2(u53,u54);\
     PXOR1_2(u54,u55);\
 \
@@ -4046,17 +4046,17 @@
     PXOR1_2(u54,R3);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,u53);\
-    PSTORE128(C+6,u54);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,u53);\
+    PSTORE128((C)+6,u54);\
     FINAL_STORE;}
 
 
 #define PCLMUL288_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL320_KAR_FINAL(PSTOREL(C+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL320_KAR_FINAL(PSTOREL((C)+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
 #define PCLMUL320_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL320_KAR_FINAL(PSTORE128(C+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL320_KAR_FINAL(PSTORE128((C)+8,u55),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
 
 
@@ -4064,117 +4064,117 @@
 #define PCLMUL384_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z1=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z1)=PXOR_(res1,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+2,z1);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+2,z1);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 0x10);\
-    z2=PCLMUL(x1, y3, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y2, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 1);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+4,z1);\
+    (z1)=PCLMUL(x1, y3, 0x10);\
+    (z2)=PCLMUL(x1, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 1);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+4,z1);\
 \
     /* X^384 */\
-    z1=PCLMUL(x1, y3, 0x11);\
-    z2=PCLMUL(x2, y3, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x11);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x3, y2, 0);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x3, y1, 0x11);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x1, y3, 0x11);\
+    (z2)=PCLMUL(x2, y3, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x11);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x3, y2, 0);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x11);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x2, y3, 0x10);\
-    z2=PCLMUL(x2, y3, 1);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x3, y2, 1);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+6,z1);\
+    (z1)=PCLMUL(x2, y3, 0x10);\
+    (z2)=PCLMUL(x2, y3, 1);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x3, y2, 1);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+6,z1);\
 \
     /* X^512 */\
-    z1=PCLMUL(x2, y3, 0x11);\
-    z2=PCLMUL(x3, y3, 0);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y2, 0x11);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y3, 0x11);\
+    (z2)=PCLMUL(x3, y3, 0);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y2, 0x11);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^576 */\
-    z1=PCLMUL(x3, y3, 0x10);\
-    z2=PCLMUL(x3, y3, 1);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+8,z1);\
+    (z1)=PCLMUL(x3, y3, 0x10);\
+    (z2)=PCLMUL(x3, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+8,z1);\
 \
     /* X^640 */\
-    res1=PCLMUL(x3,y3,0x11);\
-    z1=PRSHIFT64(res2);\
-    z2=PXOR_(res1,z1);\
+    (res1)=PCLMUL(x3,y3,0x11);\
+    (z1)=PRSHIFT64(res2);\
+    (z2)=PXOR_(res1,z1);\
     FINAL_STORE;
 
 
 #define PCLMUL352_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL384_CLAS_FINAL(PSTOREL(C+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL384_CLAS_FINAL(PSTOREL((C)+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2)
 #define PCLMUL384_CLAS_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL384_CLAS_FINAL(PSTORE128(C+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL384_CLAS_FINAL(PSTORE128((C)+10,z2),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                              sum,res1,res2)
 
 
@@ -4184,10 +4184,10 @@
     {__m128i x1m,x2m,y1m,y2m,R1,R2,R3,u63,u64,u65,u66;\
     PCLMUL192_WS_GF2X(z1,z2,u63,x1,x2,y1,y2,sum,res1,res2);\
 \
-    x1m=PMIDDLE(x2,x3);\
-    x2m=PRSHIFT64(x3);\
-    y1m=PMIDDLE(y2,y3);\
-    y2m=PRSHIFT64(y3);\
+    (x1m)=PMIDDLE(x2,x3);\
+    (x2m)=PRSHIFT64(x3);\
+    (y1m)=PMIDDLE(y2,y3);\
+    (y2m)=PRSHIFT64(y3);\
 \
     PCLMUL192_WS_GF2X(u64,u65,u66,x1m,x2m,y1m,y2m,sum,res1,res2);\
 \
@@ -4207,18 +4207,18 @@
     PXOR1_2(u64,PMIDDLE(R2,R3));\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,u63);\
-    PSTORE128(C+6,u64);\
-    PSTORE128(C+8,u65);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,u63);\
+    PSTORE128((C)+6,u64);\
+    PSTORE128((C)+8,u65);\
     FINAL_STORE;}
 
 
 #define PCLMUL352_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL384_KAR_FINAL(PSTOREL(C+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL384_KAR_FINAL(PSTOREL((C)+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
 #define PCLMUL384_KAR_GF2X(C,x1,x2,x3,y1,y2,y3,z1,z2,sum,res1,res2) \
-        PCLMUL384_KAR_FINAL(PSTORE128(C+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
+        PCLMUL384_KAR_FINAL(PSTORE128((C)+10,u66),C,x1,x2,x3,y1,y2,y3,z1,z2,\
                             sum,res1,res2)
 
 
@@ -4226,150 +4226,150 @@
 #define PCLMUL448_CLAS_FINAL(FINAL_STORE,C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,\
                              sum,res1,res2) \
     /* X^0 */\
-    res1=PCLMUL(x1,y1,0);\
+    (res1)=PCLMUL(x1,y1,0);\
 \
     /* X^64 */\
-    z1=PCLMUL(x1, y1, 1);\
-    z2=PCLMUL(x1, y1, 0x10);\
-    res2=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y1, 1);\
+    (z2)=PCLMUL(x1, y1, 0x10);\
+    (res2)=PXOR_(z1,z2);\
 \
-    sum=PLSHIFT64(res2);\
-    z1=PXOR_(res1,sum);\
+    (sum)=PLSHIFT64(res2);\
+    (z1)=PXOR_(res1,sum);\
     PSTORE128(C,z1);\
 \
     /* X^128 */\
-    z1=PCLMUL(x1, y1, 0x11);\
-    z2=PCLMUL(x2, y1, 0);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x1, y2, 0);\
-    res1=PXOR_(sum,z1);\
+    (z1)=PCLMUL(x1, y1, 0x11);\
+    (z2)=PCLMUL(x2, y1, 0);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x1, y2, 0);\
+    (res1)=PXOR_(sum,z1);\
 \
     /* X^192 */\
-    z1=PCLMUL(x1, y2, 1);\
-    z2=PCLMUL(x1, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(y1, x2, 1);\
-    z2=PXOR_(sum,z1);\
-    z1=PCLMUL(y1, x2, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+2,z1);\
+    (z1)=PCLMUL(x1, y2, 1);\
+    (z2)=PCLMUL(x1, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(y1, x2, 1);\
+    (z2)=PXOR_(sum,z1);\
+    (z1)=PCLMUL(y1, x2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+2,z1);\
 \
     /* X^256 */\
-    z1=PCLMUL(x1, y3, 0);\
-    z2=PCLMUL(x1, y2, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0);\
-    res1=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y1, 0x11);\
-    res2=PXOR_(z1,res1);\
-    z2=PCLMUL(x3, y1, 0);\
-    res1=PXOR_(res2,z2);\
+    (z1)=PCLMUL(x1, y3, 0);\
+    (z2)=PCLMUL(x1, y2, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y1, 0x11);\
+    (res2)=PXOR_(z1,res1);\
+    (z2)=PCLMUL(x3, y1, 0);\
+    (res1)=PXOR_(res2,z2);\
 \
     /* X^320 */\
-    z1=PCLMUL(x1, y3, 0x10);\
-    z2=PCLMUL(x1, y3, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y2, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x2, y2, 1);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y1, 0x10);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x3, y1, 1);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+4,z1);\
+    (z1)=PCLMUL(x1, y3, 0x10);\
+    (z2)=PCLMUL(x1, y3, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y2, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y2, 1);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y1, 0x10);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x3, y1, 1);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+4,z1);\
 \
     /* X^384 */\
-    z1=PCLMUL(x1, y4, 0);\
-    z2=PCLMUL(x1, y3, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x2, y3, 0);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x2, y2, 0x11);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x3, y2, 0);\
-    res1=PXOR_(z1,sum);\
-    z2=PCLMUL(x3, y1, 0x11);\
-    sum=PXOR_(res1,z2);\
-    z1=PCLMUL(x4, y1, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x1, y4, 0);\
+    (z2)=PCLMUL(x1, y3, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x2, y3, 0);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x2, y2, 0x11);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x3, y2, 0);\
+    (res1)=PXOR_(z1,sum);\
+    (z2)=PCLMUL(x3, y1, 0x11);\
+    (sum)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x4, y1, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^448 */\
-    z1=PCLMUL(x1, y4, 1);\
-    z2=PCLMUL(x2, y3, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x2, y3, 1);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x3, y2, 0x10);\
-    sum=PXOR_(z1,z2);\
-    z2=PCLMUL(x3, y2, 1);\
-    z1=PXOR_(sum,z2);\
-    z2=PCLMUL(x4, y1, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+6,z1);\
+    (z1)=PCLMUL(x1, y4, 1);\
+    (z2)=PCLMUL(x2, y3, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x2, y3, 1);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x3, y2, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+    (z2)=PCLMUL(x3, y2, 1);\
+    (z1)=PXOR_(sum,z2);\
+    (z2)=PCLMUL(x4, y1, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+6,z1);\
 \
     /* X^512 */\
-    z1=PCLMUL(x2, y4, 0);\
-    z2=PCLMUL(x2, y3, 0x11);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y3, 0);\
-    res1=PXOR_(res2,z1);\
-    z2=PCLMUL(x3, y2, 0x11);\
-    res2=PXOR_(res1,z2);\
-    z1=PCLMUL(x4, y2, 0);\
-    res1=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x2, y4, 0);\
+    (z2)=PCLMUL(x2, y3, 0x11);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y3, 0);\
+    (res1)=PXOR_(res2,z1);\
+    (z2)=PCLMUL(x3, y2, 0x11);\
+    (res2)=PXOR_(res1,z2);\
+    (z1)=PCLMUL(x4, y2, 0);\
+    (res1)=PXOR_(res2,z1);\
 \
     /* X^576 */\
-    z1=PCLMUL(x2, y4, 1);\
-    z2=PCLMUL(x3, y3, 0x10);\
-    res2=PXOR_(z1,z2);\
-    z1=PCLMUL(x3, y3, 1);\
-    z2=PXOR_(res2,z1);\
-    z1=PCLMUL(x4, y2, 0x10);\
-    res2=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(sum,res2);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+8,z1);\
+    (z1)=PCLMUL(x2, y4, 1);\
+    (z2)=PCLMUL(x3, y3, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x3, y3, 1);\
+    (z2)=PXOR_(res2,z1);\
+    (z1)=PCLMUL(x4, y2, 0x10);\
+    (res2)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(sum,res2);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+8,z1);\
 \
     /* X^640 */\
-    z1=PCLMUL(x3, y4, 0);\
-    z2=PCLMUL(x3, y3, 0x11);\
-    sum=PXOR_(z1,z2);\
-    z1=PCLMUL(x4, y3, 0);\
-    res1=PXOR_(z1,sum);\
+    (z1)=PCLMUL(x3, y4, 0);\
+    (z2)=PCLMUL(x3, y3, 0x11);\
+    (sum)=PXOR_(z1,z2);\
+    (z1)=PCLMUL(x4, y3, 0);\
+    (res1)=PXOR_(z1,sum);\
 \
     /* X^704 */\
-    z1=PCLMUL(x3, y4, 1);\
-    z2=PCLMUL(x4, y3, 0x10);\
-    sum=PXOR_(z1,z2);\
-\
-    z2=PMIDDLE(res2,sum);\
-    z1=PXOR_(res1,z2);\
-    PSTORE128(C+10,z1);\
+    (z1)=PCLMUL(x3, y4, 1);\
+    (z2)=PCLMUL(x4, y3, 0x10);\
+    (sum)=PXOR_(z1,z2);\
+\
+    (z2)=PMIDDLE(res2,sum);\
+    (z1)=PXOR_(res1,z2);\
+    PSTORE128((C)+10,z1);\
 \
     /* X^768 */\
-    res1=PCLMUL(x4,y4,0);\
-    res2=PRSHIFT64(sum);\
-    z2=PXOR_(res1,res2);\
+    (res1)=PCLMUL(x4,y4,0);\
+    (res2)=PRSHIFT64(sum);\
+    (z2)=PXOR_(res1,res2);\
     FINAL_STORE;
 
 
 #define PCLMUL416_CLAS_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL448_CLAS_FINAL(PSTOREL(C+12,z2),C,x1,x2,x3,x4,\
+        PCLMUL448_CLAS_FINAL(PSTOREL((C)+12,z2),C,x1,x2,x3,x4,\
                              y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 #define PCLMUL448_CLAS_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL448_CLAS_FINAL(PSTORE128(C+12,z2),C,x1,x2,x3,x4,\
+        PCLMUL448_CLAS_FINAL(PSTORE128((C)+12,z2),C,x1,x2,x3,x4,\
                              y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 
@@ -4380,34 +4380,34 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL192_WS_GF2X(z5,z6,z7,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
 \
     PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,z3);\
-    PSTORE128(C+6,z4);\
-    PSTORE128(C+8,z5);\
-    PSTORE128(C+10,z6);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,z3);\
+    PSTORE128((C)+6,z4);\
+    PSTORE128((C)+8,z5);\
+    PSTORE128((C)+10,z6);\
     FINAL_STORE;}
 
 
 #define PCLMUL416_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL448_KAR_FINAL(PSTOREL(C+12,z7),C,x1,x2,x3,x4,\
+        PCLMUL448_KAR_FINAL(PSTOREL((C)+12,z7),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 #define PCLMUL448_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL448_KAR_FINAL(PSTORE128(C+12,z7),C,x1,x2,x3,x4,\
+        PCLMUL448_KAR_FINAL(PSTORE128((C)+12,z7),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 
@@ -4418,36 +4418,36 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL256_WS_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
 \
     PCLMUL256_ADD_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,z3);\
-    PSTORE128(C+6,z4);\
-    PSTORE128(C+8,z5);\
-    PSTORE128(C+10,z6);\
-    PSTORE128(C+12,z7);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,z3);\
+    PSTORE128((C)+6,z4);\
+    PSTORE128((C)+8,z5);\
+    PSTORE128((C)+10,z6);\
+    PSTORE128((C)+12,z7);\
     FINAL_STORE;}
 
 
 #define PCLMUL480_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL512_KAR_FINAL(PSTOREL(C+14,z8),C,x1,x2,x3,x4,\
+        PCLMUL512_KAR_FINAL(PSTOREL((C)+14,z8),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 #define PCLMUL512_KAR_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL512_KAR_FINAL(PSTORE128(C+14,z8),C,x1,x2,x3,x4,\
+        PCLMUL512_KAR_FINAL(PSTORE128((C)+14,z8),C,x1,x2,x3,x4,\
                             y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 
@@ -4458,36 +4458,36 @@
     PCLMUL256_WS_KAR2_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL256_WS_KAR2_GF2X(z5,z6,z7,z8,x3,x4,y3,y4,sum,res1,res2);\
 \
-    x1m=PXOR_(x1,x3);\
-    x2m=PXOR_(x2,x4);\
-    y1m=PXOR_(y1,y3);\
-    y2m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
+    (x1m)=PXOR_(x1,x3);\
+    (x2m)=PXOR_(x2,x4);\
+    (y1m)=PXOR_(y1,y3);\
+    (y2m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
 \
     PCLMUL256_ADD_KAR2_GF2X(z3,z4,z5,z6,t1,t2,x1m,x2m,y1m,y2m,sum,res1,res2);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,z3);\
-    PSTORE128(C+6,z4);\
-    PSTORE128(C+8,z5);\
-    PSTORE128(C+10,z6);\
-    PSTORE128(C+12,z7);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,z3);\
+    PSTORE128((C)+6,z4);\
+    PSTORE128((C)+8,z5);\
+    PSTORE128((C)+10,z6);\
+    PSTORE128((C)+12,z7);\
     FINAL_STORE;}
 
 
 #define PCLMUL480_KAR2_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL512_KAR2_FINAL(PSTOREL(C+14,z8),C,x1,x2,x3,x4,\
+        PCLMUL512_KAR2_FINAL(PSTOREL((C)+14,z8),C,x1,x2,x3,x4,\
                              y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 #define PCLMUL512_KAR2_GF2X(C,x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,sum,res1,res2) \
-        PCLMUL512_KAR2_FINAL(PSTORE128(C+14,z8),C,x1,x2,x3,x4,\
+        PCLMUL512_KAR2_FINAL(PSTORE128((C)+14,z8),C,x1,x2,x3,x4,\
                              y1,y2,y3,y4,z1,z2,sum,res1,res2)
 
 
@@ -4498,39 +4498,39 @@
     PCLMUL256_WS_GF2X(z1,z2,z3,z4,x1,x2,y1,y2,sum,res1,res2);\
     PCLMUL320_WS_GF2X(z5,z6,z7,z8,z9,x3,x4,x5,y3,y4,y5,sum,res1,res2);\
 \
-    x11m=PXOR_(x1,x3);\
-    x22m=PXOR_(x2,x4);\
-    y11m=PXOR_(y1,y3);\
-    y22m=PXOR_(y2,y4);\
-\
-    z5=PXOR_(z3,z5);\
-    z6=PXOR_(z4,z6);\
-    z3=PXOR_(z5,z1);\
-    z4=PXOR_(z6,z2);\
-    z5=PXOR_(z5,z7);\
-    z6=PXOR_(z6,z8);\
-    z7=PXOR_(z7,z9);\
+    (x11m)=PXOR_(x1,x3);\
+    (x22m)=PXOR_(x2,x4);\
+    (y11m)=PXOR_(y1,y3);\
+    (y22m)=PXOR_(y2,y4);\
+\
+    (z5)=PXOR_(z3,z5);\
+    (z6)=PXOR_(z4,z6);\
+    (z3)=PXOR_(z5,z1);\
+    (z4)=PXOR_(z6,z2);\
+    (z5)=PXOR_(z5,z7);\
+    (z6)=PXOR_(z6,z8);\
+    (z7)=PXOR_(z7,z9);\
 \
     PCLMUL320_ADD_GF2X(z3,z4,z5,z6,z7,t1,t2,x11m,x22m,x5,y11m,y22m,y5,\
                        sum,res1,res2);\
 \
     PSTORE128(C,z1);\
-    PSTORE128(C+2,z2);\
-    PSTORE128(C+4,z3);\
-    PSTORE128(C+6,z4);\
-    PSTORE128(C+8,z5);\
-    PSTORE128(C+10,z6);\
-    PSTORE128(C+12,z7);\
-    PSTORE128(C+14,z8);\
+    PSTORE128((C)+2,z2);\
+    PSTORE128((C)+4,z3);\
+    PSTORE128((C)+6,z4);\
+    PSTORE128((C)+8,z5);\
+    PSTORE128((C)+10,z6);\
+    PSTORE128((C)+12,z7);\
+    PSTORE128((C)+14,z8);\
     FINAL_STORE;}
 
 
 #define PCLMUL544_KAR_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)\
-        PCLMUL576_KAR_FINAL(PSTOREL(C+16,z9),C,x1,x2,x3,x4,x5,\
+        PCLMUL576_KAR_FINAL(PSTOREL((C)+16,z9),C,x1,x2,x3,x4,x5,\
                             y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)
 
 #define PCLMUL576_KAR_GF2X(C,x1,x2,x3,x4,x5,y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)\
-        PCLMUL576_KAR_FINAL(PSTORE128(C+16,z9),C,x1,x2,x3,x4,x5,\
+        PCLMUL576_KAR_FINAL(PSTORE128((C)+16,z9),C,x1,x2,x3,x4,x5,\
                             y1,y2,y3,y4,y5,z1,z2,sum,res1,res2)
 
 

