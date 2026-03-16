char * evhttp_encode_uri ( const char * uri ) {
 struct evbuffer * buf = evbuffer_new ( ) ;
 char * p ;
 for ( p = ( char * ) uri ;
 * p != '\0' ;
 p ++ ) {
 if ( uri_chars [ ( u_char ) ( * p ) ] ) {
 evbuffer_add ( buf , p , 1 ) ;
 }
 else {
 evbuffer_add_printf ( buf , "%%%02X" , ( u_char ) ( * p ) ) ;
 }
 }
 evbuffer_add ( buf , "" , 1 ) ;
 p = strdup ( ( char * ) EVBUFFER_DATA ( buf ) ) ;
 evbuffer_free ( buf ) ;
 return ( p ) ;
 }