static void qio_channel_websock_handshake_send_res ( QIOChannelWebsock * ioc , const char * resmsg , ... ) {
 va_list vargs ;
 char * response ;
 size_t responselen ;
 va_start ( vargs , resmsg ) ;
 response = g_strdup_vprintf ( resmsg , vargs ) ;
 responselen = strlen ( response ) ;
 buffer_reserve ( & ioc -> encoutput , responselen ) ;
 buffer_append ( & ioc -> encoutput , response , responselen ) ;
 va_end ( vargs ) ;
 }