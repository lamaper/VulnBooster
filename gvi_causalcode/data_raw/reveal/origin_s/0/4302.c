static void update_alt_ref_frame_stats ( VP9_COMP * cpi ) {
 RATE_CONTROL * const rc = & cpi -> rc ;
 rc -> frames_since_golden = 0 ;
 rc -> source_alt_ref_pending = 0 ;
 rc -> source_alt_ref_active = 1 ;
 }