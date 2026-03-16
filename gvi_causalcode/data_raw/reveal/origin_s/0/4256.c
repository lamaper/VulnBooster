static void update_mv_probs ( vp9_prob * p , int n , vp9_reader * r ) {
 int i ;
 for ( i = 0 ;
 i < n ;
 ++ i ) if ( vp9_read ( r , MV_UPDATE_PROB ) ) p [ i ] = ( vp9_read_literal ( r , 7 ) << 1 ) | 1 ;
 }