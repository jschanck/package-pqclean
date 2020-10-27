--- upstream/ref/symmetric-shake.c
+++ upstream-patched/ref/symmetric-shake.c
@@ -9,14 +9,14 @@
 *
 * Description: Absorb step of the SHAKE128 specialized for the Kyber context.
 *
-* Arguments:   - keccak_state *state: pointer to (uninitialized) output
-*                                     Keccak state
+* Arguments:   - xof_state *state: pointer to (uninitialized) output
+*                                  Keccak state
 *              - const uint8_t *seed: pointer to KYBER_SYMBYTES input
 *                                     to be absorbed into state
 *              - uint8_t i            additional byte of input
 *              - uint8_t j            additional byte of input
 **************************************************/
-void kyber_shake128_absorb(keccak_state *state,
+void kyber_shake128_absorb(xof_state *state,
                            const uint8_t seed[KYBER_SYMBYTES],
                            uint8_t x,
                            uint8_t y)

