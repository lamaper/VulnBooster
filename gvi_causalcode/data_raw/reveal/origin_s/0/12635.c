static void free_mode_context ( PICK_MODE_CONTEXT * ctx ) {
 int i , k ;
 vpx_free ( ctx -> zcoeff_blk ) ;
 ctx -> zcoeff_blk = 0 ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 ++ i ) {
 for ( k = 0 ;
 k < 3 ;
 ++ k ) {
 vpx_free ( ctx -> coeff [ i ] [ k ] ) ;
 ctx -> coeff [ i ] [ k ] = 0 ;
 vpx_free ( ctx -> qcoeff [ i ] [ k ] ) ;
 ctx -> qcoeff [ i ] [ k ] = 0 ;
 vpx_free ( ctx -> dqcoeff [ i ] [ k ] ) ;
 ctx -> dqcoeff [ i ] [ k ] = 0 ;
 vpx_free ( ctx -> eobs [ i ] [ k ] ) ;
 ctx -> eobs [ i ] [ k ] = 0 ;
 }
 }
 }