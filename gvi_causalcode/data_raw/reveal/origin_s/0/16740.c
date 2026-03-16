static void update_golden_frame_stats ( VP8_COMP * cpi ) {
 VP8_COMMON * cm = & cpi -> common ;
 if ( cm -> refresh_golden_frame ) {
 if ( ! cpi -> auto_gold ) cpi -> frames_till_gf_update_due = DEFAULT_GF_INTERVAL ;
 if ( ( cpi -> pass != 2 ) && ( cpi -> frames_till_gf_update_due > 0 ) ) {
 cpi -> current_gf_interval = cpi -> frames_till_gf_update_due ;
 if ( ( cm -> frame_type != KEY_FRAME ) && ! cpi -> source_alt_ref_active ) {
 cpi -> gf_overspend_bits += ( cpi -> projected_frame_size - cpi -> inter_frame_target ) ;
 }
 cpi -> non_gf_bitrate_adjustment = cpi -> gf_overspend_bits / cpi -> frames_till_gf_update_due ;
 }
 vpx_memset ( cpi -> gf_active_flags , 1 , ( cm -> mb_rows * cm -> mb_cols ) ) ;
 cpi -> gf_active_count = cm -> mb_rows * cm -> mb_cols ;
 cm -> refresh_golden_frame = 0 ;
 cpi -> frames_since_golden = 0 ;
 cpi -> recent_ref_frame_usage [ INTRA_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ LAST_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ GOLDEN_FRAME ] = 1 ;
 cpi -> recent_ref_frame_usage [ ALTREF_FRAME ] = 1 ;
 if ( cpi -> oxcf . fixed_q >= 0 && cpi -> oxcf . play_alternate && ! cpi -> common . refresh_alt_ref_frame ) {
 cpi -> source_alt_ref_pending = 1 ;
 cpi -> frames_till_gf_update_due = cpi -> baseline_gf_interval ;
 }
 if ( ! cpi -> source_alt_ref_pending ) cpi -> source_alt_ref_active = 0 ;
 if ( cpi -> frames_till_gf_update_due > 0 ) cpi -> frames_till_gf_update_due -- ;
 }
 else if ( ! cpi -> common . refresh_alt_ref_frame ) {
 if ( cpi -> frames_till_gf_update_due > 0 ) cpi -> frames_till_gf_update_due -- ;
 if ( cpi -> frames_till_alt_ref_frame ) cpi -> frames_till_alt_ref_frame -- ;
 cpi -> frames_since_golden ++ ;
 if ( cpi -> frames_since_golden > 1 ) {
 cpi -> recent_ref_frame_usage [ INTRA_FRAME ] += cpi -> mb . count_mb_ref_frame_usage [ INTRA_FRAME ] ;
 cpi -> recent_ref_frame_usage [ LAST_FRAME ] += cpi -> mb . count_mb_ref_frame_usage [ LAST_FRAME ] ;
 cpi -> recent_ref_frame_usage [ GOLDEN_FRAME ] += cpi -> mb . count_mb_ref_frame_usage [ GOLDEN_FRAME ] ;
 cpi -> recent_ref_frame_usage [ ALTREF_FRAME ] += cpi -> mb . count_mb_ref_frame_usage [ ALTREF_FRAME ] ;
 }
 }
 }