static VP9_DENOISER_DECISION denoiser_filter ( const uint8_t * sig , int sig_stride , const uint8_t * mc_avg , int mc_avg_stride , uint8_t * avg , int avg_stride , int increase_denoising , BLOCK_SIZE bs , int motion_magnitude ) {
 int r , c ;
 const uint8_t * sig_start = sig ;
 const uint8_t * mc_avg_start = mc_avg ;
 uint8_t * avg_start = avg ;
 int diff , adj , absdiff , delta ;
 int adj_val [ ] = {
 3 , 4 , 6 }
 ;
 int total_adj = 0 ;
 int shift_inc = 1 ;
 if ( motion_magnitude <= MOTION_MAGNITUDE_THRESHOLD ) {
 if ( increase_denoising ) {
 shift_inc = 2 ;
 }
 adj_val [ 0 ] += shift_inc ;
 adj_val [ 1 ] += shift_inc ;
 adj_val [ 2 ] += shift_inc ;
 }
 for ( r = 0 ;
 r < heights [ bs ] ;
 ++ r ) {
 for ( c = 0 ;
 c < widths [ bs ] ;
 ++ c ) {
 diff = mc_avg [ c ] - sig [ c ] ;
 absdiff = abs ( diff ) ;
 if ( absdiff <= absdiff_thresh ( bs , increase_denoising ) ) {
 avg [ c ] = mc_avg [ c ] ;
 total_adj += diff ;
 }
 else {
 switch ( absdiff ) {
 case 4 : case 5 : case 6 : case 7 : adj = adj_val [ 0 ] ;
 break ;
 case 8 : case 9 : case 10 : case 11 : case 12 : case 13 : case 14 : case 15 : adj = adj_val [ 1 ] ;
 break ;
 default : adj = adj_val [ 2 ] ;
 }
 if ( diff > 0 ) {
 avg [ c ] = MIN ( UINT8_MAX , sig [ c ] + adj ) ;
 total_adj += adj ;
 }
 else {
 avg [ c ] = MAX ( 0 , sig [ c ] - adj ) ;
 total_adj -= adj ;
 }
 }
 }
 sig += sig_stride ;
 avg += avg_stride ;
 mc_avg += mc_avg_stride ;
 }
 if ( abs ( total_adj ) <= total_adj_strong_thresh ( bs , increase_denoising ) ) {
 return FILTER_BLOCK ;
 }
 delta = ( ( abs ( total_adj ) - total_adj_strong_thresh ( bs , increase_denoising ) ) >> 8 ) + 1 ;
 if ( delta >= delta_thresh ( bs , increase_denoising ) ) {
 return COPY_BLOCK ;
 }
 mc_avg = mc_avg_start ;
 avg = avg_start ;
 sig = sig_start ;
 for ( r = 0 ;
 r < heights [ bs ] ;
 ++ r ) {
 for ( c = 0 ;
 c < widths [ bs ] ;
 ++ c ) {
 diff = mc_avg [ c ] - sig [ c ] ;
 adj = abs ( diff ) ;
 if ( adj > delta ) {
 adj = delta ;
 }
 if ( diff > 0 ) {
 avg [ c ] = MAX ( 0 , avg [ c ] - adj ) ;
 total_adj -= adj ;
 }
 else {
 avg [ c ] = MIN ( UINT8_MAX , avg [ c ] + adj ) ;
 total_adj += adj ;
 }
 }
 sig += sig_stride ;
 avg += avg_stride ;
 mc_avg += mc_avg_stride ;
 }
 if ( abs ( total_adj ) <= total_adj_weak_thresh ( bs , increase_denoising ) ) {
 return FILTER_BLOCK ;
 }
 return COPY_BLOCK ;
 }