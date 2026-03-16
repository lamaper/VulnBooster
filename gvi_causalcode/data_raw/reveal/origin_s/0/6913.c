static struct evhttp_cb * evhttp_dispatch_callback ( struct httpcbq * callbacks , struct evhttp_request * req ) {
 struct evhttp_cb * cb ;
 size_t offset = 0 ;
 char * p = strchr ( req -> uri , '?' ) ;
 if ( p != NULL ) offset = ( size_t ) ( p - req -> uri ) ;
 TAILQ_FOREACH ( cb , callbacks , next ) {
 int res = 0 ;
 if ( p == NULL ) {
 res = strcmp ( cb -> what , req -> uri ) == 0 ;
 }
 else {
 res = ( ( strncmp ( cb -> what , req -> uri , offset ) == 0 ) && ( cb -> what [ offset ] == '\0' ) ) ;
 }
 if ( res ) return ( cb ) ;
 }
 return ( NULL ) ;
 }