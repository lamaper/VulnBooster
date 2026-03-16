void vp9_iht16x16_add ( TX_TYPE tx_type , const tran_low_t * input , uint8_t * dest , int stride , int eob ) {
 if ( tx_type == DCT_DCT ) {
 vp9_idct16x16_add ( input , dest , stride , eob ) ;
 }
 else {
 vp9_iht16x16_256_add ( input , dest , stride , tx_type ) ;
 }
 }