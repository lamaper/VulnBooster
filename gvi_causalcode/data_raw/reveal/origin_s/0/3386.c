static void error_handler ( void * data ) {
 VP9_COMMON * const cm = ( VP9_COMMON * ) data ;
 vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Truncated packet" ) ;
 }