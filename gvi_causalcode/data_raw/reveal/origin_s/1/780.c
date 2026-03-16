static int search_filter_level ( const YV12_BUFFER_CONFIG * sd , VP9_COMP * cpi , int partial_frame ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const struct loopfilter * const lf = & cm -> lf ;
 const int min_filter_level = 0 ;
 const int max_filter_level = get_max_filter_level ( cpi ) ;
 int filt_direction = 0 ;
 int best_err , filt_best ;
 int filt_mid = clamp ( lf -> filter_level , min_filter_level , max_filter_level ) ;
 int filter_step = filt_mid < 16 ? 4 : filt_mid / 4 ;
 int ss_err [ MAX_LOOP_FILTER + 1 ] ;
 vpx_memset ( ss_err , 0xFF , sizeof ( ss_err ) ) ;
 vpx_yv12_copy_y ( cm -> frame_to_show , & cpi -> last_frame_uf ) ;
 best_err = try_filter_frame ( sd , cpi , filt_mid , partial_frame ) ;
 filt_best = filt_mid ;
 ss_err [ filt_mid ] = best_err ;
 while ( filter_step > 0 ) {
 const int filt_high = MIN ( filt_mid + filter_step , max_filter_level ) ;
 const int filt_low = MAX ( filt_mid - filter_step , min_filter_level ) ;
 int filt_err ;
 int bias = ( best_err >> ( 15 - ( filt_mid / 8 ) ) ) * filter_step ;
 if ( ( cpi -> oxcf . pass == 2 ) && ( cpi -> twopass . section_intra_rating < 20 ) ) bias = ( bias * cpi -> twopass . section_intra_rating ) / 20 ;
 if ( cm -> tx_mode != ONLY_4X4 ) bias >>= 1 ;
 if ( filt_direction <= 0 && filt_low != filt_mid ) {
 if ( ss_err [ filt_low ] < 0 ) {
 filt_err = try_filter_frame ( sd , cpi , filt_low , partial_frame ) ;
 ss_err [ filt_low ] = filt_err ;
 }
 else {
 filt_err = ss_err [ filt_low ] ;
 }
 if ( ( filt_err - bias ) < best_err ) {
 if ( filt_err < best_err ) best_err = filt_err ;
 filt_best = filt_low ;
 }
 }
 if ( filt_direction >= 0 && filt_high != filt_mid ) {
 if ( ss_err [ filt_high ] < 0 ) {
 filt_err = try_filter_frame ( sd , cpi , filt_high , partial_frame ) ;
 ss_err [ filt_high ] = filt_err ;
 }
 else {
 filt_err = ss_err [ filt_high ] ;
 }
 if ( filt_err < ( best_err - bias ) ) {
 best_err = filt_err ;
 filt_best = filt_high ;
 }
 }
 if ( filt_best == filt_mid ) {
 filter_step /= 2 ;
 filt_direction = 0 ;
 }
 else {
 filt_direction = ( filt_best < filt_mid ) ? - 1 : 1 ;
 filt_mid = filt_best ;
 }
 }
 return filt_best ;
 }