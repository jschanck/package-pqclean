--- upstream/Reference_Implementation/hqc-128/src/parsing.h
+++ upstream-patched/Reference_Implementation/hqc-128/src/parsing.h
@@ -8,6 +8,11 @@
 
 #include <stdint.h>
 
+void store8(unsigned char *out, uint64_t in);
+uint64_t load8(const unsigned char *in);
+void load8_arr(uint64_t *out64, size_t outlen, const uint8_t *in8, size_t inlen);
+void store8_arr(uint8_t *out8, size_t outlen, const uint64_t *in64, size_t inlen);
+
 void hqc_secret_key_to_string(uint8_t *sk, const uint8_t *sk_seed, const uint8_t *pk);
 void hqc_secret_key_from_string(uint64_t *x, uint32_t *y, uint8_t *pk, const uint8_t *sk);
 

