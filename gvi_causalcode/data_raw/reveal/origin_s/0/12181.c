void vp9_rc_postencode_update_drop_frame ( VP9_COMP * cpi ) {
 update_buffer_level ( cpi , 0 ) ;
 cpi -> common . last_frame_type = cpi -> common . frame_type ;
 cpi -> rc . frames_since_key ++ ;
 cpi -> rc . frames_to_key -- ;
 }