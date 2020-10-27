--- upstream/avx2/symmetric.h
+++ upstream-patched/avx2/symmetric.h
@@ -7,36 +7,32 @@
 
 #ifdef KYBER_90S
 
-#include <openssl/sha.h>
 #include "aes256ctr.h"
-
-#if (KYBER_SSBYTES != 32)
-#error "90s variant of Kyber can only generate keys of length 256 bits"
-#endif
+#include "sha2.h"
 
 typedef aes256ctr_ctx xof_state;
 
 #define XOF_BLOCKBYTES AES256CTR_BLOCKBYTES
 
-#define hash_h(OUT, IN, INBYTES) SHA256(IN, INBYTES, OUT)
-#define hash_g(OUT, IN, INBYTES) SHA512(IN, INBYTES, OUT)
+#define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
+#define hash_g(OUT, IN, INBYTES) sha512(OUT, IN, INBYTES)
 #define xof_absorb(STATE, SEED, X, Y) \
         aes256ctr_init(STATE, SEED, (X) | ((uint16_t)(Y) << 8))
 #define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) \
         aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)
 #define prf(OUT, OUTBYTES, KEY, NONCE) \
         aes256ctr_prf(OUT, OUTBYTES, KEY, NONCE)
-#define kdf(OUT, IN, INBYTES) SHA256(IN, INBYTES, OUT)
+#define kdf(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
 
 #else
 
 #include "fips202.h"
 #include "fips202x4.h"
 
-typedef keccak_state xof_state;
+typedef shake128ctx xof_state;
 
 #define kyber_shake128_absorb KYBER_NAMESPACE(_kyber_shake128_absorb)
-void kyber_shake128_absorb(keccak_state *s,
+void kyber_shake128_absorb(xof_state *s,
                            const uint8_t seed[KYBER_SYMBYTES],
                            uint8_t x,
                            uint8_t y);
@@ -54,6 +50,7 @@
 #define xof_absorb(STATE, SEED, X, Y) kyber_shake128_absorb(STATE, SEED, X, Y)
 #define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) \
         shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
+#define xof_ctx_release(STATE) shake128_ctx_release(STATE)
 #define prf(OUT, OUTBYTES, KEY, NONCE) \
         kyber_shake256_prf(OUT, OUTBYTES, KEY, NONCE)
 #define kdf(OUT, IN, INBYTES) shake256(OUT, KYBER_SSBYTES, IN, INBYTES)

