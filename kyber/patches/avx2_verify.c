--- upstream/avx2/verify.c
+++ upstream-patched/avx2/verify.c
@@ -27,7 +27,7 @@
     avec = _mm256_xor_si256(avec, bvec);
     cvec = _mm256_or_si256(cvec, avec);
   }
-  r = !_mm256_testz_si256(cvec,cvec);
+  r = 1-_mm256_testz_si256(cvec,cvec);
 
   if(pos < len) {
     avec = _mm256_loadu_si256((__m256i *)&a[pos]);

