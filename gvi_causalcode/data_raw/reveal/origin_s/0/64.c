static void init_frame_bufs ( VP9_COMMON * cm ) {
 int i ;
 cm -> new_fb_idx = FRAME_BUFFERS - 1 ;
 cm -> frame_bufs [ cm -> new_fb_idx ] . ref_count = 1 ;
 for ( i = 0 ;
 i < REF_FRAMES ;
 ++ i ) {
 cm -> ref_frame_map [ i ] = i ;
 cm -> frame_bufs [ i ] . ref_count = 1 ;
 }
 }