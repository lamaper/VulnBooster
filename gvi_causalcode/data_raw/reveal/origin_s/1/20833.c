void vp9_idct8x8_add ( const int16_t * input , uint8_t * dest , int stride , int eob ) {
 if ( eob == 1 ) vp9_idct8x8_1_add ( input , dest , stride ) ;
 else if ( eob <= 12 ) vp9_idct8x8_12_add ( input , dest , stride ) ;
 else vp9_idct8x8_64_add ( input , dest , stride ) ;
 }