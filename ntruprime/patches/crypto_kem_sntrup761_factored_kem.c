--- upstream/crypto_kem/sntrup761/factored/kem.c
+++ upstream-patched/crypto_kem/sntrup761/factored/kem.c
@@ -75,7 +75,7 @@
 {
   unsigned char h[64];
   int i;
-  crypto_hash_sha512(h,in,inlen);
+  crypto_hash_sha512(h,in,(size_t) inlen);
   for (i = 0;i < 32;++i) out[i] = h[i];
 }
 
@@ -92,7 +92,7 @@
   for (i = w;i < p;++i) L[i] = (L[i]&(uint32)-3)|1;
   for (i = p;i < ppadsort;++i) L[i] = 0xffffffff;
   crypto_sort_uint32(L,ppadsort);
-  for (i = 0;i < p;++i) out[i] = (L[i]&3)-1;
+  for (i = 0;i < p;++i) out[i] = (small) ((L[i]&3)-1);
 }
 
 static void Small_random(small *out)
@@ -102,7 +102,7 @@
 
   randombytes((unsigned char *) L,sizeof L);
   crypto_decode_pxint32(L,(unsigned char *) L);
-  for (i = 0;i < p;++i) out[i] = (((L[i]&0x3fffffff)*3)>>30)-1;
+  for (i = 0;i < p;++i) out[i] = (small) ((((L[i]&0x3fffffff)*3)>>30)-1);
 }
 
 /* ----- Streamlined NTRU Prime */
@@ -233,10 +233,10 @@
 
     Hide(x,cnew,r_enc,r,pk,cache);
     mask = crypto_verify_clen(c,cnew);
-    for (i = 0;i < Small_bytes;++i) r_enc[i+1] ^= mask&(r_enc[i+1]^rho[i]);
+    for (i = 0;i < Small_bytes;++i) r_enc[i+1] ^= (unsigned char) (mask&(r_enc[i+1]^rho[i]));
     Hash(x+1,r_enc,1+Small_bytes); /* XXX: can instead do cmov on cached hash of rho */
     for (i = 0;i < Ciphertexts_bytes+Confirm_bytes;++i) x[1+Hash_bytes+i] = c[i];
-    x[0] = 1+mask;
+    x[0] = (unsigned char) (1+mask);
     Hash(k,x,sizeof x);
   }
   return 0;

