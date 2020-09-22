--- upstream/crypto_decode/653x3/avx/decode.c
+++ upstream-patched/crypto_decode/653x3/avx/decode.c
@@ -63,5 +63,5 @@
     nextf += 128;
   }
 
-  *f = ((uint8)(*s&3))-1;
+  *f = (uint8) ((*s&3)-1);
 }

