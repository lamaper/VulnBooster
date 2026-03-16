static void reset_temporal_layer_change ( VP8_COMP * cpi , VP8_CONFIG * oxcf , const int prev_num_layers ) {
 int i ;
 double prev_layer_framerate = 0 ;
 const int curr_num_layers = cpi -> oxcf . number_of_layers ;
 if ( prev_num_layers == 1 ) {
 cpi -> current_layer = 0 ;
 save_layer_context ( cpi ) ;
 }
 for ( i = 0 ;
 i < curr_num_layers ;
 i ++ ) {
 LAYER_CONTEXT * lc = & cpi -> layer_context [ i ] ;
 if ( i >= prev_num_layers ) {
 init_temporal_layer_context ( cpi , oxcf , i , prev_layer_framerate ) ;
 }
 lc -> buffer_level = cpi -> oxcf . starting_buffer_level_in_ms * cpi -> oxcf . target_bitrate [ i ] ;
 lc -> bits_off_target = lc -> buffer_level ;
 if ( curr_num_layers == 1 ) {
 lc -> target_bandwidth = cpi -> oxcf . target_bandwidth ;
 lc -> buffer_level = cpi -> oxcf . starting_buffer_level_in_ms * lc -> target_bandwidth / 1000 ;
 lc -> bits_off_target = lc -> buffer_level ;
 restore_layer_context ( cpi , 0 ) ;
 }
 prev_layer_framerate = cpi -> output_framerate / cpi -> oxcf . rate_decimator [ i ] ;
 }
 }