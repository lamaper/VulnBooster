static int is_skippable_frame ( const VP9_COMP * cpi ) {
 const SVC * const svc = & cpi -> svc ;
 const TWO_PASS * const twopass = is_two_pass_svc ( cpi ) ? & svc -> layer_context [ svc -> spatial_layer_id ] . twopass : & cpi -> twopass ;
 return ( ! frame_is_intra_only ( & cpi -> common ) && twopass -> stats_in - 2 > twopass -> stats_in_start && twopass -> stats_in < twopass -> stats_in_end && ( twopass -> stats_in - 1 ) -> pcnt_inter - ( twopass -> stats_in - 1 ) -> pcnt_motion == 1 && ( twopass -> stats_in - 2 ) -> pcnt_inter - ( twopass -> stats_in - 2 ) -> pcnt_motion == 1 && twopass -> stats_in -> pcnt_inter - twopass -> stats_in -> pcnt_motion == 1 ) ;
 }