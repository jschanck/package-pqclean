--- upstream/ref/symmetric-aes.c
+++ upstream-patched/ref/symmetric-aes.c
@@ -7,7 +7,7 @@
                               uint16_t nonce)
 {
   uint8_t expnonce[12] = {0};
-  expnonce[0] = nonce;
-  expnonce[1] = nonce >> 8;
+  expnonce[0] = (uint8_t) nonce;
+  expnonce[1] = (uint8_t) (nonce >> 8);
   aes256ctr_init(state, key, expnonce);
 }

