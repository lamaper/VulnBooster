static void ffmpeg_CopyPicture ( decoder_t * p_dec , picture_t * p_pic , AVFrame * p_ff_pic ) {
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 if ( p_sys -> p_va ) {
 vlc_va_Extract ( p_sys -> p_va , p_pic , p_ff_pic -> opaque , p_ff_pic -> data [ 3 ] ) ;
 }
 else if ( FindVlcChroma ( p_sys -> p_context -> pix_fmt ) ) {
 int i_plane , i_size , i_line ;
 uint8_t * p_dst , * p_src ;
 int i_src_stride , i_dst_stride ;
 for ( i_plane = 0 ;
 i_plane < p_pic -> i_planes ;
 i_plane ++ ) {
 p_src = p_ff_pic -> data [ i_plane ] ;
 p_dst = p_pic -> p [ i_plane ] . p_pixels ;
 i_src_stride = p_ff_pic -> linesize [ i_plane ] ;
 i_dst_stride = p_pic -> p [ i_plane ] . i_pitch ;
 i_size = __MIN ( i_src_stride , i_dst_stride ) ;
 for ( i_line = 0 ;
 i_line < p_pic -> p [ i_plane ] . i_visible_lines ;
 i_line ++ ) {
 memcpy ( p_dst , p_src , i_size ) ;
 p_src += i_src_stride ;
 p_dst += i_dst_stride ;
 }
 }
 }
 else {
 const char * name = av_get_pix_fmt_name ( p_sys -> p_context -> pix_fmt ) ;
 msg_Err ( p_dec , "Unsupported decoded output format %d (%s)" , p_sys -> p_context -> pix_fmt , name ? name : "unknown" ) ;
 p_dec -> b_error = 1 ;
 }
 }