void vp9_idct4x4_1_add_c ( const int16_t * input , uint8_t * dest , int dest_stride ) {
 int i ;
 int a1 ;
 int16_t out = dct_const_round_shift ( input [ 0 ] * cospi_16_64 ) ;
 out = dct_const_round_shift ( out * cospi_16_64 ) ;
 a1 = ROUND_POWER_OF_TWO ( out , 4 ) ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 dest [ 0 ] = clip_pixel ( dest [ 0 ] + a1 ) ;
 dest [ 1 ] = clip_pixel ( dest [ 1 ] + a1 ) ;
 dest [ 2 ] = clip_pixel ( dest [ 2 ] + a1 ) ;
 dest [ 3 ] = clip_pixel ( dest [ 3 ] + a1 ) ;
 dest += dest_stride ;
 }
 }