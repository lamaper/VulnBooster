static int evhttp_parse_response_line ( struct evhttp_request * req , char * line ) {
 char * protocol ;
 char * number ;
 char * readable ;
 protocol = strsep ( & line , " " ) ;
 if ( line == NULL ) return ( - 1 ) ;
 number = strsep ( & line , " " ) ;
 if ( line == NULL ) return ( - 1 ) ;
 readable = line ;
 if ( strcmp ( protocol , "HTTP/1.0" ) == 0 ) {
 req -> major = 1 ;
 req -> minor = 0 ;
 }
 else if ( strcmp ( protocol , "HTTP/1.1" ) == 0 ) {
 req -> major = 1 ;
 req -> minor = 1 ;
 }
 else {
 event_debug ( ( "%s: bad protocol \"%s\"" , __func__ , protocol ) ) ;
 return ( - 1 ) ;
 }
 req -> response_code = atoi ( number ) ;
 if ( ! evhttp_valid_response_code ( req -> response_code ) ) {
 event_debug ( ( "%s: bad response code \"%s\"" , __func__ , number ) ) ;
 return ( - 1 ) ;
 }
 if ( ( req -> response_code_line = strdup ( readable ) ) == NULL ) event_err ( 1 , "%s: strdup" , __func__ ) ;
 return ( 0 ) ;
 }