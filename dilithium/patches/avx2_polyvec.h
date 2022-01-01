--- upstream/avx2/polyvec.h
+++ upstream-patched/avx2/polyvec.h
@@ -28,8 +28,7 @@
 void polyvecl_invntt_tomont(polyvecl *v);
 #define polyvecl_pointwise_poly_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_poly_montgomery)
 void polyvecl_pointwise_poly_montgomery(polyvecl *r, const poly *a, const polyvecl *v);
-#define polyvecl_pointwise_acc_montgomery \
-        DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
+#define polyvecl_pointwise_acc_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
 void polyvecl_pointwise_acc_montgomery(poly *w,
                                        const polyvecl *u,
                                        const polyvecl *v);
@@ -74,7 +73,7 @@
 #define polyveck_make_hint DILITHIUM_NAMESPACE(polyveck_make_hint)
 unsigned int polyveck_make_hint(uint8_t *hint, const polyveck *v0, const polyveck *v1);
 #define polyveck_use_hint DILITHIUM_NAMESPACE(polyveck_use_hint)
-void polyveck_use_hint(polyveck *w, const polyveck *v, const polyveck *h);
+void polyveck_use_hint(polyveck *w, const polyveck *u, const polyveck *h);
 
 #define polyveck_pack_w1 DILITHIUM_NAMESPACE(polyveck_pack_w1)
 void polyveck_pack_w1(uint8_t r[K*POLYW1_PACKEDBYTES], const polyveck *w1);

