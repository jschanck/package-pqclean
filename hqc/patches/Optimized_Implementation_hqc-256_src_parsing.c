--- hqc-2020-05-29/Optimized_Implementation/hqc-256/src/parsing.c
+++ hqc-2020-05-29-patched/Optimized_Implementation/hqc-256/src/parsing.c
@@ -10,6 +10,64 @@
 #include <stdint.h>
 #include <string.h>
 
+void store8(unsigned char *out, uint64_t in) {
+	out[0] = (in >> 0x00) & 0xFF;
+	out[1] = (in >> 0x08) & 0xFF;
+	out[2] = (in >> 0x10) & 0xFF;
+	out[3] = (in >> 0x18) & 0xFF;
+	out[4] = (in >> 0x20) & 0xFF;
+	out[5] = (in >> 0x28) & 0xFF;
+	out[6] = (in >> 0x30) & 0xFF;
+	out[7] = (in >> 0x38) & 0xFF;
+}
+
+
+uint64_t load8(const unsigned char *in) {
+	uint64_t ret = in[7];
+
+	for (int8_t i = 6; i >= 0; i--) {
+		ret <<= 8;
+		ret |= in[i];
+	}
+
+	return ret;
+}
+
+void load8_arr(uint64_t *out64, size_t outlen, const uint8_t *in8, size_t inlen) {
+	size_t index_in = 0;
+	size_t index_out = 0;
+
+	// first copy by 8 bytes
+	if (inlen >= 8 && outlen >= 1) {
+		while (index_out < outlen && index_in + 8 <= inlen) {
+			out64[index_out] = load8(in8 + index_in);
+
+			index_in += 8;
+			index_out += 1;
+		}
+	}
+
+	// we now need to do the last 7 bytes if necessary
+	if (index_in >= inlen || index_out >= outlen) {
+		return;
+	}
+	out64[index_out] = in8[inlen - 1];
+	for (int8_t i = (int8_t)(inlen - index_in) - 2; i >= 0; i--) {
+		out64[index_out] <<= 8;
+		out64[index_out] |= in8[index_in + i];
+	}
+}
+
+void store8_arr(uint8_t *out8, size_t outlen, const uint64_t *in64, size_t inlen) {
+	for (size_t index_out = 0, index_in = 0; index_out < outlen && index_in < inlen;) {
+		out8[index_out] = (in64[index_in] >> ((index_out % 8) * 8)) & 0xFF;
+		index_out++;
+		if (index_out % 8 == 0) {
+			index_in++;
+		}
+	}
+}
+
 
 /**
  * @brief Parse a secret key into a string
@@ -22,8 +80,8 @@
  * @param[in] pk String containing the public key
  */
 void hqc_secret_key_to_string(uint8_t *sk, const uint8_t *sk_seed, const uint8_t *pk) {
-	memcpy(sk, sk_seed, SEED_BYTES);
-	memcpy(sk + SEED_BYTES, pk, PUBLIC_KEY_BYTES);
+	memcpy(sk, sk_seed, SEED_BYTES); sk += SEED_BYTES;
+	memcpy(sk, pk, PUBLIC_KEY_BYTES);
 }
 
 /**
@@ -41,12 +99,12 @@
 	AES_XOF_struct sk_seedexpander;
 	uint8_t sk_seed[SEED_BYTES] = {0};
 
-	memcpy(sk_seed, sk, SEED_BYTES);
-	seedexpander_init(&sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);
+	memcpy(sk_seed, sk, SEED_BYTES); sk += SEED_BYTES;
+	memcpy(pk, sk, PUBLIC_KEY_BYTES);
 
+	seedexpander_init(&sk_seedexpander, sk_seed, sk_seed + 32, SEEDEXPANDER_MAX_LENGTH);
 	vect_set_random_fixed_weight(&sk_seedexpander, x, PARAM_OMEGA);
 	vect_set_random_fixed_weight(&sk_seedexpander, y, PARAM_OMEGA);
-	memcpy(pk, sk + SEED_BYTES, PUBLIC_KEY_BYTES);
 }
 
 /**
@@ -60,7 +118,7 @@
  */
 void hqc_public_key_to_string(uint8_t *pk, const uint8_t *pk_seed, const uint64_t *s) {
 	memcpy(pk, pk_seed, SEED_BYTES);
-	memcpy(pk + SEED_BYTES, s, VEC_N_SIZE_BYTES);
+	store8_arr(pk + SEED_BYTES, VEC_N_SIZE_BYTES, s, VEC_N_SIZE_64);
 }
 
 
@@ -78,11 +136,11 @@
 	AES_XOF_struct pk_seedexpander;
 	uint8_t pk_seed[SEED_BYTES] = {0};
 
-	memcpy(pk_seed, pk, SEED_BYTES);
+	memcpy(pk_seed, pk, SEED_BYTES); pk += SEED_BYTES;
+	load8_arr(s, VEC_N_SIZE_64, pk, VEC_N_SIZE_BYTES);
+
 	seedexpander_init(&pk_seedexpander, pk_seed, pk_seed + 32, SEEDEXPANDER_MAX_LENGTH);
 	vect_set_random(&pk_seedexpander, h);
-
-	memcpy(s, pk + SEED_BYTES, VEC_N_SIZE_BYTES);
 }
 
 
@@ -97,9 +155,9 @@
  * @param[in] d String containing the hash d
  */
 void hqc_ciphertext_to_string(uint8_t *ct, const uint64_t *u, const uint64_t *v, const uint8_t *d) {
-	memcpy(ct, u, VEC_N_SIZE_BYTES);
-	memcpy(ct + VEC_N_SIZE_BYTES, v, VEC_N1N2_SIZE_BYTES);
-	memcpy(ct + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES, d, SHA512_BYTES);
+	store8_arr(ct, VEC_N_SIZE_BYTES, u, VEC_N_SIZE_64); ct += VEC_N_SIZE_BYTES;
+	store8_arr(ct, VEC_N1N2_SIZE_BYTES, v, VEC_N1N2_SIZE_64); ct += VEC_N1N2_SIZE_BYTES;
+	memcpy(ct, d, SHA512_BYTES);
 }
 
 
@@ -114,7 +172,7 @@
  * @param[in] ct String containing the ciphertext
  */
 void hqc_ciphertext_from_string(uint64_t *u, uint64_t *v, uint8_t *d, const uint8_t *ct) {
-	memcpy(u, ct, VEC_N_SIZE_BYTES);
-	memcpy(v, ct + VEC_N_SIZE_BYTES, VEC_N1N2_SIZE_BYTES);
-	memcpy(d, ct + VEC_N_SIZE_BYTES + VEC_N1N2_SIZE_BYTES, SHA512_BYTES);
+	load8_arr(u, VEC_N_SIZE_64, ct, VEC_N_SIZE_BYTES); ct += VEC_N_SIZE_BYTES;
+	load8_arr(v, VEC_N1N2_SIZE_64, ct, VEC_N1N2_SIZE_BYTES); ct += VEC_N1N2_SIZE_BYTES;
+	memcpy(d, ct, SHA512_BYTES);
 }

