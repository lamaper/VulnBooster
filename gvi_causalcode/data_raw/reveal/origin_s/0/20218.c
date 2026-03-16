static void cblk_destroy ( jpc_enc_cblk_t * cblk ) {
 uint_fast16_t passno ;
 jpc_enc_pass_t * pass ;
 if ( cblk -> passes ) {
 for ( passno = 0 , pass = cblk -> passes ;
 passno < cblk -> numpasses ;
 ++ passno , ++ pass ) {
 pass_destroy ( pass ) ;
 }
 jas_free ( cblk -> passes ) ;
 cblk -> passes = NULL ;
 }
 if ( cblk -> stream ) {
 jas_stream_close ( cblk -> stream ) ;
 cblk -> stream = NULL ;
 }
 if ( cblk -> mqenc ) {
 jpc_mqenc_destroy ( cblk -> mqenc ) ;
 cblk -> mqenc = NULL ;
 }
 if ( cblk -> data ) {
 jas_seq2d_destroy ( cblk -> data ) ;
 cblk -> data = NULL ;
 }
 if ( cblk -> flags ) {
 jas_seq2d_destroy ( cblk -> flags ) ;
 cblk -> flags = NULL ;
 }
 }