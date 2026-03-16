int vp9_alloc_ref_frame_buffers ( VP9_COMMON * cm , int width , int height ) {
 int i ;
 const int ss_x = cm -> subsampling_x ;
 const int ss_y = cm -> subsampling_y ;
 vp9_free_ref_frame_buffers ( cm ) ;
 for ( i = 0 ;
 i < FRAME_BUFFERS ;
 ++ i ) {
 cm -> frame_bufs [ i ] . ref_count = 0 ;
 if ( vp9_alloc_frame_buffer ( & cm -> frame_bufs [ i ] . buf , width , height , ss_x , ss_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_ENC_BORDER_IN_PIXELS ) < 0 ) goto fail ;
 }
 init_frame_bufs ( cm ) ;


 fail : vp9_free_ref_frame_buffers ( cm ) ;
 return 1 ;
 }