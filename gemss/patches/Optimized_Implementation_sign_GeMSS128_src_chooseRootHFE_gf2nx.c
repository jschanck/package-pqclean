--- upstream/Optimized_Implementation/sign/GeMSS128/src/chooseRootHFE_gf2nx.c
+++ upstream-patched/Optimized_Implementation/sign/GeMSS128/src/chooseRootHFE_gf2nx.c
@@ -29,7 +29,7 @@
  * @remark  A part of the implementation is not in constant-time.
  */
 int PREFIX_NAME(chooseRootHFE_gf2nx)(gf2n root,
-                                     const complete_sparse_monic_gf2nx F,
+                                     complete_sparse_monic_gf2nx F,
                                      cst_gf2n U)
 {
     #if (HFEDeg==1)
@@ -44,76 +44,74 @@
             unsigned int j,i,ind=0;
         #endif
 
-        vec_gf2n roots;
+        UINT roots[HFEDeg * NB_WORD_GFqn] = {0};
         int l;
 
-        l=findRootsHFE_gf2nx(&roots,F,U);
+        l=findRootsHFE_gf2nx(roots,F,U);
 
-        if(!l)
+        if(l==0)
         {
             /* Zero root */
             return 0;
-        } else
+        }
+        if(l==1)
         {
-            if(l==1)
-            {
-                /* One root */
-                copy_gf2n(root,roots);
-            } else
-            {
-                /* Several roots */
-                #if QUARTZ_ROOT
-                    hash=(UINT*)malloc(l*SIZE_DIGEST_UINT*sizeof(UINT));
-
-                    /* We hash each root */
-                    for(i=0;i<l;++i)
+            /* One root */
+            copy_gf2n(root,roots);
+        }
+        else
+        {
+            /* Several roots */
+            #if QUARTZ_ROOT
+                hash=(UINT*)malloc(l*SIZE_DIGEST_UINT*sizeof(UINT));
+
+                /* We hash each root */
+                for(i=0;i<l;++i)
+                {
+                    HASH((unsigned char*)(hash+i*SIZE_DIGEST_UINT),
+                         (unsigned char*)(roots+i*NB_WORD_GFqn),
+                         NB_BYTES_GFqn);
+                }
+
+                /* We search the smallest hash (seen as an integer) */
+                for(i=1;i<l;++i)
+                {
+                    j=0;
+                    while((j<SIZE_DIGEST_UINT)&&
+                          (hash[ind*SIZE_DIGEST_UINT+j]==
+                           hash[i*SIZE_DIGEST_UINT+j]))
                     {
-                        HASH((unsigned char*)(hash+i*SIZE_DIGEST_UINT),
-                             (unsigned char*)(roots+i*NB_WORD_GFqn),
-                             NB_BYTES_GFqn);
+                        ++j;
                     }
-
-                    /* We search the smallest hash (seen as an integer) */
-                    for(i=1;i<l;++i)
+                    if((j<SIZE_DIGEST_UINT)&&
+                       (hash[ind*SIZE_DIGEST_UINT+j]>
+                        hash[i*SIZE_DIGEST_UINT+j]))
                     {
-                        j=0;
-                        while((j<SIZE_DIGEST_UINT)&&
-                              (hash[ind*SIZE_DIGEST_UINT+j]==
-                               hash[i*SIZE_DIGEST_UINT+j]))
-                        {
-                            ++j;
-                        }
-                        if((j<SIZE_DIGEST_UINT)&&
-                           (hash[ind*SIZE_DIGEST_UINT+j]>
-                            hash[i*SIZE_DIGEST_UINT+j]))
-                        {
-                            ind=i;
-                        }
+                        ind=i;
                     }
+                }
 
-                    /* We choose the corresponding root */
-                    copy_gf2n(root,roots+ind*NB_WORD_GFqn);
-
-                    free(hash);
-                #else
+                /* We choose the corresponding root */
+                copy_gf2n(root,roots+ind*NB_WORD_GFqn);
 
-                    /* Sort the roots */
-                    sort_gf2n(roots,l);
+                free(hash);
+            #else
 
-                    #if FIRST_ROOT
-                        /* Choose the first root */
-                        copy_gf2n(root,roots);
-                    #elif DETERMINIST_ROOT
-                        /* Choose a root with a determinist hash */
-                        HASH((unsigned char*)hash,
-                             (unsigned char*)U,NB_BYTES_GFqn);
-                        copy_gf2n(root,roots+(hash[0]%l)*NB_WORD_GFqn);
-                    #endif
+                /* Sort the roots */
+                sort_gf2n(roots,l);
+
+                #if FIRST_ROOT
+                    /* Choose the first root */
+                    copy_gf2n(root,roots);
+                #elif DETERMINIST_ROOT
+                    /* Choose a root with a determinist hash */
+                    HASH((unsigned char*)hash,
+                         (unsigned char*)U,NB_BYTES_GFqn);
+                    copy_gf2n(root,roots+(hash[0]%l)*NB_WORD_GFqn);
                 #endif
-            }
-            free(roots);
-            return l;
+            #endif
         }
+        return l;
     #endif
 }
 #endif

