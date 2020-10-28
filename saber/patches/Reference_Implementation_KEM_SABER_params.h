--- upstream/Reference_Implementation_KEM/SABER_params.h
+++ upstream-patched/Reference_Implementation_KEM/SABER_params.h
@@ -1,29 +1,31 @@
 #ifndef PARAMS_H
 #define PARAMS_H
 
-/* Change this for different security strengths */
-// #define SABER_L 2 /* LightSaber */
-#define SABER_L 3 /* Saber */
-// #define SABER_L 4 /* FireSaber */
-
 /* Don't change anything below this line */
-#if SABER_L == 2
+#if LightSaber
+	#define SABER_L 2
 	#define SABER_MU 10
 	#define SABER_ET 3
-#elif SABER_L == 3
+#elif Saber
+	#define SABER_L 3
 	#define SABER_MU 8
 	#define SABER_ET 4
-#elif SABER_L == 4
+#elif FireSaber
+	#define SABER_L 4
 	#define SABER_MU 6
 	#define SABER_ET 6
 #endif
 
-#define SABER_EQ 13
-#define SABER_EP 10
 #define SABER_N 256
 
+#define SABER_EP 10
+#define SABER_P (1 << SABER_EP)
+
+#define SABER_EQ 13
+#define SABER_Q (1 << SABER_EQ)
+
 #define SABER_SEEDBYTES 32
-#define SABER_NOISE_SEEDBYTES 32
+#define SABER_NOISESEEDBYTES 32
 #define SABER_KEYBYTES 32
 #define SABER_HASHBYTES 32
 

