void configure_buffer_updates ( VP9_COMP * cpi ) {
 TWO_PASS * const twopass = & cpi -> twopass ;
 cpi -> rc . is_src_frame_alt_ref = 0 ;
 switch ( twopass -> gf_group . update_type [ twopass -> gf_group . index ] ) {
 case KF_UPDATE : cpi -> refresh_last_frame = 1 ;
 cpi -> refresh_golden_frame = 1 ;
 cpi -> refresh_alt_ref_frame = 1 ;
 break ;
 case LF_UPDATE : cpi -> refresh_last_frame = 1 ;
 cpi -> refresh_golden_frame = 0 ;
 cpi -> refresh_alt_ref_frame = 0 ;
 break ;
 case GF_UPDATE : cpi -> refresh_last_frame = 1 ;
 cpi -> refresh_golden_frame = 1 ;
 cpi -> refresh_alt_ref_frame = 0 ;
 break ;
 case OVERLAY_UPDATE : cpi -> refresh_last_frame = 0 ;
 cpi -> refresh_golden_frame = 1 ;
 cpi -> refresh_alt_ref_frame = 0 ;
 cpi -> rc . is_src_frame_alt_ref = 1 ;
 break ;
 case ARF_UPDATE : cpi -> refresh_last_frame = 0 ;
 cpi -> refresh_golden_frame = 0 ;
 cpi -> refresh_alt_ref_frame = 1 ;
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 if ( is_two_pass_svc ( cpi ) ) {
 if ( cpi -> svc . layer_context [ cpi -> svc . spatial_layer_id ] . gold_ref_idx < 0 ) cpi -> refresh_golden_frame = 0 ;
 if ( cpi -> alt_ref_source == NULL ) cpi -> refresh_alt_ref_frame = 0 ;
 }
 }