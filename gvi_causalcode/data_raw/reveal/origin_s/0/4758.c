static void CloseDecoder ( vlc_object_t * p_this ) {
 decoder_t * p_dec = ( decoder_t * ) p_this ;
 decoder_sys_t * p_sys = p_dec -> p_sys ;
 if ( p_sys -> iconv_handle != ( vlc_iconv_t ) - 1 ) vlc_iconv_close ( p_sys -> iconv_handle ) ;
 free ( p_sys ) ;
 }