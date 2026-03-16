static int get_refresh_mask ( VP9_COMP * cpi ) {
 if ( vp9_preserve_existing_gf ( cpi ) ) {
 return ( cpi -> refresh_last_frame << cpi -> lst_fb_idx ) | ( cpi -> refresh_golden_frame << cpi -> alt_fb_idx ) ;
 }
 else {
 int arf_idx = cpi -> alt_fb_idx ;
 if ( ( cpi -> oxcf . pass == 2 ) && cpi -> multi_arf_allowed ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 arf_idx = gf_group -> arf_update_idx [ gf_group -> index ] ;
 }
 return ( cpi -> refresh_last_frame << cpi -> lst_fb_idx ) | ( cpi -> refresh_golden_frame << cpi -> gld_fb_idx ) | ( cpi -> refresh_alt_ref_frame << arf_idx ) ;
 }
 }