static void set_ext_overrides ( VP9_COMP * cpi ) {
 if ( cpi -> ext_refresh_frame_context_pending ) {
 cpi -> common . refresh_frame_context = cpi -> ext_refresh_frame_context ;
 cpi -> ext_refresh_frame_context_pending = 0 ;
 }
 if ( cpi -> ext_refresh_frame_flags_pending ) {
 cpi -> refresh_last_frame = cpi -> ext_refresh_last_frame ;
 cpi -> refresh_golden_frame = cpi -> ext_refresh_golden_frame ;
 cpi -> refresh_alt_ref_frame = cpi -> ext_refresh_alt_ref_frame ;
 cpi -> ext_refresh_frame_flags_pending = 0 ;
 }
 }