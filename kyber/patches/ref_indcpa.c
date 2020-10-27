--- upstream/ref/indcpa.c
+++ upstream-patched/ref/indcpa.c
@@ -194,6 +194,7 @@
         ctr += rej_uniform(a[i].vec[j].coeffs + ctr, KYBER_N - ctr, buf,
                            XOF_BLOCKBYTES);
       }
+      xof_ctx_release(&state);
     }
   }
 }

