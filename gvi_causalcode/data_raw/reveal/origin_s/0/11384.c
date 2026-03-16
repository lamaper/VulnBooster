void vp9_update_layer_context_change_config ( VP9_COMP * const cpi , const int target_bandwidth ) {
 SVC * const svc = & cpi -> svc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 const RATE_CONTROL * const rc = & cpi -> rc ;
 int layer ;
 int layer_end ;
 float bitrate_alloc = 1.0 ;
 if ( svc -> number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) {
 layer_end = svc -> number_temporal_layers ;
 }
 else {
 layer_end = svc -> number_spatial_layers ;
 }
 for ( layer = 0 ;
 layer < layer_end ;
 ++ layer ) {
 LAYER_CONTEXT * const lc = & svc -> layer_context [ layer ] ;
 RATE_CONTROL * const lrc = & lc -> rc ;
 if ( svc -> number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) {
 lc -> target_bandwidth = oxcf -> ts_target_bitrate [ layer ] ;
 }
 else {
 lc -> target_bandwidth = oxcf -> ss_target_bitrate [ layer ] ;
 }
 bitrate_alloc = ( float ) lc -> target_bandwidth / target_bandwidth ;
 lrc -> starting_buffer_level = ( int64_t ) ( rc -> starting_buffer_level * bitrate_alloc ) ;
 lrc -> optimal_buffer_level = ( int64_t ) ( rc -> optimal_buffer_level * bitrate_alloc ) ;
 lrc -> maximum_buffer_size = ( int64_t ) ( rc -> maximum_buffer_size * bitrate_alloc ) ;
 lrc -> bits_off_target = MIN ( lrc -> bits_off_target , lrc -> maximum_buffer_size ) ;
 lrc -> buffer_level = MIN ( lrc -> buffer_level , lrc -> maximum_buffer_size ) ;
 if ( svc -> number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) {
 lc -> framerate = cpi -> framerate / oxcf -> ts_rate_decimator [ layer ] ;
 }
 else {
 lc -> framerate = cpi -> framerate ;
 }
 lrc -> avg_frame_bandwidth = ( int ) ( lc -> target_bandwidth / lc -> framerate ) ;
 lrc -> max_frame_bandwidth = rc -> max_frame_bandwidth ;
 lrc -> worst_quality = rc -> worst_quality ;
 lrc -> best_quality = rc -> best_quality ;
 }
 }