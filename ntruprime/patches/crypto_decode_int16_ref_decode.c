--- upstream/crypto_decode/int16/ref/decode.c
+++ upstream-patched/crypto_decode/int16/ref/decode.c
@@ -5,6 +5,6 @@
 {
   crypto_uint16 u0 = s[0];
   crypto_uint16 u1 = s[1];
-  u1 <<= 8;
+  u1 = (crypto_uint16) (u1 << 8);
   *(crypto_uint16 *) x = u0 | u1;
 }

