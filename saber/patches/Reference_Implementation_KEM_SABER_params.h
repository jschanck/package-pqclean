--- upstream/Reference_Implementation_KEM/SABER_params.h
+++ upstream-patched/Reference_Implementation_KEM/SABER_params.h
@@ -2,18 +2,18 @@
 #define PARAMS_H
 
 /* Change this for different security strengths */
-// #define SABER_L 2 /* LightSaber */
-#define SABER_L 3 /* Saber */
-// #define SABER_L 4 /* FireSaber */
 
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

