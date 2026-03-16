static void fill_token_costs ( vp9_coeff_cost * c , vp9_coeff_probs_model ( * p ) [ PLANE_TYPES ] ) {
 int i , j , k , l ;
 TX_SIZE t ;
 for ( t = TX_4X4 ;
 t <= TX_32X32 ;
 ++ t ) for ( i = 0 ;
 i < PLANE_TYPES ;
 ++ i ) for ( j = 0 ;
 j < REF_TYPES ;
 ++ j ) for ( k = 0 ;
 k < COEF_BANDS ;
 ++ k ) for ( l = 0 ;
 l < BAND_COEFF_CONTEXTS ( k ) ;
 ++ l ) {
 vp9_prob probs [ ENTROPY_NODES ] ;
 vp9_model_to_full_probs ( p [ t ] [ i ] [ j ] [ k ] [ l ] , probs ) ;
 vp9_cost_tokens ( ( int * ) c [ t ] [ i ] [ j ] [ k ] [ 0 ] [ l ] , probs , vp9_coef_tree ) ;
 vp9_cost_tokens_skip ( ( int * ) c [ t ] [ i ] [ j ] [ k ] [ 1 ] [ l ] , probs , vp9_coef_tree ) ;
 assert ( c [ t ] [ i ] [ j ] [ k ] [ 0 ] [ l ] [ EOB_TOKEN ] == c [ t ] [ i ] [ j ] [ k ] [ 1 ] [ l ] [ EOB_TOKEN ] ) ;
 }
 }