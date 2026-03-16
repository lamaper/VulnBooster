static TX_SIZE read_selected_tx_size ( VP9_COMMON * cm , MACROBLOCKD * xd , TX_SIZE max_tx_size , vp9_reader * r ) {
 const int ctx = vp9_get_tx_size_context ( xd ) ;
 const vp9_prob * tx_probs = get_tx_probs ( max_tx_size , ctx , & cm -> fc . tx_probs ) ;
 int tx_size = vp9_read ( r , tx_probs [ 0 ] ) ;
 if ( tx_size != TX_4X4 && max_tx_size >= TX_16X16 ) {
 tx_size += vp9_read ( r , tx_probs [ 1 ] ) ;
 if ( tx_size != TX_8X8 && max_tx_size >= TX_32X32 ) tx_size += vp9_read ( r , tx_probs [ 2 ] ) ;
 }
 if ( ! cm -> frame_parallel_decoding_mode ) ++ get_tx_counts ( max_tx_size , ctx , & cm -> counts . tx ) [ tx_size ] ;
 return ( TX_SIZE ) tx_size ;
 }