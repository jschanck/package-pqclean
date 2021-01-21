--- upstream/ref/polyvec.h
+++ upstream-patched/ref/polyvec.h
@@ -31,8 +31,7 @@
 void polyvecl_invntt_tomont(polyvecl *v);
 #define polyvecl_pointwise_poly_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_poly_montgomery)
 void polyvecl_pointwise_poly_montgomery(polyvecl *r, const poly *a, const polyvecl *v);
-#define polyvecl_pointwise_acc_montgomery \
-        DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
+#define polyvecl_pointwise_acc_montgomery DILITHIUM_NAMESPACE(polyvecl_pointwise_acc_montgomery)
 void polyvecl_pointwise_acc_montgomery(poly *w,
                                        const polyvecl *u,
                                        const polyvecl *v);
@@ -84,7 +83,7 @@
                                 const polyveck *v0,
                                 const polyveck *v1);
 #define polyveck_use_hint DILITHIUM_NAMESPACE(polyveck_use_hint)
-void polyveck_use_hint(polyveck *w, const polyveck *v, const polyveck *h);
+void polyveck_use_hint(polyveck *w, const polyveck *u, const polyveck *h);
 
 #define polyveck_pack_w1 DILITHIUM_NAMESPACE(polyveck_pack_w1)
 void polyveck_pack_w1(uint8_t r[K*POLYW1_PACKEDBYTES], const polyveck *w1);

