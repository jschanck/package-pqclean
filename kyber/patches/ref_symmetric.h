--- upstream/ref/symmetric.h
+++ upstream-patched/ref/symmetric.h
@@ -7,17 +7,17 @@
 
 #ifdef KYBER_90S
 
-#include "aes256ctr.h"
+#include "symmetric-aes.h"
 #include "sha2.h"
 
 #if (KYBER_SSBYTES != 32)
 #error "90s variant of Kyber can only generate keys of length 256 bits"
 #endif
 
-typedef aes256ctr_ctx xof_state;
+typedef aes256xof_ctx xof_state;
 
 #define kyber_aes256xof_absorb KYBER_NAMESPACE(kyber_aes256xof_absorb)
-void kyber_aes256xof_absorb(aes256ctr_ctx *state, const uint8_t seed[32], uint8_t x, uint8_t y);
+void kyber_aes256xof_absorb(aes256xof_ctx *state, const uint8_t seed[32], uint8_t x, uint8_t y);
 
 #define kyber_aes256ctr_prf KYBER_NAMESPACE(kyber_aes256ctr_prf)
 void kyber_aes256ctr_prf(uint8_t *out, size_t outlen, const uint8_t key[32], uint8_t nonce);
@@ -26,19 +26,20 @@
 
 #define hash_h(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
 #define hash_g(OUT, IN, INBYTES) sha512(OUT, IN, INBYTES)
-#define xof_absorb(STATE, SEED, X, Y) kyber_aes256xof_absorb(STATE, SEED, X, Y)
-#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) aes256ctr_squeezeblocks(OUT, OUTBLOCKS, STATE)
-#define prf(OUT, OUTBYTES, KEY, NONCE) kyber_aes256ctr_prf(OUT, OUTBYTES, KEY, NONCE)
+#define xof_absorb(STATE, SEED, X, Y) aes256xof_absorb(STATE, SEED, X, Y)
+#define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) aes256xof_squeezeblocks(OUT, OUTBLOCKS, STATE)
+#define xof_ctx_release(STATE) aes256xof_ctx_release(STATE)
+#define prf(OUT, OUTBYTES, KEY, NONCE) aes256ctr_prf(OUT, OUTBYTES, KEY, NONCE)
 #define kdf(OUT, IN, INBYTES) sha256(OUT, IN, INBYTES)
 
 #else
 
 #include "fips202.h"
 
-typedef keccak_state xof_state;
+typedef shake128ctx xof_state;
 
 #define kyber_shake128_absorb KYBER_NAMESPACE(kyber_shake128_absorb)
-void kyber_shake128_absorb(keccak_state *s,
+void kyber_shake128_absorb(xof_state *s,
                            const uint8_t seed[KYBER_SYMBYTES],
                            uint8_t x,
                            uint8_t y);
@@ -52,6 +53,7 @@
 #define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)
 #define xof_absorb(STATE, SEED, X, Y) kyber_shake128_absorb(STATE, SEED, X, Y)
 #define xof_squeezeblocks(OUT, OUTBLOCKS, STATE) shake128_squeezeblocks(OUT, OUTBLOCKS, STATE)
+#define xof_ctx_release(STATE) shake128_ctx_release(STATE)
 #define prf(OUT, OUTBYTES, KEY, NONCE) kyber_shake256_prf(OUT, OUTBYTES, KEY, NONCE)
 #define kdf(OUT, IN, INBYTES) shake256(OUT, KYBER_SSBYTES, IN, INBYTES)
 

