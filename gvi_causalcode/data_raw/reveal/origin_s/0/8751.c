void vbr_rate_correction ( int * this_frame_target , const int64_t vbr_bits_off_target ) {
 int max_delta = ( * this_frame_target * 15 ) / 100 ;
 if ( vbr_bits_off_target > 0 ) {
 * this_frame_target += ( vbr_bits_off_target > max_delta ) ? max_delta : ( int ) vbr_bits_off_target ;
 }
 else {
 * this_frame_target -= ( vbr_bits_off_target < - max_delta ) ? max_delta : ( int ) - vbr_bits_off_target ;
 }
 }