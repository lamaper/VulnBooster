static void read_switchable_interp_probs ( FRAME_CONTEXT * fc , vp9_reader * r ) {
 int i , j ;
 for ( j = 0 ;
 j < SWITCHABLE_FILTER_CONTEXTS ;
 ++ j ) for ( i = 0 ;
 i < SWITCHABLE_FILTERS - 1 ;
 ++ i ) vp9_diff_update_prob ( r , & fc -> switchable_interp_prob [ j ] [ i ] ) ;
 }