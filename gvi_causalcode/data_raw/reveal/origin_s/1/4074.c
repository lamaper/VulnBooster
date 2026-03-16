void vp9_fdct4x4_1_c ( const int16_t * input , int16_t * output , int stride ) {
 int r , c ;
 int16_t sum = 0 ;
 for ( r = 0 ;
 r < 4 ;
 ++ r ) for ( c = 0 ;
 c < 4 ;
 ++ c ) sum += input [ r * stride + c ] ;
 output [ 0 ] = sum << 1 ;
 output [ 1 ] = 0 ;
 }