int vp9_rc_drop_frame ( VP9_COMP * cpi ) {
 const VP9EncoderConfig * oxcf = & cpi -> oxcf ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 if ( ! oxcf -> drop_frames_water_mark ) {
 return 0 ;
 }
 else {
 if ( rc -> buffer_level < 0 ) {
 return 1 ;
 }
 else {
 int drop_mark = ( int ) ( oxcf -> drop_frames_water_mark * rc -> optimal_buffer_level / 100 ) ;
 if ( ( rc -> buffer_level > drop_mark ) && ( rc -> decimation_factor > 0 ) ) {
 -- rc -> decimation_factor ;
 }
 else if ( rc -> buffer_level <= drop_mark && rc -> decimation_factor == 0 ) {
 rc -> decimation_factor = 1 ;
 }
 if ( rc -> decimation_factor > 0 ) {
 if ( rc -> decimation_count > 0 ) {
 -- rc -> decimation_count ;
 return 1 ;
 }
 else {
 rc -> decimation_count = rc -> decimation_factor ;
 return 0 ;
 }
 }
 else {
 rc -> decimation_count = 0 ;
 return 0 ;
 }
 }
 }
 }