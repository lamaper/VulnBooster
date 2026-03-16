static TX_SIZE read_tx_size ( VP9_COMMON * cm , MACROBLOCKD * xd , TX_MODE tx_mode , BLOCK_SIZE bsize , int allow_select , vp9_reader * r ) {
 const TX_SIZE max_tx_size = max_txsize_lookup [ bsize ] ;
 if ( allow_select && tx_mode == TX_MODE_SELECT && bsize >= BLOCK_8X8 ) return read_selected_tx_size ( cm , xd , max_tx_size , r ) ;
 else return MIN ( max_tx_size , tx_mode_to_biggest_tx_size [ tx_mode ] ) ;
 }