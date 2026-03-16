void evhttp_send_error ( struct evhttp_request * req , int error , const char * reason ) {

 evhttp_add_header ( req -> output_headers , "Connection" , "close" ) ;
 evhttp_response_code ( req , error , reason ) ;
 evbuffer_add_printf ( buf , ERR_FORMAT , error , reason ) ;
 evhttp_send_page ( req , buf ) ;
 evbuffer_free ( buf ) ;
