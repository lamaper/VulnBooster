int vp8_denoiser_filter_c ( unsigned char * mc_running_avg_y , int mc_avg_y_stride , unsigned char * running_avg_y , int avg_y_stride , unsigned char * sig , int sig_stride , unsigned int motion_magnitude , int increase_denoising ) {
 unsigned char * running_avg_y_start = running_avg_y ;
 unsigned char * sig_start = sig ;
 int sum_diff_thresh ;
 int r , c ;
 int sum_diff = 0 ;
 int adj_val [ 3 ] = {
 3 , 4 , 6 }
 ;
 int shift_inc1 = 0 ;
 int shift_inc2 = 1 ;
 if ( motion_magnitude <= MOTION_MAGNITUDE_THRESHOLD ) {
 if ( increase_denoising ) {
 shift_inc1 = 1 ;
 shift_inc2 = 2 ;
 }
 adj_val [ 0 ] += shift_inc2 ;
 adj_val [ 1 ] += shift_inc2 ;
 adj_val [ 2 ] += shift_inc2 ;
 }
 for ( r = 0 ;
 r < 16 ;
 ++ r ) {
 for ( c = 0 ;
 c < 16 ;
 ++ c ) {
 int diff = 0 ;
 int adjustment = 0 ;
 int absdiff = 0 ;
 diff = mc_running_avg_y [ c ] - sig [ c ] ;
 absdiff = abs ( diff ) ;
 if ( absdiff <= 3 + shift_inc1 ) {
 running_avg_y [ c ] = mc_running_avg_y [ c ] ;
 sum_diff += diff ;
 }
 else {
 if ( absdiff >= 4 && absdiff <= 7 ) adjustment = adj_val [ 0 ] ;
 else if ( absdiff >= 8 && absdiff <= 15 ) adjustment = adj_val [ 1 ] ;
 else adjustment = adj_val [ 2 ] ;
 if ( diff > 0 ) {
 if ( ( sig [ c ] + adjustment ) > 255 ) running_avg_y [ c ] = 255 ;
 else running_avg_y [ c ] = sig [ c ] + adjustment ;
 sum_diff += adjustment ;
 }
 else {
 if ( ( sig [ c ] - adjustment ) < 0 ) running_avg_y [ c ] = 0 ;
 else running_avg_y [ c ] = sig [ c ] - adjustment ;
 sum_diff -= adjustment ;
 }
 }
 }
 sig += sig_stride ;
 mc_running_avg_y += mc_avg_y_stride ;
 running_avg_y += avg_y_stride ;
 }
 sum_diff_thresh = SUM_DIFF_THRESHOLD ;
 if ( increase_denoising ) sum_diff_thresh = SUM_DIFF_THRESHOLD_HIGH ;
 if ( abs ( sum_diff ) > sum_diff_thresh ) {
 int delta = ( ( abs ( sum_diff ) - sum_diff_thresh ) >> 8 ) + 1 ;
 if ( delta < 4 ) {
 sig -= sig_stride * 16 ;
 mc_running_avg_y -= mc_avg_y_stride * 16 ;
 running_avg_y -= avg_y_stride * 16 ;
 for ( r = 0 ;
 r < 16 ;
 ++ r ) {
 for ( c = 0 ;
 c < 16 ;
 ++ c ) {
 int diff = mc_running_avg_y [ c ] - sig [ c ] ;
 int adjustment = abs ( diff ) ;
 if ( adjustment > delta ) adjustment = delta ;
 if ( diff > 0 ) {
 if ( running_avg_y [ c ] - adjustment < 0 ) running_avg_y [ c ] = 0 ;
 else running_avg_y [ c ] = running_avg_y [ c ] - adjustment ;
 sum_diff -= adjustment ;
 }
 else if ( diff < 0 ) {
 if ( running_avg_y [ c ] + adjustment > 255 ) running_avg_y [ c ] = 255 ;
 else running_avg_y [ c ] = running_avg_y [ c ] + adjustment ;
 sum_diff += adjustment ;
 }
 }
 sig += sig_stride ;
 mc_running_avg_y += mc_avg_y_stride ;
 running_avg_y += avg_y_stride ;
 }
 if ( abs ( sum_diff ) > sum_diff_thresh ) return COPY_BLOCK ;
 }
 else {
 return COPY_BLOCK ;
 }
 }
 vp8_copy_mem16x16 ( running_avg_y_start , avg_y_stride , sig_start , sig_stride ) ;
 return FILTER_BLOCK ;
 }