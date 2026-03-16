static void update_alt_ref_frame_stats ( VP8_COMP * cpi ) {
 VP8_COMMON * cm = & cpi -> common ;
 if ( ! cpi -> auto_gold ) cpi -> frames_till_gf_update_due = DEFAULT_GF_INTERVAL ;
 if ( ( cpi -> pass != 2 ) && cpi -> frames_till_gf_update_due ) {
 cpi -> current_gf_interval = cpi -> frames_till_gf_update_due ;
 cpi -> gf_overspend_bits += cpi -> projected_frame_size ;
 cpi -> non_gf_bitrate_adjustment = cpi -> gf_overspend_bits / cpi -> frames_till_gf_update_due ;
 }
 vpx_memset ( cpi -> gf_active_flags , 1 , ( cm -> mb_rows * cm -> mb_cols ) ) ;
 cpi -> gf_active_count = cm -> mb_rows * cm -> mb_cols ;
 cpi -> frames_since_golden = 0 ;
 cpi -> source_alt_ref_pending = 0 ;
 cpi -> source_alt_ref_active = 1 ;
 }