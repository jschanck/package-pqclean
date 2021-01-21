--- upstream/ref/poly.c
+++ upstream-patched/ref/poly.c
@@ -383,6 +383,7 @@
     buflen = STREAM128_BLOCKBYTES + off;
     ctr += rej_uniform(a->coeffs + ctr, N - ctr, buf, buflen);
   }
+  stream128_release(&state);
 }
 
 /*************************************************
@@ -468,6 +469,7 @@
     stream128_squeezeblocks(buf, 1, &state);
     ctr += rej_eta(a->coeffs + ctr, N - ctr, buf, STREAM128_BLOCKBYTES);
   }
+  stream128_release(&state);
 }
 
 /*************************************************
@@ -491,6 +493,7 @@
 
   stream256_init(&state, seed, nonce);
   stream256_squeezeblocks(buf, POLY_UNIFORM_GAMMA1_NBLOCKS, &state);
+  stream256_release(&state);
   polyz_unpack(a, buf);
 }
 
@@ -508,12 +511,12 @@
   unsigned int i, b, pos;
   uint64_t signs;
   uint8_t buf[SHAKE256_RATE];
-  keccak_state state;
+  shake256incctx state;
 
-  shake256_init(&state);
-  shake256_absorb(&state, seed, SEEDBYTES);
-  shake256_finalize(&state);
-  shake256_squeezeblocks(buf, 1, &state);
+  shake256_inc_init(&state);
+  shake256_inc_absorb(&state, seed, SEEDBYTES);
+  shake256_inc_finalize(&state);
+  shake256_inc_squeeze(buf, sizeof buf, &state);
 
   signs = 0;
   for(i = 0; i < 8; ++i)
@@ -525,7 +528,7 @@
   for(i = N-TAU; i < N; ++i) {
     do {
       if(pos >= SHAKE256_RATE) {
-        shake256_squeezeblocks(buf, 1, &state);
+        shake256_inc_squeeze(buf, sizeof buf, &state);
         pos = 0;
       }
 
@@ -536,6 +539,7 @@
     c->coeffs[b] = 1 - 2*(signs & 1);
     signs >>= 1;
   }
+  shake256_inc_ctx_release(&state);
 }
 
 /*************************************************

