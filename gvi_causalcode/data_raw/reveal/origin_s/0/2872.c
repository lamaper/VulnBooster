void vp9_iht16x16_256_add_sse2 ( const int16_t * input , uint8_t * dest , int stride , int tx_type ) {
 __m128i in0 [ 16 ] , in1 [ 16 ] ;
 load_buffer_8x16 ( input , in0 ) ;
 input += 8 ;
 load_buffer_8x16 ( input , in1 ) ;
 switch ( tx_type ) {
 case 0 : idct16_sse2 ( in0 , in1 ) ;
 idct16_sse2 ( in0 , in1 ) ;
 break ;
 case 1 : idct16_sse2 ( in0 , in1 ) ;
 iadst16_sse2 ( in0 , in1 ) ;
 break ;
 case 2 : iadst16_sse2 ( in0 , in1 ) ;
 idct16_sse2 ( in0 , in1 ) ;
 break ;
 case 3 : iadst16_sse2 ( in0 , in1 ) ;
 iadst16_sse2 ( in0 , in1 ) ;
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 write_buffer_8x16 ( dest , in0 , stride ) ;
 dest += 8 ;
 write_buffer_8x16 ( dest , in1 , stride ) ;
 }