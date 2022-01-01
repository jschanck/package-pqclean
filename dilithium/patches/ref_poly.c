--- upstream/ref/poly.c
+++ upstream-patched/ref/poly.c
@@ -365,6 +365,7 @@
     buflen = STREAM128_BLOCKBYTES + off;
     ctr += rej_uniform(a->coeffs + ctr, N - ctr, buf, buflen);
   }
+  stream128_release(&state);
 }
 
 /*************************************************
@@ -450,6 +451,7 @@
     stream256_squeezeblocks(buf, 1, &state);
     ctr += rej_eta(a->coeffs + ctr, N - ctr, buf, STREAM256_BLOCKBYTES);
   }
+  stream256_release(&state);
 }
 
 /*************************************************
@@ -473,6 +475,7 @@
 
   stream256_init(&state, seed, nonce);
   stream256_squeezeblocks(buf, POLY_UNIFORM_GAMMA1_NBLOCKS, &state);
+  stream256_release(&state);
   polyz_unpack(a, buf);
 }
 
@@ -490,12 +493,12 @@
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
@@ -507,7 +510,7 @@
   for(i = N-TAU; i < N; ++i) {
     do {
       if(pos >= SHAKE256_RATE) {
-        shake256_squeezeblocks(buf, 1, &state);
+        shake256_inc_squeeze(buf, sizeof buf, &state);
         pos = 0;
       }
 
@@ -518,6 +521,7 @@
     c->coeffs[b] = 1 - 2*(signs & 1);
     signs >>= 1;
   }
+  shake256_inc_ctx_release(&state);
 }
 
 /*************************************************
@@ -536,14 +540,14 @@
 
 #if ETA == 2
   for(i = 0; i < N/8; ++i) {
-    t[0] = ETA - a->coeffs[8*i+0];
-    t[1] = ETA - a->coeffs[8*i+1];
-    t[2] = ETA - a->coeffs[8*i+2];
-    t[3] = ETA - a->coeffs[8*i+3];
-    t[4] = ETA - a->coeffs[8*i+4];
-    t[5] = ETA - a->coeffs[8*i+5];
-    t[6] = ETA - a->coeffs[8*i+6];
-    t[7] = ETA - a->coeffs[8*i+7];
+    t[0] = (uint8_t) (ETA - a->coeffs[8*i+0]);
+    t[1] = (uint8_t) (ETA - a->coeffs[8*i+1]);
+    t[2] = (uint8_t) (ETA - a->coeffs[8*i+2]);
+    t[3] = (uint8_t) (ETA - a->coeffs[8*i+3]);
+    t[4] = (uint8_t) (ETA - a->coeffs[8*i+4]);
+    t[5] = (uint8_t) (ETA - a->coeffs[8*i+5]);
+    t[6] = (uint8_t) (ETA - a->coeffs[8*i+6]);
+    t[7] = (uint8_t) (ETA - a->coeffs[8*i+7]);
 
     r[3*i+0]  = (t[0] >> 0) | (t[1] << 3) | (t[2] << 6);
     r[3*i+1]  = (t[2] >> 2) | (t[3] << 1) | (t[4] << 4) | (t[5] << 7);
@@ -551,8 +555,8 @@
   }
 #elif ETA == 4
   for(i = 0; i < N/2; ++i) {
-    t[0] = ETA - a->coeffs[2*i+0];
-    t[1] = ETA - a->coeffs[2*i+1];
+    t[0] = (uint8_t) (ETA - a->coeffs[2*i+0]);
+    t[1] = (uint8_t) (ETA - a->coeffs[2*i+1]);
     r[i] = t[0] | (t[1] << 4);
   }
 #endif
@@ -619,11 +623,11 @@
   DBENCH_START();
 
   for(i = 0; i < N/4; ++i) {
-    r[5*i+0] = (a->coeffs[4*i+0] >> 0);
-    r[5*i+1] = (a->coeffs[4*i+0] >> 8) | (a->coeffs[4*i+1] << 2);
-    r[5*i+2] = (a->coeffs[4*i+1] >> 6) | (a->coeffs[4*i+2] << 4);
-    r[5*i+3] = (a->coeffs[4*i+2] >> 4) | (a->coeffs[4*i+3] << 6);
-    r[5*i+4] = (a->coeffs[4*i+3] >> 2);
+    r[5*i+0] = (uint8_t) (a->coeffs[4*i+0] >> 0);
+    r[5*i+1] = (uint8_t) ((a->coeffs[4*i+0] >> 8) | (a->coeffs[4*i+1] << 2));
+    r[5*i+2] = (uint8_t) ((a->coeffs[4*i+1] >> 6) | (a->coeffs[4*i+2] << 4));
+    r[5*i+3] = (uint8_t) ((a->coeffs[4*i+2] >> 4) | (a->coeffs[4*i+3] << 6));
+    r[5*i+4] = (uint8_t) (a->coeffs[4*i+3] >> 2);
   }
 
   DBENCH_STOP(*tpack);
@@ -676,26 +680,26 @@
     t[6] = (1 << (D-1)) - a->coeffs[8*i+6];
     t[7] = (1 << (D-1)) - a->coeffs[8*i+7];
 
-    r[13*i+ 0]  =  t[0];
-    r[13*i+ 1]  =  t[0] >>  8;
-    r[13*i+ 1] |=  t[1] <<  5;
-    r[13*i+ 2]  =  t[1] >>  3;
-    r[13*i+ 3]  =  t[1] >> 11;
-    r[13*i+ 3] |=  t[2] <<  2;
-    r[13*i+ 4]  =  t[2] >>  6;
-    r[13*i+ 4] |=  t[3] <<  7;
-    r[13*i+ 5]  =  t[3] >>  1;
-    r[13*i+ 6]  =  t[3] >>  9;
-    r[13*i+ 6] |=  t[4] <<  4;
-    r[13*i+ 7]  =  t[4] >>  4;
-    r[13*i+ 8]  =  t[4] >> 12;
-    r[13*i+ 8] |=  t[5] <<  1;
-    r[13*i+ 9]  =  t[5] >>  7;
-    r[13*i+ 9] |=  t[6] <<  6;
-    r[13*i+10]  =  t[6] >>  2;
-    r[13*i+11]  =  t[6] >> 10;
-    r[13*i+11] |=  t[7] <<  3;
-    r[13*i+12]  =  t[7] >>  5;
+    r[13*i+ 0]  =  (uint8_t) t[0];
+    r[13*i+ 1]  =  (uint8_t) (t[0] >>  8);
+    r[13*i+ 1] |=  (uint8_t) (t[1] <<  5);
+    r[13*i+ 2]  =  (uint8_t) (t[1] >>  3);
+    r[13*i+ 3]  =  (uint8_t) (t[1] >> 11);
+    r[13*i+ 3] |=  (uint8_t) (t[2] <<  2);
+    r[13*i+ 4]  =  (uint8_t) (t[2] >>  6);
+    r[13*i+ 4] |=  (uint8_t) (t[3] <<  7);
+    r[13*i+ 5]  =  (uint8_t) (t[3] >>  1);
+    r[13*i+ 6]  =  (uint8_t) (t[3] >>  9);
+    r[13*i+ 6] |=  (uint8_t) (t[4] <<  4);
+    r[13*i+ 7]  =  (uint8_t) (t[4] >>  4);
+    r[13*i+ 8]  =  (uint8_t) (t[4] >> 12);
+    r[13*i+ 8] |=  (uint8_t) (t[5] <<  1);
+    r[13*i+ 9]  =  (uint8_t) (t[5] >>  7);
+    r[13*i+ 9] |=  (uint8_t) (t[6] <<  6);
+    r[13*i+10]  =  (uint8_t) (t[6] >>  2);
+    r[13*i+11]  =  (uint8_t) (t[6] >> 10);
+    r[13*i+11] |=  (uint8_t) (t[7] <<  3);
+    r[13*i+12]  =  (uint8_t) (t[7] >>  5);
   }
 
   DBENCH_STOP(*tpack);
@@ -785,30 +789,30 @@
     t[2] = GAMMA1 - a->coeffs[4*i+2];
     t[3] = GAMMA1 - a->coeffs[4*i+3];
 
-    r[9*i+0]  = t[0];
-    r[9*i+1]  = t[0] >> 8;
-    r[9*i+2]  = t[0] >> 16;
-    r[9*i+2] |= t[1] << 2;
-    r[9*i+3]  = t[1] >> 6;
-    r[9*i+4]  = t[1] >> 14;
-    r[9*i+4] |= t[2] << 4;
-    r[9*i+5]  = t[2] >> 4;
-    r[9*i+6]  = t[2] >> 12;
-    r[9*i+6] |= t[3] << 6;
-    r[9*i+7]  = t[3] >> 2;
-    r[9*i+8]  = t[3] >> 10;
+    r[9*i+0]  = (uint8_t) t[0];
+    r[9*i+1]  = (uint8_t) (t[0] >> 8);
+    r[9*i+2]  = (uint8_t) (t[0] >> 16);
+    r[9*i+2] |= (uint8_t) (t[1] << 2);
+    r[9*i+3]  = (uint8_t) (t[1] >> 6);
+    r[9*i+4]  = (uint8_t) (t[1] >> 14);
+    r[9*i+4] |= (uint8_t) (t[2] << 4);
+    r[9*i+5]  = (uint8_t) (t[2] >> 4);
+    r[9*i+6]  = (uint8_t) (t[2] >> 12);
+    r[9*i+6] |= (uint8_t) (t[3] << 6);
+    r[9*i+7]  = (uint8_t) (t[3] >> 2);
+    r[9*i+8]  = (uint8_t) (t[3] >> 10);
   }
 #elif GAMMA1 == (1 << 19)
   for(i = 0; i < N/2; ++i) {
     t[0] = GAMMA1 - a->coeffs[2*i+0];
     t[1] = GAMMA1 - a->coeffs[2*i+1];
 
-    r[5*i+0]  = t[0];
-    r[5*i+1]  = t[0] >> 8;
-    r[5*i+2]  = t[0] >> 16;
-    r[5*i+2] |= t[1] << 4;
-    r[5*i+3]  = t[1] >> 4;
-    r[5*i+4]  = t[1] >> 12;
+    r[5*i+0]  = (uint8_t) t[0];
+    r[5*i+1]  = (uint8_t) (t[0] >> 8);
+    r[5*i+2]  = (uint8_t) (t[0] >> 16);
+    r[5*i+2] |= (uint8_t) (t[1] << 4);
+    r[5*i+3]  = (uint8_t) (t[1] >> 4);
+    r[5*i+4]  = (uint8_t) (t[1] >> 12);
   }
 #endif
 
@@ -891,16 +895,16 @@
 
 #if GAMMA2 == (Q-1)/88
   for(i = 0; i < N/4; ++i) {
-    r[3*i+0]  = a->coeffs[4*i+0];
-    r[3*i+0] |= a->coeffs[4*i+1] << 6;
-    r[3*i+1]  = a->coeffs[4*i+1] >> 2;
-    r[3*i+1] |= a->coeffs[4*i+2] << 4;
-    r[3*i+2]  = a->coeffs[4*i+2] >> 4;
-    r[3*i+2] |= a->coeffs[4*i+3] << 2;
+    r[3*i+0]  = (uint8_t) a->coeffs[4*i+0];
+    r[3*i+0] |= (uint8_t) (a->coeffs[4*i+1] << 6);
+    r[3*i+1]  = (uint8_t) (a->coeffs[4*i+1] >> 2);
+    r[3*i+1] |= (uint8_t) (a->coeffs[4*i+2] << 4);
+    r[3*i+2]  = (uint8_t) (a->coeffs[4*i+2] >> 4);
+    r[3*i+2] |= (uint8_t) (a->coeffs[4*i+3] << 2);
   }
 #elif GAMMA2 == (Q-1)/32
   for(i = 0; i < N/2; ++i)
-    r[i] = a->coeffs[2*i+0] | (a->coeffs[2*i+1] << 4);
+    r[i] = (uint8_t) (a->coeffs[2*i+0] | (a->coeffs[2*i+1] << 4));
 #endif
 
   DBENCH_STOP(*tpack);

