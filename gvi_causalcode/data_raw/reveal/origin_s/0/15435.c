static int calc_iframe_target_size_one_pass_vbr ( const VP9_COMP * const cpi ) {
 static const int kf_ratio = 25 ;
 const RATE_CONTROL * rc = & cpi -> rc ;
 const int target = rc -> avg_frame_bandwidth * kf_ratio ;
 return vp9_rc_clamp_iframe_target_size ( cpi , target ) ;
 }