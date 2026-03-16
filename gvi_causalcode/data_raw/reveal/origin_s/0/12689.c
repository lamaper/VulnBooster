static int svc_log ( SvcContext * svc_ctx , SVC_LOG_LEVEL level , const char * fmt , ... ) {
 char buf [ 512 ] ;
 int retval = 0 ;
 va_list ap ;
 SvcInternal * const si = get_svc_internal ( svc_ctx ) ;
 if ( level > svc_ctx -> log_level ) {
 return retval ;
 }
 va_start ( ap , fmt ) ;
 retval = vsnprintf ( buf , sizeof ( buf ) , fmt , ap ) ;
 va_end ( ap ) ;
 if ( svc_ctx -> log_print ) {
 printf ( "%s" , buf ) ;
 }
 else {
 strncat ( si -> message_buffer , buf , sizeof ( si -> message_buffer ) - strlen ( si -> message_buffer ) - 1 ) ;
 }
 if ( level == SVC_LOG_ERROR ) {
 si -> codec_ctx -> err_detail = si -> message_buffer ;
 }
 return retval ;
 }