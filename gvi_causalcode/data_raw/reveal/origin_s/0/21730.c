void vp9_iwht4x4_1_add_c ( const tran_low_t * in , uint8_t * dest , int dest_stride ) {
 int i ;
 tran_high_t a1 , e1 ;
 tran_low_t tmp [ 4 ] ;
 const tran_low_t * ip = in ;
 tran_low_t * op = tmp ;
 a1 = ip [ 0 ] >> UNIT_QUANT_SHIFT ;
 e1 = a1 >> 1 ;
 a1 -= e1 ;
 op [ 0 ] = a1 ;
 op [ 1 ] = op [ 2 ] = op [ 3 ] = e1 ;
 ip = tmp ;
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 e1 = ip [ 0 ] >> 1 ;
 a1 = ip [ 0 ] - e1 ;
 dest [ dest_stride * 0 ] = clip_pixel ( dest [ dest_stride * 0 ] + a1 ) ;
 dest [ dest_stride * 1 ] = clip_pixel ( dest [ dest_stride * 1 ] + e1 ) ;
 dest [ dest_stride * 2 ] = clip_pixel ( dest [ dest_stride * 2 ] + e1 ) ;
 dest [ dest_stride * 3 ] = clip_pixel ( dest [ dest_stride * 3 ] + e1 ) ;
 ip ++ ;
 dest ++ ;
 }
 }