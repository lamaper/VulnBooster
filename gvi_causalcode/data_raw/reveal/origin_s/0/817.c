void vp9_restore_layer_context ( VP9_COMP * const cpi ) {
 LAYER_CONTEXT * const lc = get_layer_context ( cpi ) ;
 const int old_frame_since_key = cpi -> rc . frames_since_key ;
 const int old_frame_to_key = cpi -> rc . frames_to_key ;
 cpi -> rc = lc -> rc ;
 cpi -> twopass = lc -> twopass ;
 cpi -> oxcf . target_bandwidth = lc -> target_bandwidth ;
 cpi -> alt_ref_source = lc -> alt_ref_source ;
 if ( cpi -> svc . number_temporal_layers > 1 ) {
 cpi -> rc . frames_since_key = old_frame_since_key ;
 cpi -> rc . frames_to_key = old_frame_to_key ;
 }
 }