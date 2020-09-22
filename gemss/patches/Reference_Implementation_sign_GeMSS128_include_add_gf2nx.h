--- GeMSS-Round2_V2.a/Reference_Implementation/sign/GeMSS128/include/add_gf2nx.h
+++ GeMSS-Round2_V2.a-patched/Reference_Implementation/sign/GeMSS128/include/add_gf2nx.h
@@ -14,7 +14,7 @@
  * @remark  Constant-time implementation when len is not secret.
  */
 #define add2_gf2nx(res,A,len,i) \
-    for(i=0;i<((len)*NB_WORD_GFqn);++i)\
+    for((i)=0;(i)<((len)*NB_WORD_GFqn);++(i))\
     {\
         (res)[i]^=(A)[i];\
     }
@@ -30,7 +30,7 @@
  * @remark  Constant-time implementation when len is not secret.
  */
 #define copy_gf2nx(res,A,len,i) \
-    for(i=0;i<((len)*NB_WORD_GFqn);++i)\
+    for((i)=0;(i)<((len)*NB_WORD_GFqn);++(i))\
     {\
         (res)[i]=(A)[i];\
     }
@@ -45,7 +45,7 @@
  * @remark  Constant-time implementation when len is not secret.
  */
 #define set0_gf2nx(res,len,i) \
-    for(i=0;i<((len)*NB_WORD_GFqn);++i)\
+    for((i)=0;(i)<((len)*NB_WORD_GFqn);++(i))\
     {\
         (res)[i]=0;\
     }

