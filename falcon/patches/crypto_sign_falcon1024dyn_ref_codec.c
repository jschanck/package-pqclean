--- upstream/crypto_sign/falcon1024dyn/ref/codec.c
+++ upstream-patched/crypto_sign/falcon1024dyn/ref/codec.c
@@ -451,7 +451,10 @@
 				return 0;
 			}
 		}
-		x[u] = (int16_t)(s ? -(int)m : (int)m);
+		x[u] = (int16_t) m;
+		if (s) {
+		    x[u] = (int16_t) - x[u];
+		}
 	}
 	return v;
 }

