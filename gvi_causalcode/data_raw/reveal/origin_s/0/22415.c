static void print_http_error ( struct Curl_easy * data ) {
 struct SingleRequest * k = & data -> req ;
 char * beg = k -> p ;
 if ( ! strncmp ( beg , "HTTP" , 4 ) ) {
 beg = strchr ( beg , ' ' ) ;
 if ( beg && * ++ beg ) {
 char end_char = '\r' ;
 char * end = strchr ( beg , end_char ) ;
 if ( ! end ) {
 end_char = '\n' ;
 end = strchr ( beg , end_char ) ;
 }
 if ( end ) {
 * end = '\0' ;
 failf ( data , "The requested URL returned error: %s" , beg ) ;
 * end = end_char ;
 return ;
 }
 }
 }
 failf ( data , "The requested URL returned error: %d" , k -> httpcode ) ;
 }