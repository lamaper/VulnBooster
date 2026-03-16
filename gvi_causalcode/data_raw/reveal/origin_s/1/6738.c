void vp9_fwht4x4_c ( const int16_t * input , int16_t * output , int stride ) {
 int i ;
 int a1 , b1 , c1 , d1 , e1 ;
 const int16_t * ip = input ;
 int16_t * op = output ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 a1 = ip [ 0 * stride ] ;
 b1 = ip [ 1 * stride ] ;
 c1 = ip [ 2 * stride ] ;
 d1 = ip [ 3 * stride ] ;
 a1 += b1 ;
 d1 = d1 - c1 ;
 e1 = ( a1 - d1 ) >> 1 ;
 b1 = e1 - b1 ;
 c1 = e1 - c1 ;
 a1 -= c1 ;
 d1 += b1 ;
 op [ 0 ] = a1 ;
 op [ 4 ] = c1 ;
 op [ 8 ] = d1 ;
 op [ 12 ] = b1 ;
 ip ++ ;
 op ++ ;
 }
 ip = output ;
 op = output ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 a1 = ip [ 0 ] ;
 b1 = ip [ 1 ] ;
 c1 = ip [ 2 ] ;
 d1 = ip [ 3 ] ;
 a1 += b1 ;
 d1 -= c1 ;
 e1 = ( a1 - d1 ) >> 1 ;
 b1 = e1 - b1 ;
 c1 = e1 - c1 ;
 a1 -= c1 ;
 d1 += b1 ;
 op [ 0 ] = a1 * UNIT_QUANT_FACTOR ;
 op [ 1 ] = c1 * UNIT_QUANT_FACTOR ;
 op [ 2 ] = d1 * UNIT_QUANT_FACTOR ;
 op [ 3 ] = b1 * UNIT_QUANT_FACTOR ;
 ip += 4 ;
 op += 4 ;
 }
 }