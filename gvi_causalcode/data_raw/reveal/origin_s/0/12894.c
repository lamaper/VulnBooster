static void set_first_pass_params ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 if ( ! cpi -> refresh_alt_ref_frame && ( cm -> current_video_frame == 0 || ( cpi -> frame_flags & FRAMEFLAGS_KEY ) ) ) {
 cm -> frame_type = KEY_FRAME ;
 }
 else {
 cm -> frame_type = INTER_FRAME ;
 }
 cpi -> rc . frames_to_key = INT_MAX ;
 }