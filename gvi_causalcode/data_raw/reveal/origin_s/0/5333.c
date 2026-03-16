static enum PixelFormat ffmpeg_GetFormat ( AVCodecContext * p_context , const enum PixelFormat * pi_fmt ) {
 decoder_t * p_dec = p_context -> opaque ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 vlc_va_t * p_va = p_sys -> p_va ;
 if ( p_va != NULL ) vlc_va_Delete ( p_va ) ;
 bool can_hwaccel = false ;
 for ( size_t i = 0 ;
 pi_fmt [ i ] != AV_PIX_FMT_NONE ;
 i ++ ) {
 const AVPixFmtDescriptor * dsc = av_pix_fmt_desc_get ( pi_fmt [ i ] ) ;
 if ( dsc == NULL ) continue ;
 bool hwaccel = ( dsc -> flags & AV_PIX_FMT_FLAG_HWACCEL ) != 0 ;
 msg_Dbg ( p_dec , "available %sware decoder output format %d (%s)" , hwaccel ? "hard" : "soft" , pi_fmt [ i ] , dsc -> name ) ;
 if ( hwaccel ) can_hwaccel = true ;
 }
 if ( ! can_hwaccel ) goto end ;
 if ( p_context -> profile != FF_PROFILE_UNKNOWN ) p_dec -> fmt_in . i_profile = p_context -> profile ;
 if ( p_context -> level != FF_LEVEL_UNKNOWN ) p_dec -> fmt_in . i_level = p_context -> level ;
 p_va = vlc_va_New ( VLC_OBJECT ( p_dec ) , p_context , & p_dec -> fmt_in ) ;
 if ( p_va == NULL ) goto end ;
 for ( size_t i = 0 ;
 pi_fmt [ i ] != AV_PIX_FMT_NONE ;
 i ++ ) {
 if ( p_va -> pix_fmt != pi_fmt [ i ] ) continue ;
 if ( p_context -> coded_width > 0 && p_context -> coded_height > 0 && vlc_va_Setup ( p_va , & p_context -> hwaccel_context , & p_dec -> fmt_out . video . i_chroma , p_context -> coded_width , p_context -> coded_height ) ) {
 msg_Err ( p_dec , "acceleration setup failure" ) ;
 break ;
 }
 if ( p_va -> description ) msg_Info ( p_dec , "Using %s for hardware decoding." , p_va -> description ) ;
 p_sys -> b_direct_rendering = false ;
 p_sys -> p_va = p_va ;
 p_context -> draw_horiz_band = NULL ;
 return pi_fmt [ i ] ;
 }
 vlc_va_Delete ( p_va ) ;
 end : p_sys -> p_va = NULL ;
 return avcodec_default_get_format ( p_context , pi_fmt ) ;
 }