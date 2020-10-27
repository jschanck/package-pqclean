--- upstream/ref/ntt.h
+++ upstream-patched/ref/ntt.h
@@ -11,10 +11,10 @@
 extern const int16_t zetas_inv[128];
 
 #define ntt KYBER_NAMESPACE(_ntt)
-void ntt(int16_t poly[256]);
+void ntt(int16_t r[256]);
 
 #define invntt KYBER_NAMESPACE(_invntt)
-void invntt(int16_t poly[256]);
+void invntt(int16_t r[256]);
 
 #define basemul KYBER_NAMESPACE(_basemul)
 void basemul(int16_t r[2],

