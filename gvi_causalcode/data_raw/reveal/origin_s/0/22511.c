static void ctx_exit_on_error ( vpx_codec_ctx_t * ctx , const char * s , ... ) {
 va_list ap ;
 va_start ( ap , s ) ;
 warn_or_exit_on_errorv ( ctx , 1 , s , ap ) ;
 va_end ( ap ) ;
 }