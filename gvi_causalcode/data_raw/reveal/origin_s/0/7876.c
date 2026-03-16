static void filter_selectively_vert ( uint8_t * s , int pitch , unsigned int mask_16x16 , unsigned int mask_8x8 , unsigned int mask_4x4 , unsigned int mask_4x4_int , const loop_filter_info_n * lfi_n , const uint8_t * lfl ) {
 unsigned int mask ;
 for ( mask = mask_16x16 | mask_8x8 | mask_4x4 | mask_4x4_int ;
 mask ;
 mask >>= 1 ) {
 const loop_filter_thresh * lfi = lfi_n -> lfthr + * lfl ;
 if ( mask & 1 ) {
 if ( mask_16x16 & 1 ) {
 vp9_lpf_vertical_16 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr ) ;
 }
 else if ( mask_8x8 & 1 ) {
 vp9_lpf_vertical_8 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 else if ( mask_4x4 & 1 ) {
 vp9_lpf_vertical_4 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 }
 if ( mask_4x4_int & 1 ) vp9_lpf_vertical_4 ( s + 4 , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 s += 8 ;
 lfl += 1 ;
 mask_16x16 >>= 1 ;
 mask_8x8 >>= 1 ;
 mask_4x4 >>= 1 ;
 mask_4x4_int >>= 1 ;
 }
 }