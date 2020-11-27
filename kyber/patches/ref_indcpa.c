--- upstream/ref/indcpa.c
+++ upstream-patched/ref/indcpa.c
@@ -171,9 +171,9 @@
   for(i=0;i<KYBER_K;i++) {
     for(j=0;j<KYBER_K;j++) {
       if(transposed)
-        xof_absorb(&state, seed, i, j);
+        xof_absorb(&state, seed, (uint8_t)i, (uint8_t)j);
       else
-        xof_absorb(&state, seed, j, i);
+        xof_absorb(&state, seed, (uint8_t)j, (uint8_t)i);
 
       xof_squeezeblocks(buf, GEN_MATRIX_NBLOCKS, &state);
       buflen = GEN_MATRIX_NBLOCKS*XOF_BLOCKBYTES;
@@ -187,6 +187,7 @@
         buflen = off + XOF_BLOCKBYTES;
         ctr += rej_uniform(a[i].vec[j].coeffs + ctr, KYBER_N - ctr, buf, buflen);
       }
+      xof_ctx_release(&state);
     }
   }
 }

