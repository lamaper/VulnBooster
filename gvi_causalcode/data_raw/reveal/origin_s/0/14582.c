static TX_MODE read_tx_mode ( vp9_reader * r ) {
 TX_MODE tx_mode = vp9_read_literal ( r , 2 ) ;
 if ( tx_mode == ALLOW_32X32 ) tx_mode += vp9_read_bit ( r ) ;
 return tx_mode ;
 }