void vp9_iwht4x4_16_add_c ( const int16_t * input , uint8_t * dest , int stride ) {
 int i ;
 int16_t output [ 16 ] ;
 int a1 , b1 , c1 , d1 , e1 ;
 const int16_t * ip = input ;
 int16_t * op = output ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 a1 = ip [ 0 ] >> UNIT_QUANT_SHIFT ;
 c1 = ip [ 1 ] >> UNIT_QUANT_SHIFT ;
 d1 = ip [ 2 ] >> UNIT_QUANT_SHIFT ;
 b1 = ip [ 3 ] >> UNIT_QUANT_SHIFT ;
 a1 += c1 ;
 d1 -= b1 ;
 e1 = ( a1 - d1 ) >> 1 ;
 b1 = e1 - b1 ;
 c1 = e1 - c1 ;
 a1 -= b1 ;
 d1 += c1 ;
 op [ 0 ] = a1 ;
 op [ 1 ] = b1 ;
 op [ 2 ] = c1 ;
 op [ 3 ] = d1 ;
 ip += 4 ;
 op += 4 ;
 }
 ip = output ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 a1 = ip [ 4 * 0 ] ;
 c1 = ip [ 4 * 1 ] ;
 d1 = ip [ 4 * 2 ] ;
 b1 = ip [ 4 * 3 ] ;
 a1 += c1 ;
 d1 -= b1 ;
 e1 = ( a1 - d1 ) >> 1 ;
 b1 = e1 - b1 ;
 c1 = e1 - c1 ;
 a1 -= b1 ;
 d1 += c1 ;
 dest [ stride * 0 ] = clip_pixel ( dest [ stride * 0 ] + a1 ) ;
 dest [ stride * 1 ] = clip_pixel ( dest [ stride * 1 ] + b1 ) ;
 dest [ stride * 2 ] = clip_pixel ( dest [ stride * 2 ] + c1 ) ;
 dest [ stride * 3 ] = clip_pixel ( dest [ stride * 3 ] + d1 ) ;
 ip ++ ;
 dest ++ ;
 }
 }