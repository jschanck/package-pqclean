--- upstream/ref/polyvec.h
+++ upstream-patched/ref/polyvec.h
@@ -25,8 +25,7 @@
 #define polyvec_invntt_tomont KYBER_NAMESPACE(_polyvec_invntt_tomont)
 void polyvec_invntt_tomont(polyvec *r);
 
-#define polyvec_pointwise_acc_montgomery \
-        KYBER_NAMESPACE(_polyvec_pointwise_acc_montgomery)
+#define polyvec_pointwise_acc_montgomery KYBER_NAMESPACE(_polyvec_pointwise_acc_montgomery)
 void polyvec_pointwise_acc_montgomery(poly *r,
                                       const polyvec *a,
                                       const polyvec *b);

