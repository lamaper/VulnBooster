static void http_bad_header_test ( void ) {
 struct evkeyvalq headers ;
 fprintf ( stdout , "Testing HTTP Header filtering: " ) ;
 TAILQ_INIT ( & headers ) ;
 if ( evhttp_add_header ( & headers , "One" , "Two" ) != 0 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One\r" , "Two" ) != - 1 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One" , "Two" ) != 0 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One" , "Two\r\n Three" ) != 0 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One\r" , "Two" ) != - 1 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One\n" , "Two" ) != - 1 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One" , "Two\r" ) != - 1 ) goto fail ;
 if ( evhttp_add_header ( & headers , "One" , "Two\n" ) != - 1 ) goto fail ;
 evhttp_clear_headers ( & headers ) ;
 fprintf ( stdout , "OK\n" ) ;
 return ;
 fail : fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }