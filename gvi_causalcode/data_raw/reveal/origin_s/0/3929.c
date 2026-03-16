static void update_buffer_level ( VP9_COMP * cpi , int encoded_frame_size ) {
 const VP9_COMMON * const cm = & cpi -> common ;
 RATE_CONTROL * const rc = & cpi -> rc ;
 if ( ! cm -> show_frame ) {
 rc -> bits_off_target -= encoded_frame_size ;
 }
 else {
 rc -> bits_off_target += rc -> avg_frame_bandwidth - encoded_frame_size ;
 }
 rc -> bits_off_target = MIN ( rc -> bits_off_target , rc -> maximum_buffer_size ) ;
 rc -> buffer_level = rc -> bits_off_target ;
 if ( cpi -> use_svc && cpi -> oxcf . rc_mode == VPX_CBR ) {
 update_layer_buffer_level ( & cpi -> svc , encoded_frame_size ) ;
 }
 }