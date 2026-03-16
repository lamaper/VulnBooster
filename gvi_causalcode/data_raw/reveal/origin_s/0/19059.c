static void svc_log_reset ( SvcContext * svc_ctx ) {
 SvcInternal * const si = ( SvcInternal * ) svc_ctx -> internal ;
 si -> message_buffer [ 0 ] = '\0' ;
 }