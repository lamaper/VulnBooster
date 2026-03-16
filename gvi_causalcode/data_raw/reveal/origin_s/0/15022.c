IN_PROC_BROWSER_TEST_F ( RegisterProtocolHandlerBrowserTest , CustomHandler ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 GURL handler_url = test_server ( ) -> GetURL ( "files/custom_handler_foo.html" ) ;
 AddProtocolHandler ( "foo" , handler_url ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( "foo:test" ) ) ;
 ASSERT_EQ ( handler_url , browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetURL ( ) ) ;
 }