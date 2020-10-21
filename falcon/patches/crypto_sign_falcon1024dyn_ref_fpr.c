--- upstream/crypto_sign/falcon1024dyn/ref/fpr.c
+++ upstream-patched/crypto_sign/falcon1024dyn/ref/fpr.c
@@ -544,7 +544,7 @@
 	};
 
 	uint64_t z, y;
-	unsigned u;
+	size_t u;
 	uint32_t z0, z1, y0, y1;
 	uint64_t a, b;
 

