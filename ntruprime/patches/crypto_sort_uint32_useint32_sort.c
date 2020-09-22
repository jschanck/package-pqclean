--- upstream/crypto_sort/uint32/useint32/sort.c
+++ upstream-patched/crypto_sort/uint32/useint32/sort.c
@@ -10,6 +10,6 @@
   crypto_uint32 *x = array;
   long long j;
   for (j = 0;j < n;++j) x[j] ^= 0x80000000;
-  crypto_sort_int32(array,n);
+  crypto_sort_int32((int32_t *)array,n);
   for (j = 0;j < n;++j) x[j] ^= 0x80000000;
 }

