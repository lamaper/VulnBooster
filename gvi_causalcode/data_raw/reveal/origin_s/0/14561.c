static void read_inter_mode_probs ( FRAME_CONTEXT * fc , vp9_reader * r ) {
 int i , j ;
 for ( i = 0 ;
 i < INTER_MODE_CONTEXTS ;
 ++ i ) for ( j = 0 ;
 j < INTER_MODES - 1 ;
 ++ j ) vp9_diff_update_prob ( r , & fc -> inter_mode_probs [ i ] [ j ] ) ;
 }