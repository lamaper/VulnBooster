static void check_src_altref ( VP9_COMP * cpi , const struct lookahead_entry * source ) {
 RATE_CONTROL * const rc = & cpi -> rc ;
 if ( cpi -> oxcf . pass == 2 ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 rc -> is_src_frame_alt_ref = ( gf_group -> update_type [ gf_group -> index ] == OVERLAY_UPDATE ) ;
 }
 else {
 rc -> is_src_frame_alt_ref = cpi -> alt_ref_source && ( source == cpi -> alt_ref_source ) ;
 }
 if ( rc -> is_src_frame_alt_ref ) {
 cpi -> alt_ref_source = NULL ;
 cpi -> refresh_last_frame = 0 ;
 }
 }