void vp9_rc_set_gf_max_interval ( const VP9_COMP * const cpi , RATE_CONTROL * const rc ) {
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 rc -> max_gf_interval = 16 ;
 rc -> static_scene_max_gf_interval = oxcf -> key_freq >> 1 ;
 if ( rc -> static_scene_max_gf_interval > ( MAX_LAG_BUFFERS * 2 ) ) rc -> static_scene_max_gf_interval = MAX_LAG_BUFFERS * 2 ;
 if ( is_altref_enabled ( cpi ) ) {
 if ( rc -> static_scene_max_gf_interval > oxcf -> lag_in_frames - 1 ) rc -> static_scene_max_gf_interval = oxcf -> lag_in_frames - 1 ;
 }
 if ( rc -> max_gf_interval > rc -> static_scene_max_gf_interval ) rc -> max_gf_interval = rc -> static_scene_max_gf_interval ;
 }