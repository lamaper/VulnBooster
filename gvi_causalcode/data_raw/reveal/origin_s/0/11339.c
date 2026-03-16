static void ffmpeg_ReleaseFrameBuf ( struct AVCodecContext * p_context , AVFrame * p_ff_pic ) {
 decoder_t * p_dec = ( decoder_t * ) p_context -> opaque ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 if ( p_sys -> p_va ) vlc_va_Release ( p_sys -> p_va , p_ff_pic -> opaque , p_ff_pic -> data [ 0 ] ) ;
 else if ( p_ff_pic -> opaque ) decoder_UnlinkPicture ( p_dec , ( picture_t * ) p_ff_pic -> opaque ) ;
 else if ( p_ff_pic -> type == FF_BUFFER_TYPE_INTERNAL ) avcodec_default_release_buffer ( p_context , p_ff_pic ) ;
 for ( int i = 0 ;
 i < 4 ;
 i ++ ) p_ff_pic -> data [ i ] = NULL ;
 }