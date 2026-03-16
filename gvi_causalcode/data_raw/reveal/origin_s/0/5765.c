static void update_golden_frame_stats ( VP9_COMP * cpi ) {
 RATE_CONTROL * const rc = & cpi -> rc ;
 if ( cpi -> refresh_golden_frame ) {
 rc -> frames_since_golden = 0 ;
 if ( cpi -> oxcf . pass == 2 ) {
 if ( ! rc -> source_alt_ref_pending && cpi -> twopass . gf_group . rf_level [ 0 ] == GF_ARF_STD ) rc -> source_alt_ref_active = 0 ;
 }
 else if ( ! rc -> source_alt_ref_pending ) {
 rc -> source_alt_ref_active = 0 ;
 }
 if ( rc -> frames_till_gf_update_due > 0 ) rc -> frames_till_gf_update_due -- ;
 }
 else if ( ! cpi -> refresh_alt_ref_frame ) {
 if ( rc -> frames_till_gf_update_due > 0 ) rc -> frames_till_gf_update_due -- ;
 rc -> frames_since_golden ++ ;
 }
 }