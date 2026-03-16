void vp9_idct16x16_add ( const tran_low_t * input , uint8_t * dest , int stride , int eob ) {
 if ( eob == 1 ) vp9_idct16x16_1_add ( input , dest , stride ) ;
 else if ( eob <= 10 ) vp9_idct16x16_10_add ( input , dest , stride ) ;
 else vp9_idct16x16_256_add ( input , dest , stride ) ;
 }