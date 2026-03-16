static void free_picture ( AVCodecContext * avctx , Picture * pic ) {
 int i ;
 for ( i = 0 ;
 i < 2 ;
 i ++ ) {
 av_buffer_unref ( & pic -> motion_val_buf [ i ] ) ;
 av_buffer_unref ( & pic -> ref_index_buf [ i ] ) ;
 }
 av_buffer_unref ( & pic -> mb_type_buf ) ;
 av_frame_unref ( & pic -> f ) ;
 }