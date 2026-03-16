static int calc_active_worst_quality_one_pass_cbr ( const VP9_COMP * cpi ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 const RATE_CONTROL * rc = & cpi -> rc ;
 int64_t critical_level = rc -> optimal_buffer_level >> 2 ;
 int64_t buff_lvl_step = 0 ;
 int adjustment = 0 ;
 int active_worst_quality ;
 if ( cm -> frame_type == KEY_FRAME ) return rc -> worst_quality ;
 if ( cm -> current_video_frame > 1 ) active_worst_quality = MIN ( rc -> worst_quality , rc -> avg_frame_qindex [ INTER_FRAME ] * 5 / 4 ) ;
 else active_worst_quality = MIN ( rc -> worst_quality , rc -> avg_frame_qindex [ KEY_FRAME ] * 3 / 2 ) ;
 if ( rc -> buffer_level > rc -> optimal_buffer_level ) {
 int max_adjustment_down = active_worst_quality / 3 ;
 if ( max_adjustment_down ) {
 buff_lvl_step = ( ( rc -> maximum_buffer_size - rc -> optimal_buffer_level ) / max_adjustment_down ) ;
 if ( buff_lvl_step ) adjustment = ( int ) ( ( rc -> buffer_level - rc -> optimal_buffer_level ) / buff_lvl_step ) ;
 active_worst_quality -= adjustment ;
 }
 }
 else if ( rc -> buffer_level > critical_level ) {
 if ( critical_level ) {
 buff_lvl_step = ( rc -> optimal_buffer_level - critical_level ) ;
 if ( buff_lvl_step ) {
 adjustment = ( int ) ( ( rc -> worst_quality - rc -> avg_frame_qindex [ INTER_FRAME ] ) * ( rc -> optimal_buffer_level - rc -> buffer_level ) / buff_lvl_step ) ;
 }
 active_worst_quality = rc -> avg_frame_qindex [ INTER_FRAME ] + adjustment ;
 }
 }
 else {
 active_worst_quality = rc -> worst_quality ;
 }
 return active_worst_quality ;
 }