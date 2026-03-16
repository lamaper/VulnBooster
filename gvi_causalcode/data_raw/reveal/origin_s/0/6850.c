void jpc_enc_destroy ( jpc_enc_t * enc ) {
 if ( enc -> curtile ) {
 jpc_enc_tile_destroy ( enc -> curtile ) ;
 }
 if ( enc -> cp ) {
 jpc_enc_cp_destroy ( enc -> cp ) ;
 }
 if ( enc -> cstate ) {
 jpc_cstate_destroy ( enc -> cstate ) ;
 }
 if ( enc -> tmpstream ) {
 jas_stream_close ( enc -> tmpstream ) ;
 }
 jas_free ( enc ) ;
 }