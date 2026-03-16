static int ffmpeg_GetFrameBuf ( struct AVCodecContext * p_context , AVFrame * p_ff_pic ) {
 decoder_t * p_dec = ( decoder_t * ) p_context -> opaque ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 p_ff_pic -> opaque = NULL ;



 if ( ! p_sys -> b_direct_rendering ) return avcodec_default_get_buffer ( p_context , p_ff_pic ) ;
 wait_mt ( p_sys ) ;
 picture_t * p_pic = ffmpeg_dr_GetFrameBuf ( p_context ) ;
 if ( ! p_pic ) {
 if ( p_sys -> i_direct_rendering_used != 0 ) {
 msg_Warn ( p_dec , "disabling direct rendering" ) ;
 p_sys -> i_direct_rendering_used = 0 ;
 }
 post_mt ( p_sys ) ;
 return avcodec_default_get_buffer ( p_context , p_ff_pic ) ;
 }
 if ( p_sys -> i_direct_rendering_used != 1 ) {
 msg_Dbg ( p_dec , "using direct rendering" ) ;
 p_sys -> i_direct_rendering_used = 1 ;
 }
 p_context -> draw_horiz_band = NULL ;
 post_mt ( p_sys ) ;
 p_ff_pic -> opaque = ( void * ) p_pic ;
 p_ff_pic -> type = FF_BUFFER_TYPE_USER ;
 p_ff_pic -> data [ 0 ] = p_pic -> p [ 0 ] . p_pixels ;
 p_ff_pic -> data [ 1 ] = p_pic -> p [ 1 ] . p_pixels ;
 p_ff_pic -> data [ 2 ] = p_pic -> p [ 2 ] . p_pixels ;
 p_ff_pic -> data [ 3 ] = NULL ;
 p_ff_pic -> linesize [ 0 ] = p_pic -> p [ 0 ] . i_pitch ;
 p_ff_pic -> linesize [ 1 ] = p_pic -> p [ 1 ] . i_pitch ;
 p_ff_pic -> linesize [ 2 ] = p_pic -> p [ 2 ] . i_pitch ;
 p_ff_pic -> linesize [ 3 ] = 0 ;
 return 0 ;
 }