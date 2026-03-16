void vp9_update_temporal_layer_framerate ( VP9_COMP * const cpi ) {
 SVC * const svc = & cpi -> svc ;
 const VP9EncoderConfig * const oxcf = & cpi -> oxcf ;
 LAYER_CONTEXT * const lc = get_layer_context ( cpi ) ;
 RATE_CONTROL * const lrc = & lc -> rc ;
 const int layer = svc -> temporal_layer_id ;
 lc -> framerate = cpi -> framerate / oxcf -> ts_rate_decimator [ layer ] ;
 lrc -> avg_frame_bandwidth = ( int ) ( lc -> target_bandwidth / lc -> framerate ) ;
 lrc -> max_frame_bandwidth = cpi -> rc . max_frame_bandwidth ;
 if ( layer == 0 ) {
 lc -> avg_frame_size = lrc -> avg_frame_bandwidth ;
 }
 else {
 const double prev_layer_framerate = cpi -> framerate / oxcf -> ts_rate_decimator [ layer - 1 ] ;
 const int prev_layer_target_bandwidth = oxcf -> ts_target_bitrate [ layer - 1 ] ;
 lc -> avg_frame_size = ( int ) ( ( lc -> target_bandwidth - prev_layer_target_bandwidth ) / ( lc -> framerate - prev_layer_framerate ) ) ;
 }
 }