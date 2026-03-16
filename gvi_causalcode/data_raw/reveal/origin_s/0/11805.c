static void read_coef_probs ( FRAME_CONTEXT * fc , TX_MODE tx_mode , vp9_reader * r ) {
 const TX_SIZE max_tx_size = tx_mode_to_biggest_tx_size [ tx_mode ] ;
 TX_SIZE tx_size ;
 for ( tx_size = TX_4X4 ;
 tx_size <= max_tx_size ;
 ++ tx_size ) read_coef_probs_common ( fc -> coef_probs [ tx_size ] , r ) ;
 }