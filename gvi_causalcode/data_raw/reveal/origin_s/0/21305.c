void vp9_iht4x4_add ( TX_TYPE tx_type , const tran_low_t * input , uint8_t * dest , int stride , int eob ) {
 if ( tx_type == DCT_DCT ) vp9_idct4x4_add ( input , dest , stride , eob ) ;
 else vp9_iht4x4_16_add ( input , dest , stride , tx_type ) ;
 }