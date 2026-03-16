int vp9_is_upper_layer_key_frame ( const VP9_COMP * const cpi ) {
 return is_two_pass_svc ( cpi ) && cpi -> svc . spatial_layer_id > 0 && cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . is_key_frame ;
 }