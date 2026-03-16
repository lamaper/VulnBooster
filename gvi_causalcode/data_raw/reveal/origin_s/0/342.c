void vp9_end_first_pass ( VP9_COMP * cpi ) {
 if ( is_two_pass_svc ( cpi ) ) {
 int i ;
 for ( i = 0 ;
 i < cpi -> svc . number_spatial_layers ;
 ++ i ) {
 output_stats ( & cpi -> svc . layer_context [ i ] . twopass . total_stats , cpi -> output_pkt_list ) ;
 }
 }
 else {
 output_stats ( & cpi -> twopass . total_stats , cpi -> output_pkt_list ) ;
 }
 }