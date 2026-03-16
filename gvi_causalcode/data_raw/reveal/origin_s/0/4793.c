IN_PROC_BROWSER_TEST_F ( MimeHandlerViewTest , SingleRequest ) {
 GURL url ( embedded_test_server ( ) -> GetURL ( "/testBasic.csv" ) ) ;
 URLRequestCounter request_counter ( url ) ;
 RunTest ( "testBasic.csv" ) ;
 EXPECT_EQ ( 1 , request_counter . GetCount ( ) ) ;
 }