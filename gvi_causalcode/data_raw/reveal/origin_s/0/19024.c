static size_t qio_channel_websock_extract_headers ( QIOChannelWebsock * ioc , char * buffer , QIOChannelWebsockHTTPHeader * hdrs , size_t nhdrsalloc , Error * * errp ) {
 char * nl , * sep , * tmp ;
 size_t nhdrs = 0 ;
 nl = strstr ( buffer , QIO_CHANNEL_WEBSOCK_HANDSHAKE_DELIM ) ;
 if ( ! nl ) {
 error_setg ( errp , "Missing HTTP header delimiter" ) ;
 goto bad_request ;
 }
 * nl = '\0' ;
 tmp = strchr ( buffer , ' ' ) ;
 if ( ! tmp ) {
 error_setg ( errp , "Missing HTTP path delimiter" ) ;
 return 0 ;
 }
 * tmp = '\0' ;
 if ( ! g_str_equal ( buffer , QIO_CHANNEL_WEBSOCK_HTTP_METHOD ) ) {
 error_setg ( errp , "Unsupported HTTP method %s" , buffer ) ;
 goto bad_request ;
 }
 buffer = tmp + 1 ;
 tmp = strchr ( buffer , ' ' ) ;
 if ( ! tmp ) {
 error_setg ( errp , "Missing HTTP version delimiter" ) ;
 goto bad_request ;
 }
 * tmp = '\0' ;
 if ( ! g_str_equal ( buffer , QIO_CHANNEL_WEBSOCK_HTTP_PATH ) ) {
 qio_channel_websock_handshake_send_res_err ( ioc , QIO_CHANNEL_WEBSOCK_HANDSHAKE_RES_NOT_FOUND ) ;
 error_setg ( errp , "Unexpected HTTP path %s" , buffer ) ;
 return 0 ;
 }
 buffer = tmp + 1 ;
 if ( ! g_str_equal ( buffer , QIO_CHANNEL_WEBSOCK_HTTP_VERSION ) ) {
 error_setg ( errp , "Unsupported HTTP version %s" , buffer ) ;
 goto bad_request ;
 }
 buffer = nl + strlen ( QIO_CHANNEL_WEBSOCK_HANDSHAKE_DELIM ) ;
 do {
 QIOChannelWebsockHTTPHeader * hdr ;
 nl = strstr ( buffer , QIO_CHANNEL_WEBSOCK_HANDSHAKE_DELIM ) ;
 if ( nl ) {
 * nl = '\0' ;
 }
 sep = strchr ( buffer , ':' ) ;
 if ( ! sep ) {
 error_setg ( errp , "Malformed HTTP header" ) ;
 goto bad_request ;
 }
 * sep = '\0' ;
 sep ++ ;
 while ( * sep == ' ' ) {
 sep ++ ;
 }
 if ( nhdrs >= nhdrsalloc ) {
 error_setg ( errp , "Too many HTTP headers" ) ;
 goto bad_request ;
 }
 hdr = & hdrs [ nhdrs ++ ] ;
 hdr -> name = buffer ;
 hdr -> value = sep ;
 for ( tmp = hdr -> name ;
 * tmp ;
 tmp ++ ) {
 * tmp = g_ascii_tolower ( * tmp ) ;
 }
 if ( nl ) {
 buffer = nl + strlen ( QIO_CHANNEL_WEBSOCK_HANDSHAKE_DELIM ) ;
 }
 }
 while ( nl != NULL ) ;
 return nhdrs ;
 bad_request : qio_channel_websock_handshake_send_res_err ( ioc , QIO_CHANNEL_WEBSOCK_HANDSHAKE_RES_BAD_REQUEST ) ;
 return 0 ;
 }