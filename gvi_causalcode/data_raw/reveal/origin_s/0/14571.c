char * evhttp_decode_uri ( const char * uri ) {
 char * ret ;
 if ( ( ret = malloc ( strlen ( uri ) + 1 ) ) == NULL ) event_err ( 1 , "%s: malloc(%lu)" , __func__ , ( unsigned long ) ( strlen ( uri ) + 1 ) ) ;
 evhttp_decode_uri_internal ( uri , strlen ( uri ) , ret , 0 ) ;
 return ( ret ) ;
 }