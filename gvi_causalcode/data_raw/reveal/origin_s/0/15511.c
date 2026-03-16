int evhttp_hostportfile ( char * url , char * * phost , u_short * pport , char * * pfile ) {
 static char host [ 1024 ] ;
 static char file [ 1024 ] ;
 char * p ;
 const char * p2 ;
 int len ;
 u_short port ;
 len = strlen ( HTTP_PREFIX ) ;
 if ( strncasecmp ( url , HTTP_PREFIX , len ) ) return ( - 1 ) ;
 url += len ;
 if ( strlcpy ( host , url , sizeof ( host ) ) >= sizeof ( host ) ) return ( - 1 ) ;
 p = strchr ( host , '/' ) ;
 if ( p != NULL ) {
 * p = '\0' ;
 p2 = p + 1 ;
 }
 else p2 = NULL ;
 if ( pfile != NULL ) {
 if ( p2 == NULL ) p2 = "" ;
 evutil_snprintf ( file , sizeof ( file ) , "/%s" , p2 ) ;
 }
 p = strchr ( host , ':' ) ;
 if ( p != NULL ) {
 * p = '\0' ;
 port = atoi ( p + 1 ) ;
 if ( port == 0 ) return ( - 1 ) ;
 }
 else port = HTTP_DEFAULTPORT ;
 if ( phost != NULL ) * phost = host ;
 if ( pport != NULL ) * pport = port ;
 if ( pfile != NULL ) * pfile = file ;
 return ( 0 ) ;
 }