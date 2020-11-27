--- upstream/avx2/indcpa.c
+++ upstream-patched/avx2/indcpa.c
@@ -273,7 +273,7 @@
   ALIGNED_UINT8(REJ_UNIFORM_AVX_NBLOCKS*SHAKE128_RATE) buf[4];
   __m256i f;
   keccakx4_state state;
-  keccak_state state1x;
+  xof_state state1x;
 
   f = _mm256_loadu_si256((__m256i *)seed);
   _mm256_store_si256(buf[0].vec, f);
@@ -377,14 +377,14 @@
   _mm256_store_si256(buf[0].vec, f);
   buf[0].coeffs[32] = 2;
   buf[0].coeffs[33] = 2;
-  shake128_absorb_once(&state1x, buf[0].coeffs, 34);
+  shake128_absorb(&state1x, buf[0].coeffs, 34);
   shake128_squeezeblocks(buf[0].coeffs, REJ_UNIFORM_AVX_NBLOCKS, &state1x);
   ctr0 = rej_uniform_avx(a[2].vec[2].coeffs, buf[0].coeffs);
   while(ctr0 < KYBER_N) {
     shake128_squeezeblocks(buf[0].coeffs, 1, &state1x);
     ctr0 += rej_uniform(a[2].vec[2].coeffs + ctr0, KYBER_N - ctr0, buf[0].coeffs, SHAKE128_RATE);
   }
-
+  xof_ctx_release(&state1x);
   poly_nttunpack(&a[2].vec[2]);
 }
 #elif KYBER_K == 4

