void evhttp_send_page ( struct evhttp_request * req , struct evbuffer * databuf ) {
 if ( ! req -> major || ! req -> minor ) {
 req -> major = 1 ;
 req -> minor = 1 ;
 }
 if ( req -> kind != EVHTTP_RESPONSE ) evhttp_response_code ( req , 200 , "OK" ) ;
 evhttp_clear_headers ( req -> output_headers ) ;
 evhttp_add_header ( req -> output_headers , "Content-Type" , "text/html" ) ;
 evhttp_add_header ( req -> output_headers , "Connection" , "close" ) ;
 evhttp_send ( req , databuf ) ;
 }