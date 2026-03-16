void vp9_init_second_pass_spatial_svc ( VP9_COMP * cpi ) {
 SVC * const svc = & cpi -> svc ;
 int i ;
 for ( i = 0 ;
 i < svc -> number_spatial_layers ;
 ++ i ) {
 TWO_PASS * const twopass = & svc -> layer_context [ i ] . twopass ;
 svc -> spatial_layer_id = i ;
 vp9_init_second_pass ( cpi ) ;
 twopass -> total_stats . spatial_layer_id = i ;
 twopass -> total_left_stats . spatial_layer_id = i ;
 }
 svc -> spatial_layer_id = 0 ;
 }