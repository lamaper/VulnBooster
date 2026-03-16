static int calc_iframe_target_size_one_pass_cbr ( const VP9_COMP * cpi ) {
 const RATE_CONTROL * rc = & cpi -> rc ;
 const VP9EncoderConfig * oxcf = & cpi -> oxcf ;
 const SVC * const svc = & cpi -> svc ;
 int target ;
 if ( cpi -> common . current_video_frame == 0 ) {
 target = ( ( rc -> starting_buffer_level / 2 ) > INT_MAX ) ? INT_MAX : ( int ) ( rc -> starting_buffer_level / 2 ) ;
 }
 else {
 int kf_boost = 32 ;
 double framerate = cpi -> framerate ;
 if ( svc -> number_temporal_layers > 1 && oxcf -> rc_mode == VPX_CBR ) {
 const LAYER_CONTEXT * lc = & svc -> layer_context [ svc -> temporal_layer_id ] ;
 framerate = lc -> framerate ;
 }
 kf_boost = MAX ( kf_boost , ( int ) ( 2 * framerate - 16 ) ) ;
 if ( rc -> frames_since_key < framerate / 2 ) {
 kf_boost = ( int ) ( kf_boost * rc -> frames_since_key / ( framerate / 2 ) ) ;
 }
 target = ( ( 16 + kf_boost ) * rc -> avg_frame_bandwidth ) >> 4 ;
 }
 return vp9_rc_clamp_iframe_target_size ( cpi , target ) ;
 }