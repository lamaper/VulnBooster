void vp9_inc_frame_in_layer ( VP9_COMP * const cpi ) {
 LAYER_CONTEXT * const lc = ( cpi -> svc . number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) ? & cpi -> svc . layer_context [ cpi -> svc . temporal_layer_id ] : & cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] ;
 ++ lc -> current_video_frame_in_layer ;
 ++ lc -> frames_from_key_frame ;
 }