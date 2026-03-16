static void filter_selectively_vert_row2 ( PLANE_TYPE plane_type , uint8_t * s , int pitch , unsigned int mask_16x16_l , unsigned int mask_8x8_l , unsigned int mask_4x4_l , unsigned int mask_4x4_int_l , const loop_filter_info_n * lfi_n , const uint8_t * lfl ) {
 const int mask_shift = plane_type ? 4 : 8 ;
 const int mask_cutoff = plane_type ? 0xf : 0xff ;
 const int lfl_forward = plane_type ? 4 : 8 ;
 unsigned int mask_16x16_0 = mask_16x16_l & mask_cutoff ;
 unsigned int mask_8x8_0 = mask_8x8_l & mask_cutoff ;
 unsigned int mask_4x4_0 = mask_4x4_l & mask_cutoff ;
 unsigned int mask_4x4_int_0 = mask_4x4_int_l & mask_cutoff ;
 unsigned int mask_16x16_1 = ( mask_16x16_l >> mask_shift ) & mask_cutoff ;
 unsigned int mask_8x8_1 = ( mask_8x8_l >> mask_shift ) & mask_cutoff ;
 unsigned int mask_4x4_1 = ( mask_4x4_l >> mask_shift ) & mask_cutoff ;
 unsigned int mask_4x4_int_1 = ( mask_4x4_int_l >> mask_shift ) & mask_cutoff ;
 unsigned int mask ;
 for ( mask = mask_16x16_0 | mask_8x8_0 | mask_4x4_0 | mask_4x4_int_0 | mask_16x16_1 | mask_8x8_1 | mask_4x4_1 | mask_4x4_int_1 ;
 mask ;
 mask >>= 1 ) {
 const loop_filter_thresh * lfi0 = lfi_n -> lfthr + * lfl ;
 const loop_filter_thresh * lfi1 = lfi_n -> lfthr + * ( lfl + lfl_forward ) ;
 if ( mask & 1 ) {
 if ( ( mask_16x16_0 | mask_16x16_1 ) & 1 ) {
 if ( ( mask_16x16_0 & mask_16x16_1 ) & 1 ) {
 vp9_lpf_vertical_16_dual ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr ) ;
 }
 else if ( mask_16x16_0 & 1 ) {
 vp9_lpf_vertical_16 ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr ) ;
 }
 else {
 vp9_lpf_vertical_16 ( s + 8 * pitch , pitch , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr ) ;
 }
 }
 if ( ( mask_8x8_0 | mask_8x8_1 ) & 1 ) {
 if ( ( mask_8x8_0 & mask_8x8_1 ) & 1 ) {
 vp9_lpf_vertical_8_dual ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr ) ;
 }
 else if ( mask_8x8_0 & 1 ) {
 vp9_lpf_vertical_8 ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , 1 ) ;
 }
 else {
 vp9_lpf_vertical_8 ( s + 8 * pitch , pitch , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr , 1 ) ;
 }
 }
 if ( ( mask_4x4_0 | mask_4x4_1 ) & 1 ) {
 if ( ( mask_4x4_0 & mask_4x4_1 ) & 1 ) {
 vp9_lpf_vertical_4_dual ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr ) ;
 }
 else if ( mask_4x4_0 & 1 ) {
 vp9_lpf_vertical_4 ( s , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , 1 ) ;
 }
 else {
 vp9_lpf_vertical_4 ( s + 8 * pitch , pitch , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr , 1 ) ;
 }
 }
 if ( ( mask_4x4_int_0 | mask_4x4_int_1 ) & 1 ) {
 if ( ( mask_4x4_int_0 & mask_4x4_int_1 ) & 1 ) {
 vp9_lpf_vertical_4_dual ( s + 4 , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr ) ;
 }
 else if ( mask_4x4_int_0 & 1 ) {
 vp9_lpf_vertical_4 ( s + 4 , pitch , lfi0 -> mblim , lfi0 -> lim , lfi0 -> hev_thr , 1 ) ;
 }
 else {
 vp9_lpf_vertical_4 ( s + 8 * pitch + 4 , pitch , lfi1 -> mblim , lfi1 -> lim , lfi1 -> hev_thr , 1 ) ;
 }
 }
 }
 s += 8 ;
 lfl += 1 ;
 mask_16x16_0 >>= 1 ;
 mask_8x8_0 >>= 1 ;
 mask_4x4_0 >>= 1 ;
 mask_4x4_int_0 >>= 1 ;
 mask_16x16_1 >>= 1 ;
 mask_8x8_1 >>= 1 ;
 mask_4x4_1 >>= 1 ;
 mask_4x4_int_1 >>= 1 ;
 }
 }