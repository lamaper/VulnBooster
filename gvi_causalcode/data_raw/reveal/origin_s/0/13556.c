static void filter_selectively_horiz ( uint8_t * s , int pitch , unsigned int mask_16x16 , unsigned int mask_8x8 , unsigned int mask_4x4 , unsigned int mask_4x4_int , const loop_filter_info_n * lfi_n , const uint8_t * lfl ) {
 unsigned int mask ;
 int count ;
 for ( mask = mask_16x16 | mask_8x8 | mask_4x4 | mask_4x4_int ;
 mask ;
 mask >>= count ) {
 const loop_filter_thresh * lfi = lfi_n -> lfthr + * lfl ;
 count = 1 ;
 if ( mask & 1 ) {
 if ( mask_16x16 & 1 ) {
 if ( ( mask_16x16 & 3 ) == 3 ) {
 vp9_lpf_horizontal_16 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 2 ) ;
 count = 2 ;
 }
 else {
 vp9_lpf_horizontal_16 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 }
 else if ( mask_8x8 & 1 ) {
 if ( ( mask_8x8 & 3 ) == 3 ) {
 const loop_filter_thresh * lfin = lfi_n -> lfthr + * ( lfl + 1 ) ;
 vp9_lpf_horizontal_8_dual ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , lfin -> mblim , lfin -> lim , lfin -> hev_thr ) ;
 if ( ( mask_4x4_int & 3 ) == 3 ) {
 vp9_lpf_horizontal_4_dual ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , lfin -> mblim , lfin -> lim , lfin -> hev_thr ) ;
 }
 else {
 if ( mask_4x4_int & 1 ) vp9_lpf_horizontal_4 ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 else if ( mask_4x4_int & 2 ) vp9_lpf_horizontal_4 ( s + 8 + 4 * pitch , pitch , lfin -> mblim , lfin -> lim , lfin -> hev_thr , 1 ) ;
 }
 count = 2 ;
 }
 else {
 vp9_lpf_horizontal_8 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 if ( mask_4x4_int & 1 ) vp9_lpf_horizontal_4 ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 }
 else if ( mask_4x4 & 1 ) {
 if ( ( mask_4x4 & 3 ) == 3 ) {
 const loop_filter_thresh * lfin = lfi_n -> lfthr + * ( lfl + 1 ) ;
 vp9_lpf_horizontal_4_dual ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , lfin -> mblim , lfin -> lim , lfin -> hev_thr ) ;
 if ( ( mask_4x4_int & 3 ) == 3 ) {
 vp9_lpf_horizontal_4_dual ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , lfin -> mblim , lfin -> lim , lfin -> hev_thr ) ;
 }
 else {
 if ( mask_4x4_int & 1 ) vp9_lpf_horizontal_4 ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 else if ( mask_4x4_int & 2 ) vp9_lpf_horizontal_4 ( s + 8 + 4 * pitch , pitch , lfin -> mblim , lfin -> lim , lfin -> hev_thr , 1 ) ;
 }
 count = 2 ;
 }
 else {
 vp9_lpf_horizontal_4 ( s , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 if ( mask_4x4_int & 1 ) vp9_lpf_horizontal_4 ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 }
 else if ( mask_4x4_int & 1 ) {
 vp9_lpf_horizontal_4 ( s + 4 * pitch , pitch , lfi -> mblim , lfi -> lim , lfi -> hev_thr , 1 ) ;
 }
 }
 s += 8 * count ;
 lfl += count ;
 mask_16x16 >>= count ;
 mask_8x8 >>= count ;
 mask_4x4 >>= count ;
 mask_4x4_int >>= count ;
 }
 }