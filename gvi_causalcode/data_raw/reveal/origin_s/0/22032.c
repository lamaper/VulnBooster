static void http_parse_query_test ( void ) {
 struct evkeyvalq headers ;
 fprintf ( stdout , "Testing HTTP query parsing: " ) ;
 TAILQ_INIT ( & headers ) ;
 evhttp_parse_query ( "http://www.test.com/?q=test" , & headers ) ;
 if ( validate_header ( & headers , "q" , "test" ) != 0 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 evhttp_parse_query ( "http://www.test.com/?q=test&foo=bar" , & headers ) ;
 if ( validate_header ( & headers , "q" , "test" ) != 0 ) goto fail ;
 if ( validate_header ( & headers , "foo" , "bar" ) != 0 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 evhttp_parse_query ( "http://www.test.com/?q=test+foo" , & headers ) ;
 if ( validate_header ( & headers , "q" , "test foo" ) != 0 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 evhttp_parse_query ( "http://www.test.com/?q=test%0Afoo" , & headers ) ;
 if ( validate_header ( & headers , "q" , "test\nfoo" ) != 0 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 evhttp_parse_query ( "http://www.test.com/?q=test%0Dfoo" , & headers ) ;
 if ( validate_header ( & headers , "q" , "test\rfoo" ) != 0 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 fprintf ( stdout , "OK\n" ) ;
 return ;
 fail : fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }