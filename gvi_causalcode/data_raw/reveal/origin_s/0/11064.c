static void truespeech_update_filters ( TSContext * dec , int16_t * out , int quart ) {
 int i ;
 memmove ( dec -> filtbuf , & dec -> filtbuf [ 60 ] , 86 * sizeof ( * dec -> filtbuf ) ) ;
 for ( i = 0 ;
 i < 60 ;
 i ++ ) {
 dec -> filtbuf [ i + 86 ] = out [ i ] + dec -> newvec [ i ] - ( dec -> newvec [ i ] >> 3 ) ;
 out [ i ] += dec -> newvec [ i ] ;
 }
 }