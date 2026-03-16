void vp9_idct32x32_add ( const int16_t * input , uint8_t * dest , int stride , int eob ) {
 if ( eob == 1 ) vp9_idct32x32_1_add ( input , dest , stride ) ;
 else if ( eob <= 34 ) vp9_idct32x32_34_add ( input , dest , stride ) ;
 else vp9_idct32x32_1024_add ( input , dest , stride ) ;
 }