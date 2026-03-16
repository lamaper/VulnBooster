static void encode_txfm_probs ( VP9_COMMON * cm , vp9_writer * w ) {
 vp9_write_literal ( w , MIN ( cm -> tx_mode , ALLOW_32X32 ) , 2 ) ;
 if ( cm -> tx_mode >= ALLOW_32X32 ) vp9_write_bit ( w , cm -> tx_mode == TX_MODE_SELECT ) ;
 if ( cm -> tx_mode == TX_MODE_SELECT ) {
 int i , j ;
 unsigned int ct_8x8p [ TX_SIZES - 3 ] [ 2 ] ;
 unsigned int ct_16x16p [ TX_SIZES - 2 ] [ 2 ] ;
 unsigned int ct_32x32p [ TX_SIZES - 1 ] [ 2 ] ;
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 i ++ ) {
 tx_counts_to_branch_counts_8x8 ( cm -> counts . tx . p8x8 [ i ] , ct_8x8p ) ;
 for ( j = 0 ;
 j < TX_SIZES - 3 ;
 j ++ ) vp9_cond_prob_diff_update ( w , & cm -> fc . tx_probs . p8x8 [ i ] [ j ] , ct_8x8p [ j ] ) ;
 }
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 i ++ ) {
 tx_counts_to_branch_counts_16x16 ( cm -> counts . tx . p16x16 [ i ] , ct_16x16p ) ;
 for ( j = 0 ;
 j < TX_SIZES - 2 ;
 j ++ ) vp9_cond_prob_diff_update ( w , & cm -> fc . tx_probs . p16x16 [ i ] [ j ] , ct_16x16p [ j ] ) ;
 }
 for ( i = 0 ;
 i < TX_SIZE_CONTEXTS ;
 i ++ ) {
 tx_counts_to_branch_counts_32x32 ( cm -> counts . tx . p32x32 [ i ] , ct_32x32p ) ;
 for ( j = 0 ;
 j < TX_SIZES - 1 ;
 j ++ ) vp9_cond_prob_diff_update ( w , & cm -> fc . tx_probs . p32x32 [ i ] [ j ] , ct_32x32p [ j ] ) ;
 }
 }
 }