static void update_layer_buffer_level ( SVC * svc , int encoded_frame_size ) {
 int temporal_layer = 0 ;
 int current_temporal_layer = svc -> temporal_layer_id ;
 for ( temporal_layer = current_temporal_layer + 1 ;
 temporal_layer < svc -> number_temporal_layers ;
 ++ temporal_layer ) {
 LAYER_CONTEXT * lc = & svc -> layer_context [ temporal_layer ] ;
 RATE_CONTROL * lrc = & lc -> rc ;
 int bits_off_for_this_layer = ( int ) ( lc -> target_bandwidth / lc -> framerate - encoded_frame_size ) ;
 lrc -> bits_off_target += bits_off_for_this_layer ;
 lrc -> bits_off_target = MIN ( lrc -> bits_off_target , lrc -> maximum_buffer_size ) ;
 lrc -> buffer_level = lrc -> bits_off_target ;
 }
 }