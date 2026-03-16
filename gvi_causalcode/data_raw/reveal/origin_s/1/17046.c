void http_suite ( void ) {
 http_base_test ( ) ;
 http_bad_header_test ( ) ;
 http_parse_query_test ( ) ;
 http_basic_test ( ) ;
 http_connection_test ( 0 ) ;
 http_connection_test ( 1 ) ;
 http_close_detection ( 0 ) ;
 http_close_detection ( 1 ) ;
 http_post_test ( ) ;
 http_failure_test ( ) ;
 http_highport_test ( ) ;
 http_dispatcher_test ( ) ;
 http_multi_line_header_test ( ) ;
 http_negative_content_length_test ( ) ;
 http_chunked_test ( ) ;
 }