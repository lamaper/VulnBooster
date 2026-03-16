static int ffmpeg_va_GetFrameBuf ( struct AVCodecContext * p_context , AVFrame * p_ff_pic ) {
 decoder_t * p_dec = ( decoder_t * ) p_context -> opaque ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 vlc_va_t * p_va = p_sys -> p_va ;
 if ( vlc_va_Setup ( p_va , & p_context -> hwaccel_context , & p_dec -> fmt_out . video . i_chroma , p_context -> coded_width , p_context -> coded_height ) ) {
 msg_Err ( p_dec , "vlc_va_Setup failed" ) ;
 return - 1 ;
 }
 if ( vlc_va_Get ( p_va , & p_ff_pic -> opaque , & p_ff_pic -> data [ 0 ] ) ) {
 msg_Err ( p_dec , "vlc_va_Get failed" ) ;
 return - 1 ;
 }
 p_ff_pic -> data [ 3 ] = p_ff_pic -> data [ 0 ] ;
 p_ff_pic -> type = FF_BUFFER_TYPE_USER ;
 return 0 ;
 }