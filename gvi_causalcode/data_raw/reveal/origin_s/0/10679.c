static int OpenDecoder ( vlc_object_t * p_this ) {
 decoder_t * p_dec = ( decoder_t * ) p_this ;
 decoder_sys_t * p_sys ;
 switch ( p_dec -> fmt_in . i_codec ) {
 case VLC_CODEC_SUBT : case VLC_CODEC_ITU_T140 : break ;
 default : return VLC_EGENERIC ;
 }
 p_dec -> pf_decode_sub = DecodeBlock ;
 p_dec -> fmt_out . i_cat = SPU_ES ;
 p_dec -> fmt_out . i_codec = 0 ;
 p_dec -> p_sys = p_sys = calloc ( 1 , sizeof ( * p_sys ) ) ;
 if ( p_sys == NULL ) return VLC_ENOMEM ;
 p_sys -> i_align = 0 ;
 p_sys -> iconv_handle = ( vlc_iconv_t ) - 1 ;
 p_sys -> b_autodetect_utf8 = false ;
 const char * encoding ;
 char * var = NULL ;
 if ( p_dec -> fmt_in . i_codec == VLC_CODEC_ITU_T140 ) encoding = "UTF-8" ;
 else if ( p_dec -> fmt_in . subs . psz_encoding && * p_dec -> fmt_in . subs . psz_encoding ) {
 encoding = p_dec -> fmt_in . subs . psz_encoding ;
 msg_Dbg ( p_dec , "trying demuxer-specified character encoding: %s" , encoding ) ;
 }
 else {
 if ( ( var = var_InheritString ( p_dec , "subsdec-encoding" ) ) != NULL ) {
 msg_Dbg ( p_dec , "trying configured character encoding: %s" , var ) ;
 if ( ! strcmp ( var , "system" ) ) {
 free ( var ) ;
 var = NULL ;
 encoding = "" ;
 }
 else encoding = var ;
 }
 else {
 encoding = vlc_pgettext ( "GetACP" , "CP1252" ) ;
 msg_Dbg ( p_dec , "trying default character encoding: %s" , encoding ) ;
 }
 if ( var_InheritBool ( p_dec , "subsdec-autodetect-utf8" ) ) {
 msg_Dbg ( p_dec , "using automatic UTF-8 detection" ) ;
 p_sys -> b_autodetect_utf8 = true ;
 }
 }
 if ( strcasecmp ( encoding , "UTF-8" ) && strcasecmp ( encoding , "utf8" ) ) {
 p_sys -> iconv_handle = vlc_iconv_open ( "UTF-8" , encoding ) ;
 if ( p_sys -> iconv_handle == ( vlc_iconv_t ) ( - 1 ) ) msg_Err ( p_dec , "cannot convert from %s: %s" , encoding , vlc_strerror_c ( errno ) ) ;
 }
 free ( var ) ;
 p_sys -> i_align = var_InheritInteger ( p_dec , "subsdec-align" ) ;
 return VLC_SUCCESS ;
 }