static void read_tx_mode_probs ( struct tx_probs * tx_probs , vp9_reader * r ) {
 int i , j ;
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 ++ i ) for ( j = 0 ;
 j < TX_SIZES - 3 ;
 ++ j ) vp9_diff_update_prob ( r , & tx_probs -> p8x8 [ i ] [ j ] ) ;
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 ++ i ) for ( j = 0 ;
 j < TX_SIZES - 2 ;
 ++ j ) vp9_diff_update_prob ( r , & tx_probs -> p16x16 [ i ] [ j ] ) ;
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 ++ i ) for ( j = 0 ;
 j < TX_SIZES - 1 ;
 ++ j ) vp9_diff_update_prob ( r , & tx_probs -> p32x32 [ i ] [ j ] ) ;
 }