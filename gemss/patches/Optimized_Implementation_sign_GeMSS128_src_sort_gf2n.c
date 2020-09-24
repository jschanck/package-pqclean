--- upstream/Optimized_Implementation/sign/GeMSS128/src/sort_gf2n.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/sort_gf2n.c
@@ -111,7 +111,7 @@
 
     /* The power of 2 before l, which is 1<<position(MSB(l-1)). */
     pow2_prev=2;
-    while(pow2_prev<l)
+    while(pow2_prev<(unsigned int)l)
     {
         pow2_prev<<=1;
     }
@@ -123,7 +123,14 @@
         /* Size of the remainder block */
         rem=l-(pa<<1)*quo;
         /* Impact on the sort */
-        rem=(rem<=pa)?0:(rem-pa);
+        if (rem<=pa)
+        {
+            rem=0;
+        }
+        else
+        {
+            rem=rem-pa;
+        }
 
         tab_i=tab;
         tab_ipa=tab+pa*NB_WORD_GFqn;
@@ -171,7 +178,7 @@
     /* pa=1 */
     tab_i=tab;
     tab_ipa=tab+NB_WORD_GFqn;
-    for(i=0;i<(l-1);i+=2)
+    for(i=0;i<(unsigned int)(l-1);i+=2)
     {
         CMP_AND_SWAP_CST_TIME(tab_i,tab_ipa);
         tab_i+=NB_WORD_GFqn<<1;

