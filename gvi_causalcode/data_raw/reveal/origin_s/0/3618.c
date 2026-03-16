void evhttp_parse_query ( const char * uri , struct evkeyvalq * headers ) {
 char * line ;
 char * argument ;
 char * p ;
 TAILQ_INIT ( headers ) ;
 if ( strchr ( uri , '?' ) == NULL ) return ;
 if ( ( line = strdup ( uri ) ) == NULL ) event_err ( 1 , "%s: strdup" , __func__ ) ;
 argument = line ;
 strsep ( & argument , "?" ) ;
 p = argument ;
 while ( p != NULL && * p != '\0' ) {
 char * key , * value , * decoded_value ;
 argument = strsep ( & p , "&" ) ;
 value = argument ;
 key = strsep ( & value , "=" ) ;
 if ( value == NULL ) goto error ;
 if ( ( decoded_value = malloc ( strlen ( value ) + 1 ) ) == NULL ) event_err ( 1 , "%s: malloc" , __func__ ) ;
 evhttp_decode_uri_internal ( value , strlen ( value ) , decoded_value , 1 ) ;
 event_debug ( ( "Query Param: %s -> %s\n" , key , decoded_value ) ) ;
 evhttp_add_header_internal ( headers , key , decoded_value ) ;
 free ( decoded_value ) ;
 }
 error : free ( line ) ;
 }