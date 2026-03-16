static picture_t * ffmpeg_dr_GetFrameBuf ( struct AVCodecContext * p_context ) {
 decoder_t * p_dec = ( decoder_t * ) p_context -> opaque ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 int i_width = p_context -> width ;
 int i_height = p_context -> height ;
 avcodec_align_dimensions ( p_context , & i_width , & i_height ) ;
 picture_t * p_pic = NULL ;
 if ( GetVlcChroma ( & p_dec -> fmt_out . video , p_context -> pix_fmt ) != VLC_SUCCESS ) goto no_dr ;
 if ( p_context -> pix_fmt == AV_PIX_FMT_PAL8 ) goto no_dr ;
 p_dec -> fmt_out . i_codec = p_dec -> fmt_out . video . i_chroma ;
 p_pic = ffmpeg_NewPictBuf ( p_dec , p_context ) ;
 if ( ! p_pic ) goto no_dr ;
 if ( p_pic -> p [ 0 ] . i_pitch / p_pic -> p [ 0 ] . i_pixel_pitch < i_width || p_pic -> p [ 0 ] . i_lines < i_height ) goto no_dr ;
 for ( int i = 0 ;
 i < p_pic -> i_planes ;
 i ++ ) {
 unsigned i_align ;
 switch ( p_sys -> i_codec_id ) {
 case AV_CODEC_ID_SVQ1 : case AV_CODEC_ID_VP5 : case AV_CODEC_ID_VP6 : case AV_CODEC_ID_VP6F : case AV_CODEC_ID_VP6A : i_align = 16 ;
 break ;
 default : i_align = i == 0 ? 16 : 8 ;
 break ;
 }
 if ( p_pic -> p [ i ] . i_pitch % i_align ) goto no_dr ;
 if ( ( intptr_t ) p_pic -> p [ i ] . p_pixels % i_align ) goto no_dr ;
 }
 if ( p_context -> pix_fmt == AV_PIX_FMT_YUV422P ) {
 if ( 2 * p_pic -> p [ 1 ] . i_pitch != p_pic -> p [ 0 ] . i_pitch || 2 * p_pic -> p [ 2 ] . i_pitch != p_pic -> p [ 0 ] . i_pitch ) goto no_dr ;
 }
 return p_pic ;
 no_dr : if ( p_pic ) decoder_DeletePicture ( p_dec , p_pic ) ;
 return NULL ;
 }