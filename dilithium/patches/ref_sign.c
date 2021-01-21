--- upstream/ref/sign.c
+++ upstream-patched/ref/sign.c
@@ -90,7 +90,7 @@
   polyvecl mat[K], s1, y, z;
   polyveck t0, s2, w1, w0, h;
   poly cp;
-  keccak_state state;
+  shake256incctx state;
 
   rho = seedbuf;
   tr = rho + SEEDBYTES;
@@ -100,11 +100,12 @@
   unpack_sk(rho, tr, key, &t0, &s1, &s2, sk);
 
   /* Compute CRH(tr, msg) */
-  shake256_init(&state);
-  shake256_absorb(&state, tr, CRHBYTES);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, tr, CRHBYTES);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
 #ifdef DILITHIUM_RANDOMIZED_SIGNING
   randombytes(rhoprime, CRHBYTES);
@@ -134,11 +135,12 @@
   polyveck_decompose(&w1, &w0, &w1);
   polyveck_pack_w1(sig, &w1);
 
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(sig, SEEDBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, sig, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(sig, SEEDBYTES, &state);
+  shake256_inc_ctx_release(&state);
   poly_challenge(&cp, sig);
   poly_ntt(&cp);
 
@@ -236,7 +238,7 @@
   poly cp;
   polyvecl mat[K], z;
   polyveck t1, w1, h;
-  keccak_state state;
+  shake256incctx state;
 
   if(siglen != CRYPTO_BYTES)
     return -1;
@@ -249,11 +251,12 @@
 
   /* Compute CRH(CRH(rho, t1), msg) */
   crh(mu, pk, CRYPTO_PUBLICKEYBYTES);
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, m, mlen);
-  shake256_finalize(&state);
-  shake256_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, m, mlen);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(mu, CRHBYTES, &state);
+  shake256_inc_ctx_release(&state);
 
   /* Matrix-vector multiplication; compute Az - c2^dt1 */
   poly_challenge(&cp, c);
@@ -277,14 +280,17 @@
   polyveck_pack_w1(buf, &w1);
 
   /* Call random oracle and verify challenge */
-  shake256_init(&state);
-  shake256_absorb(&state, mu, CRHBYTES);
-  shake256_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeeze(c2, SEEDBYTES, &state);
-  for(i = 0; i < SEEDBYTES; ++i)
-    if(c[i] != c2[i])
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, mu, CRHBYTES);
+  shake256_inc_absorb(&state, buf, K*POLYW1_PACKEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(c2, SEEDBYTES, &state);
+  shake256_inc_ctx_release(&state);
+  for(i = 0; i < SEEDBYTES; ++i) {
+    if(c[i] != c2[i]) {
       return -1;
+    }
+  }
 
   return 0;
 }
@@ -326,7 +332,7 @@
 
 badsig:
   /* Signature verification failed */
-  *mlen = -1;
+  *mlen = (size_t) -1;
   for(i = 0; i < smlen; ++i)
     m[i] = 0;
 

