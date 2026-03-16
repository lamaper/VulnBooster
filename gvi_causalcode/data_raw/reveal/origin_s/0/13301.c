static void update_quantizer_histogram ( struct stream_state * stream ) {
 if ( stream -> config . cfg . g_pass != VPX_RC_FIRST_PASS ) {
 int q ;
 vpx_codec_control ( & stream -> encoder , VP8E_GET_LAST_QUANTIZER_64 , & q ) ;
 ctx_exit_on_error ( & stream -> encoder , "Failed to read quantizer" ) ;
 stream -> counts [ q ] ++ ;
 }
 }