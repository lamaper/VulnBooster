static void read_coef_probs_common ( vp9_coeff_probs_model * coef_probs , vp9_reader * r ) {
 int i , j , k , l , m ;
 if ( vp9_read_bit ( r ) ) for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) for ( m = 0 ;
 m < UNCONSTRAINED_NODES ;
 ++ m ) vp9_diff_update_prob ( r , & coef_probs [ i ] [ j ] [ k ] [ l ] [ m ] ) ;
 }