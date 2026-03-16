static int calc_pframe_target_size_one_pass_cbr ( const VP9_COMP * cpi ) {
 const VP9EncoderConfig * oxcf = & cpi -> oxcf ;
 const RATE_CONTROL * rc = & cpi -> rc ;
 const SVC * const svc = & cpi -> svc ;
 const int64_t diff = rc -> optimal_buffer_level - rc -> buffer_level ;
 const int64_t one_pct_bits = 1 + rc -> optimal_buffer_level / 100 ;
 int min_frame_target = MAX ( rc -> avg_frame_bandwidth >> 4 , FRAME_OVERHEAD_BITS ) ;
 int target = rc -> avg_frame_bandwidth ;
 if ( svc -> number_temporal_layers > 1 && oxcf -> rc_mode == VPX_CBR ) {
 int current_temporal_layer = svc -> temporal_layer_id ;
 const LAYER_CONTEXT * lc = & svc -> layer_context [ current_temporal_layer ] ;
 target = lc -> avg_frame_size ;
 min_frame_target = MAX ( lc -> avg_frame_size >> 4 , FRAME_OVERHEAD_BITS ) ;
 }
 if ( diff > 0 ) {
 const int pct_low = ( int ) MIN ( diff / one_pct_bits , oxcf -> under_shoot_pct ) ;
 target -= ( target * pct_low ) / 200 ;
 }
 else if ( diff < 0 ) {
 const int pct_high = ( int ) MIN ( - diff / one_pct_bits , oxcf -> over_shoot_pct ) ;
 target += ( target * pct_high ) / 200 ;
 }
 return MAX ( min_frame_target , target ) ;
 }