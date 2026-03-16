CURLcode Curl_add_custom_headers ( struct connectdata * conn , bool is_connect , Curl_send_buffer * req_buffer ) {
 char * ptr ;
 struct curl_slist * h [ 2 ] ;
 struct curl_slist * headers ;
 int numlists = 1 ;
 struct Curl_easy * data = conn -> data ;
 int i ;
 enum proxy_use proxy ;
 if ( is_connect ) proxy = HEADER_CONNECT ;
 else proxy = conn -> bits . httpproxy && ! conn -> bits . tunnel_proxy ? HEADER_PROXY : HEADER_SERVER ;
 switch ( proxy ) {
 case HEADER_SERVER : h [ 0 ] = data -> set . headers ;
 break ;
 case HEADER_PROXY : h [ 0 ] = data -> set . headers ;
 if ( data -> set . sep_headers ) {
 h [ 1 ] = data -> set . proxyheaders ;
 numlists ++ ;
 }
 break ;
 case HEADER_CONNECT : if ( data -> set . sep_headers ) h [ 0 ] = data -> set . proxyheaders ;
 else h [ 0 ] = data -> set . headers ;
 break ;
 }
 for ( i = 0 ;
 i < numlists ;
 i ++ ) {
 headers = h [ i ] ;
 while ( headers ) {
 ptr = strchr ( headers -> data , ':' ) ;
 if ( ptr ) {
 ptr ++ ;
 while ( * ptr && ISSPACE ( * ptr ) ) ptr ++ ;
 if ( * ptr ) {
 if ( conn -> allocptr . host && checkprefix ( "Host:" , headers -> data ) ) ;
 else if ( data -> set . httpreq == HTTPREQ_POST_FORM && checkprefix ( "Content-Type:" , headers -> data ) ) ;
 else if ( conn -> bits . authneg && checkprefix ( "Content-Length" , headers -> data ) ) ;
 else if ( conn -> allocptr . te && checkprefix ( "Connection" , headers -> data ) ) ;
 else if ( ( conn -> httpversion == 20 ) && checkprefix ( "Transfer-Encoding:" , headers -> data ) ) ;
 else {
 CURLcode result = Curl_add_bufferf ( req_buffer , "%s\r\n" , headers -> data ) ;
 if ( result ) return result ;
 }
 }
 }
 else {
 ptr = strchr ( headers -> data , ';
' ) ;
 if ( ptr ) {
 ptr ++ ;
 while ( * ptr && ISSPACE ( * ptr ) ) ptr ++ ;
 if ( * ptr ) {
 }
 else {
 if ( * ( -- ptr ) == ';
' ) {
 CURLcode result ;
 * ptr = ':' ;
 result = Curl_add_bufferf ( req_buffer , "%s\r\n" , headers -> data ) ;
 if ( result ) return result ;
 }
 }
 }
 }
 headers = headers -> next ;
 }
 }
 return CURLE_OK ;
 }