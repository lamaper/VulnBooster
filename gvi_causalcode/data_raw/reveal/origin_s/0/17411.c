void vp9_free_ref_frame_buffers ( VP9_COMMON * cm ) {
 int i ;
 for ( i = 0 ;
 i < FRAME_BUFFERS ;
 ++ i ) {
 vp9_free_frame_buffer ( & cm -> frame_bufs [ i ] . buf ) ;
 if ( cm -> frame_bufs [ i ] . ref_count > 0 && cm -> frame_bufs [ i ] . raw_frame_buffer . data != NULL ) {
 cm -> release_fb_cb ( cm -> cb_priv , & cm -> frame_bufs [ i ] . raw_frame_buffer ) ;
 cm -> frame_bufs [ i ] . ref_count = 0 ;
 }
 }
 vp9_free_frame_buffer ( & cm -> post_proc_buffer ) ;
 }