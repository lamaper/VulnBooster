int vp8_denoiser_filter_uv_c ( unsigned char * mc_running_avg_uv , int mc_avg_uv_stride , unsigned char * running_avg_uv , int avg_uv_stride , unsigned char * sig , int sig_stride , unsigned int motion_magnitude , int increase_denoising ) {
 unsigned char * running_avg_uv_start = running_avg_uv ;
 unsigned char * sig_start = sig ;
 int sum_diff_thresh ;
 int r , c ;
 int sum_diff = 0 ;
 int sum_block = 0 ;
 int adj_val [ 3 ] = {
 3 , 4 , 6 }
 ;
 int shift_inc1 = 0 ;
 int shift_inc2 = 1 ;
 if ( motion_magnitude <= MOTION_MAGNITUDE_THRESHOLD_UV ) {
 if ( increase_denoising ) {
 shift_inc1 = 1 ;
 shift_inc2 = 2 ;
 }
 adj_val [ 0 ] += shift_inc2 ;
 adj_val [ 1 ] += shift_inc2 ;
 adj_val [ 2 ] += shift_inc2 ;
 }
 for ( r = 0 ;
 r < 8 ;
 ++ r ) {
 for ( c = 0 ;
 c < 8 ;
 ++ c ) {
 sum_block += sig [ c ] ;
 }
 sig += sig_stride ;
 }
 if ( abs ( sum_block - ( 128 * 8 * 8 ) ) < SUM_DIFF_FROM_AVG_THRESH_UV ) {
 return COPY_BLOCK ;
 }
 sig -= sig_stride * 8 ;
 for ( r = 0 ;
 r < 8 ;
 ++ r ) {
 for ( c = 0 ;
 c < 8 ;
 ++ c ) {
 int diff = 0 ;
 int adjustment = 0 ;
 int absdiff = 0 ;
 diff = mc_running_avg_uv [ c ] - sig [ c ] ;
 absdiff = abs ( diff ) ;
 if ( absdiff <= 3 + shift_inc1 ) {
 running_avg_uv [ c ] = mc_running_avg_uv [ c ] ;
 sum_diff += diff ;
 }
 else {
 if ( absdiff >= 4 && absdiff <= 7 ) adjustment = adj_val [ 0 ] ;
 else if ( absdiff >= 8 && absdiff <= 15 ) adjustment = adj_val [ 1 ] ;
 else adjustment = adj_val [ 2 ] ;
 if ( diff > 0 ) {
 if ( ( sig [ c ] + adjustment ) > 255 ) running_avg_uv [ c ] = 255 ;
 else running_avg_uv [ c ] = sig [ c ] + adjustment ;
 sum_diff += adjustment ;
 }
 else {
 if ( ( sig [ c ] - adjustment ) < 0 ) running_avg_uv [ c ] = 0 ;
 else running_avg_uv [ c ] = sig [ c ] - adjustment ;
 sum_diff -= adjustment ;
 }
 }
 }
 sig += sig_stride ;
 mc_running_avg_uv += mc_avg_uv_stride ;
 running_avg_uv += avg_uv_stride ;
 }
 sum_diff_thresh = SUM_DIFF_THRESHOLD_UV ;
 if ( increase_denoising ) sum_diff_thresh = SUM_DIFF_THRESHOLD_HIGH_UV ;
 if ( abs ( sum_diff ) > sum_diff_thresh ) {
 int delta = ( ( abs ( sum_diff ) - sum_diff_thresh ) >> 8 ) + 1 ;
 if ( delta < 4 ) {
 sig -= sig_stride * 8 ;
 mc_running_avg_uv -= mc_avg_uv_stride * 8 ;
 running_avg_uv -= avg_uv_stride * 8 ;
 for ( r = 0 ;
 r < 8 ;
 ++ r ) {
 for ( c = 0 ;
 c < 8 ;
 ++ c ) {
 int diff = mc_running_avg_uv [ c ] - sig [ c ] ;
 int adjustment = abs ( diff ) ;
 if ( adjustment > delta ) adjustment = delta ;
 if ( diff > 0 ) {
 if ( running_avg_uv [ c ] - adjustment < 0 ) running_avg_uv [ c ] = 0 ;
 else running_avg_uv [ c ] = running_avg_uv [ c ] - adjustment ;
 sum_diff -= adjustment ;
 }
 else if ( diff < 0 ) {
 if ( running_avg_uv [ c ] + adjustment > 255 ) running_avg_uv [ c ] = 255 ;
 else running_avg_uv [ c ] = running_avg_uv [ c ] + adjustment ;
 sum_diff += adjustment ;
 }
 }
 sig += sig_stride ;
 mc_running_avg_uv += mc_avg_uv_stride ;
 running_avg_uv += avg_uv_stride ;
 }
 if ( abs ( sum_diff ) > sum_diff_thresh ) return COPY_BLOCK ;
 }
 else {
 return COPY_BLOCK ;
 }
 }
 vp8_copy_mem8x8 ( running_avg_uv_start , avg_uv_stride , sig_start , sig_stride ) ;
 return FILTER_BLOCK ;
 }