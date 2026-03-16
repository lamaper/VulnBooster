static void swap_frame_buffers ( VP9Decoder * pbi ) {
 int ref_index = 0 , mask ;
 VP9_COMMON * const cm = & pbi -> common ;
 for ( mask = pbi -> refresh_frame_flags ;
 mask ;
 mask >>= 1 ) {
 if ( mask & 1 ) {
 const int old_idx = cm -> ref_frame_map [ ref_index ] ;
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ ref_index ] , cm -> new_fb_idx ) ;
 if ( old_idx >= 0 && cm -> frame_bufs [ old_idx ] . ref_count == 0 ) cm -> release_fb_cb ( cm -> cb_priv , & cm -> frame_bufs [ old_idx ] . raw_frame_buffer ) ;
 }
 ++ ref_index ;
 }
 cm -> frame_to_show = get_frame_new_buffer ( cm ) ;
 cm -> frame_bufs [ cm -> new_fb_idx ] . ref_count -- ;
 for ( ref_index = 0 ;
 ref_index < 3 ;
 ref_index ++ ) cm -> frame_refs [ ref_index ] . idx = INT_MAX ;
 }