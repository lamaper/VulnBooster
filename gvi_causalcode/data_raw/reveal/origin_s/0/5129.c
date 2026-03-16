static void warn_or_exit_on_errorv ( vpx_codec_ctx_t * ctx , int fatal , const char * s , va_list ap ) {
 if ( ctx -> err ) {
 const char * detail = vpx_codec_error_detail ( ctx ) ;
 vfprintf ( stderr , s , ap ) ;
 fprintf ( stderr , ": %s\n" , vpx_codec_error ( ctx ) ) ;
 if ( detail ) fprintf ( stderr , " %s\n" , detail ) ;
 if ( fatal ) exit ( EXIT_FAILURE ) ;
 }
 }