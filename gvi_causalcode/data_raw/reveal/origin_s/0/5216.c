int vp9_rc_clamp_iframe_target_size ( const VP9_COMP * const cpi , int target ) {
 const RATE_CONTROL * rc = & cpi -> rc ;
 const VP9EncoderConfig * oxcf = & cpi -> oxcf ;
 if ( oxcf -> rc_max_intra_bitrate_pct ) {
 const int max_rate = rc -> avg_frame_bandwidth * oxcf -> rc_max_intra_bitrate_pct / 100 ;
 target = MIN ( target , max_rate ) ;
 }
 if ( target > rc -> max_frame_bandwidth ) target = rc -> max_frame_bandwidth ;
 return target ;
 }