static LAYER_CONTEXT * get_layer_context ( VP9_COMP * const cpi ) {
 return ( cpi -> svc . number_temporal_layers > 1 && cpi -> oxcf . rc_mode == VPX_CBR ) ? & cpi -> svc . layer_context [ cpi -> svc . temporal_layer_id ] : & cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] ;
 }