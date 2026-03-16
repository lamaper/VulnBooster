static void prc_destroy ( jpc_enc_prc_t * prc ) {
 jpc_enc_cblk_t * cblk ;
 uint_fast32_t cblkno ;
 if ( prc -> cblks ) {
 for ( cblkno = 0 , cblk = prc -> cblks ;
 cblkno < prc -> numcblks ;
 ++ cblkno , ++ cblk ) {
 cblk_destroy ( cblk ) ;
 }
 jas_free ( prc -> cblks ) ;
 prc -> cblks = NULL ;
 }
 if ( prc -> incltree ) {
 jpc_tagtree_destroy ( prc -> incltree ) ;
 prc -> incltree = NULL ;
 }
 if ( prc -> nlibtree ) {
 jpc_tagtree_destroy ( prc -> nlibtree ) ;
 prc -> nlibtree = NULL ;
 }
 if ( prc -> savincltree ) {
 jpc_tagtree_destroy ( prc -> savincltree ) ;
 prc -> savincltree = NULL ;
 }
 if ( prc -> savnlibtree ) {
 jpc_tagtree_destroy ( prc -> savnlibtree ) ;
 prc -> savnlibtree = NULL ;
 }
 }