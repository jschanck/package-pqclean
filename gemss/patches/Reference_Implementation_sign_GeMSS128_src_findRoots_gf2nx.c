--- upstream/Reference_Implementation/sign/GeMSS128/src/findRoots_gf2nx.c
+++ upstream-patched/Reference_Implementation/sign/GeMSS128/src/findRoots_gf2nx.c
@@ -27,33 +27,23 @@
  * @remark  Requirement: F.L must be initialized with initListDifferences_gf2nx.
  * @remark  A part of the implementation is not in constant-time.
  */
-int PREFIX_NAME(findRootsHFE_gf2nx)(vec_gf2n* roots,
+int PREFIX_NAME(findRootsHFE_gf2nx)(vec_gf2n roots,
                                     const complete_sparse_monic_gf2nx F,
                                     cst_gf2n U)
 {
     #if (HFEDeg==1)
-        *roots=(UINT*)malloc(NB_WORD_GFqn*sizeof(UINT));
-        VERIFY_ALLOC_RET(roots);
-        add_gf2n(*roots,F.poly,U);
+        add_gf2n(roots,F.poly,U);
         return 1;
     #else
 
-    gf2nx tmp_p, poly, poly2;
+    UINT p1[((HFEDeg<<1)-1)*NB_WORD_GFqn]={0};
+    UINT p2[(HFEDeg+1)*NB_WORD_GFqn]={0};
+    UINT *tmp_p;
+    UINT *poly=p1;
+    UINT *poly2=p2;
     unsigned int i,l,d2;
 
     d2=HFEDeg;
-    poly=(UINT*)calloc(((HFEDeg<<1)-1)*NB_WORD_GFqn,sizeof(UINT));
-    if(!poly) 
-    {
-        return ERROR_ALLOC;
-    }
-
-    poly2=(UINT*)calloc((HFEDeg+1)*NB_WORD_GFqn,sizeof(UINT));
-    if(!poly2) 
-    {
-        free(poly);
-        return ERROR_ALLOC;
-    }
 
     /* X^(2^n) - X mod (F-U) */
     l=best_frobeniusMap_HFE_gf2nx(poly,F,U);
@@ -78,26 +68,14 @@
         /* The gcd is a constant (!=0) */
         /* Irreducible: 0 root */
         /* l=0; */
-        free(poly);
-        free(poly2);
         return 0;
-    } else
-    {
-        /* poly2 is the gcd */
-        /* Here, it becomes monic */
-        convMonic_gf2nx(poly2,l);
     }
-    free(poly);
+    /* poly2 is the gcd */
+    /* Here, it becomes monic */
+    convMonic_gf2nx(poly2,l);
 
 
-    *roots=(UINT*)malloc(l*NB_WORD_GFqn*sizeof(UINT));
-    if(!roots) 
-    {
-        free(poly2);
-        return ERROR_ALLOC;
-    }
-    findRootsSplit_gf2nx(*roots,poly2,l);
-    free(poly2);
+    findRootsSplit_gf2nx(roots,poly2,l);
 
     return (int)l;
     #endif
@@ -127,23 +105,15 @@
         return 1;
     #else
 
-    static_gf2n inv[NB_WORD_GFqn];
-    gf2nx tmp_p, poly, poly2;
+    static_gf2n inv[NB_WORD_GFqn]={0};
+    UINT p1[((HFEDeg<<1)-1)*NB_WORD_GFqn]={0};
+    UINT p2[(HFEDeg+1)*NB_WORD_GFqn]={0};
+    UINT *tmp_p;
+    UINT *poly=p1;
+    UINT *poly2=p2;
     unsigned int i,l,d2;
 
     d2=HFEDeg;
-    poly=(UINT*)calloc(((HFEDeg<<1)-1)*NB_WORD_GFqn,sizeof(UINT));
-    if(!poly) 
-    {
-        return ERROR_ALLOC;
-    }
-
-    poly2=(UINT*)calloc((HFEDeg+1)*NB_WORD_GFqn,sizeof(UINT));
-    if(!poly2) 
-    {
-        free(poly);
-        return ERROR_ALLOC;
-    }
 
     /* X^(2^n) - X mod (F-U) */
     l=best_frobeniusMap_HFE_gf2nx(poly,F,U);
@@ -171,20 +141,14 @@
 
         /* else, l roots */
 
-        free(poly);
-        free(poly2);
         return 0;
-    } else
-    {
-        /* poly2 is the gcd such that poly2 = a*x+b. */
-        /* The root is b*a^(-1). */
-        inv_gf2n(inv,poly2+NB_WORD_GFqn);
-        mul_gf2n(root,inv,poly2);
-
-        free(poly);
-        free(poly2);
-        return 1;
     }
+    /* poly2 is the gcd such that poly2 = a*x+b. */
+    /* The root is b*a^(-1). */
+    inv_gf2n(inv,poly2+NB_WORD_GFqn);
+    mul_gf2n(root,inv,poly2);
+
+    return 1;
     #endif
 }
 

