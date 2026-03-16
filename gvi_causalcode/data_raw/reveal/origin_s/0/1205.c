int InitVideoDec ( decoder_t * p_dec , AVCodecContext * p_context , AVCodec * p_codec , int i_codec_id , const char * psz_namecodec ) {
 decoder_sys_t * p_sys ;
 int i_val ;
 if ( ( p_dec -> p_sys = p_sys = calloc ( 1 , sizeof ( decoder_sys_t ) ) ) == NULL ) return VLC_ENOMEM ;
 p_codec -> type = AVMEDIA_TYPE_VIDEO ;
 p_context -> codec_type = AVMEDIA_TYPE_VIDEO ;
 p_context -> codec_id = i_codec_id ;
 p_sys -> p_context = p_context ;
 p_sys -> p_codec = p_codec ;
 p_sys -> i_codec_id = i_codec_id ;
 p_sys -> psz_namecodec = psz_namecodec ;
 p_sys -> p_ff_pic = avcodec_alloc_frame ( ) ;
 p_sys -> b_delayed_open = true ;
 p_sys -> p_va = NULL ;
 vlc_sem_init ( & p_sys -> sem_mt , 0 ) ;
 p_sys -> p_context -> codec_tag = ffmpeg_CodecTag ( p_dec -> fmt_in . i_original_fourcc ? : p_dec -> fmt_in . i_codec ) ;
 p_sys -> p_context -> workaround_bugs = var_InheritInteger ( p_dec , "avcodec-workaround-bugs" ) ;
 p_sys -> p_context -> err_recognition = var_InheritInteger ( p_dec , "avcodec-error-resilience" ) ;
 if ( var_CreateGetBool ( p_dec , "grayscale" ) ) p_sys -> p_context -> flags |= CODEC_FLAG_GRAY ;


 if ( i_val ) p_sys -> p_context -> debug_mv = i_val ;
 i_val = var_CreateGetInteger ( p_dec , "avcodec-skiploopfilter" ) ;
 if ( i_val >= 4 ) p_sys -> p_context -> skip_loop_filter = AVDISCARD_ALL ;
 else if ( i_val == 3 ) p_sys -> p_context -> skip_loop_filter = AVDISCARD_NONKEY ;
 else if ( i_val == 2 ) p_sys -> p_context -> skip_loop_filter = AVDISCARD_BIDIR ;
 else if ( i_val == 1 ) p_sys -> p_context -> skip_loop_filter = AVDISCARD_NONREF ;
 if ( var_CreateGetBool ( p_dec , "avcodec-fast" ) ) p_sys -> p_context -> flags2 |= CODEC_FLAG2_FAST ;
 p_sys -> b_hurry_up = var_CreateGetBool ( p_dec , "avcodec-hurry-up" ) ;
 i_val = var_CreateGetInteger ( p_dec , "avcodec-skip-frame" ) ;
 if ( i_val >= 4 ) p_sys -> p_context -> skip_frame = AVDISCARD_ALL ;
 else if ( i_val == 3 ) p_sys -> p_context -> skip_frame = AVDISCARD_NONKEY ;
 else if ( i_val == 2 ) p_sys -> p_context -> skip_frame = AVDISCARD_BIDIR ;
 else if ( i_val == 1 ) p_sys -> p_context -> skip_frame = AVDISCARD_NONREF ;
 else if ( i_val == - 1 ) p_sys -> p_context -> skip_frame = AVDISCARD_NONE ;
 else p_sys -> p_context -> skip_frame = AVDISCARD_DEFAULT ;
 p_sys -> i_skip_frame = p_sys -> p_context -> skip_frame ;
 i_val = var_CreateGetInteger ( p_dec , "avcodec-skip-idct" ) ;
 if ( i_val >= 4 ) p_sys -> p_context -> skip_idct = AVDISCARD_ALL ;
 else if ( i_val == 3 ) p_sys -> p_context -> skip_idct = AVDISCARD_NONKEY ;
 else if ( i_val == 2 ) p_sys -> p_context -> skip_idct = AVDISCARD_BIDIR ;
 else if ( i_val == 1 ) p_sys -> p_context -> skip_idct = AVDISCARD_NONREF ;
 else if ( i_val == - 1 ) p_sys -> p_context -> skip_idct = AVDISCARD_NONE ;
 else p_sys -> p_context -> skip_idct = AVDISCARD_DEFAULT ;
 p_sys -> i_skip_idct = p_sys -> p_context -> skip_idct ;
 p_sys -> b_direct_rendering = false ;
 p_sys -> i_direct_rendering_used = - 1 ;
 if ( var_CreateGetBool ( p_dec , "avcodec-dr" ) && ( p_sys -> p_codec -> capabilities & CODEC_CAP_DR1 ) && p_sys -> i_codec_id != AV_CODEC_ID_TSCC && p_sys -> i_codec_id != AV_CODEC_ID_CSCD && p_sys -> i_codec_id != AV_CODEC_ID_CINEPAK && ! p_sys -> p_context -> debug_mv ) {
 p_sys -> b_direct_rendering = true ;
 }
 if ( p_sys -> b_direct_rendering ) {
 msg_Dbg ( p_dec , "trying to use direct rendering" ) ;
 p_sys -> p_context -> flags |= CODEC_FLAG_EMU_EDGE ;
 }
 else {
 msg_Dbg ( p_dec , "direct rendering is disabled" ) ;
 }
 p_sys -> p_context -> get_format = ffmpeg_GetFormat ;


 p_sys -> p_context -> reget_buffer = avcodec_default_reget_buffer ;
 p_sys -> p_context -> release_buffer = ffmpeg_ReleaseFrameBuf ;


 if ( i_thread_count <= 0 ) {
 i_thread_count = vlc_GetCPUCount ( ) ;
 if ( i_thread_count > 1 ) i_thread_count ++ ;
 i_thread_count = __MIN ( i_thread_count , 4 ) ;
 }
 i_thread_count = __MIN ( i_thread_count , 16 ) ;
 msg_Dbg ( p_dec , "allowing %d thread(s) for decoding" , i_thread_count ) ;
 p_sys -> p_context -> thread_count = i_thread_count ;
 p_sys -> p_context -> thread_safe_callbacks = true ;
 switch ( i_codec_id ) {
 case AV_CODEC_ID_MPEG4 : case AV_CODEC_ID_H263 : p_sys -> p_context -> thread_type = 0 ;
 break ;
 case AV_CODEC_ID_MPEG1VIDEO : case AV_CODEC_ID_MPEG2VIDEO : p_sys -> p_context -> thread_type &= ~ FF_THREAD_SLICE ;



 if ( avcodec_hw == NULL || strcasecmp ( avcodec_hw , "none" ) ) {
 msg_Warn ( p_dec , "threaded frame decoding is not compatible with DXVA2, disabled" ) ;
 p_sys -> p_context -> thread_type &= ~ FF_THREAD_FRAME ;
 }
 free ( avcodec_hw ) ;


 p_sys -> b_has_b_frames = false ;
 p_sys -> b_first_frame = true ;
 p_sys -> b_flush = false ;
 p_sys -> i_late_frames = 0 ;
 p_dec -> fmt_out . i_cat = VIDEO_ES ;
 if ( GetVlcChroma ( & p_dec -> fmt_out . video , p_context -> pix_fmt ) != VLC_SUCCESS ) {
 p_dec -> fmt_out . i_codec = VLC_CODEC_I420 ;
 }
 p_dec -> fmt_out . i_codec = p_dec -> fmt_out . video . i_chroma ;
 p_dec -> fmt_out . video . orientation = p_dec -> fmt_in . video . orientation ;

 if ( p_dec -> fmt_in . video . p_palette ) {
 p_sys -> palette . palette_changed = 1 ;
 for ( int i = 0 ;
 i < __MIN ( AVPALETTE_COUNT , p_dec -> fmt_in . video . p_palette -> i_entries ) ;
 i ++ ) {
 union {
 uint32_t u ;
 uint8_t a [ 4 ] ;
 }
 c ;
 c . a [ 0 ] = p_dec -> fmt_in . video . p_palette -> palette [ i ] [ 0 ] ;
 c . a [ 1 ] = p_dec -> fmt_in . video . p_palette -> palette [ i ] [ 1 ] ;
 c . a [ 2 ] = p_dec -> fmt_in . video . p_palette -> palette [ i ] [ 2 ] ;
 c . a [ 3 ] = p_dec -> fmt_in . video . p_palette -> palette [ i ] [ 3 ] ;
 p_sys -> palette . palette [ i ] = c . u ;
 }
 p_sys -> p_context -> palctrl = & p_sys -> palette ;
 p_dec -> fmt_out . video . p_palette = malloc ( sizeof ( video_palette_t ) ) ;
 if ( p_dec -> fmt_out . video . p_palette ) * p_dec -> fmt_out . video . p_palette = * p_dec -> fmt_in . video . p_palette ;
 }
 else if ( p_sys -> i_codec_id != CODEC_ID_MSVIDEO1 && p_sys -> i_codec_id != CODEC_ID_CINEPAK ) {
 p_sys -> p_context -> palctrl = & p_sys -> palette ;
 }

 p_sys -> palette_sent = false ;
 p_dec -> fmt_out . video . p_palette = malloc ( sizeof ( video_palette_t ) ) ;
 if ( p_dec -> fmt_out . video . p_palette ) * p_dec -> fmt_out . video . p_palette = * p_dec -> fmt_in . video . p_palette ;
 }
 else p_sys -> palette_sent = true ;

 if ( ffmpeg_OpenCodec ( p_dec ) < 0 ) {
 msg_Err ( p_dec , "cannot open codec (%s)" , p_sys -> psz_namecodec ) ;
 avcodec_free_frame ( & p_sys -> p_ff_pic ) ;
 vlc_sem_destroy ( & p_sys -> sem_mt ) ;
 free ( p_sys ) ;
 return VLC_EGENERIC ;
 }
 if ( p_dec -> fmt_in . i_codec == VLC_CODEC_VP9 ) p_dec -> b_need_packetized = true ;
 return VLC_SUCCESS ;
 }