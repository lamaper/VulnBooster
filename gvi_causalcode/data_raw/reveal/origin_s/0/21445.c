void vp9_idct4x4_add ( const tran_low_t * input , uint8_t * dest , int stride , int eob ) {
 if ( eob > 1 ) vp9_idct4x4_16_add ( input , dest , stride ) ;
 else vp9_idct4x4_1_add ( input , dest , stride ) ;
 }