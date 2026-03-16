static int calc_arf_boost ( VP9_COMP * cpi , int offset , int f_frames , int b_frames , int * f_boost , int * b_boost ) {
 TWO_PASS * const twopass = & cpi -> twopass ;
 int i ;
 double boost_score = 0.0 ;
 double mv_ratio_accumulator = 0.0 ;
 double decay_accumulator = 1.0 ;
 double this_frame_mv_in_out = 0.0 ;
 double mv_in_out_accumulator = 0.0 ;
 double abs_mv_in_out_accumulator = 0.0 ;
 int arf_boost ;
 int flash_detected = 0 ;
 for ( i = 0 ;
 i < f_frames ;
 ++ i ) {
 const FIRSTPASS_STATS * this_frame = read_frame_stats ( twopass , i + offset ) ;
 if ( this_frame == NULL ) break ;
 accumulate_frame_motion_stats ( this_frame , & this_frame_mv_in_out , & mv_in_out_accumulator , & abs_mv_in_out_accumulator , & mv_ratio_accumulator ) ;
 flash_detected = detect_flash ( twopass , i + offset ) || detect_flash ( twopass , i + offset + 1 ) ;
 if ( ! flash_detected ) {
 decay_accumulator *= get_prediction_decay_rate ( & cpi -> common , this_frame ) ;
 decay_accumulator = decay_accumulator < MIN_DECAY_FACTOR ? MIN_DECAY_FACTOR : decay_accumulator ;
 }
 boost_score += decay_accumulator * calc_frame_boost ( twopass , this_frame , this_frame_mv_in_out ) ;
 }
 * f_boost = ( int ) boost_score ;
 boost_score = 0.0 ;
 mv_ratio_accumulator = 0.0 ;
 decay_accumulator = 1.0 ;
 this_frame_mv_in_out = 0.0 ;
 mv_in_out_accumulator = 0.0 ;
 abs_mv_in_out_accumulator = 0.0 ;
 for ( i = - 1 ;
 i >= - b_frames ;
 -- i ) {
 const FIRSTPASS_STATS * this_frame = read_frame_stats ( twopass , i + offset ) ;
 if ( this_frame == NULL ) break ;
 accumulate_frame_motion_stats ( this_frame , & this_frame_mv_in_out , & mv_in_out_accumulator , & abs_mv_in_out_accumulator , & mv_ratio_accumulator ) ;
 flash_detected = detect_flash ( twopass , i + offset ) || detect_flash ( twopass , i + offset + 1 ) ;
 if ( ! flash_detected ) {
 decay_accumulator *= get_prediction_decay_rate ( & cpi -> common , this_frame ) ;
 decay_accumulator = decay_accumulator < MIN_DECAY_FACTOR ? MIN_DECAY_FACTOR : decay_accumulator ;
 }
 boost_score += decay_accumulator * calc_frame_boost ( twopass , this_frame , this_frame_mv_in_out ) ;
 }
 * b_boost = ( int ) boost_score ;
 arf_boost = ( * f_boost + * b_boost ) ;
 if ( arf_boost < ( ( b_frames + f_frames ) * 20 ) ) arf_boost = ( ( b_frames + f_frames ) * 20 ) ;
 return arf_boost ;
 }