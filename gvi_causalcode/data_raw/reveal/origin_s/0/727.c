static void write_selected_tx_size ( const VP9_COMMON * cm , const MACROBLOCKD * xd , TX_SIZE tx_size , BLOCK_SIZE bsize , vp9_writer * w ) {
 const TX_SIZE max_tx_size = max_txsize_lookup [ bsize ] ;
 const vp9_prob * const tx_probs = get_tx_probs2 ( max_tx_size , xd , & cm -> fc . tx_probs ) ;
 vp9_write ( w , tx_size != TX_4X4 , tx_probs [ 0 ] ) ;
 if ( tx_size != TX_4X4 && max_tx_size >= TX_16X16 ) {
 vp9_write ( w , tx_size != TX_8X8 , tx_probs [ 1 ] ) ;
 if ( tx_size != TX_8X8 && max_tx_size >= TX_32X32 ) vp9_write ( w , tx_size != TX_16X16 , tx_probs [ 2 ] ) ;
 }
 }