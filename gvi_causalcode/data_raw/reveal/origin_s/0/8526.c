IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , MixedContentInsecureFaviconBlocked ) {
 net : : EmbeddedTestServer ssl_server ( net : : EmbeddedTestServer : : TYPE_HTTPS ) ;
 ssl_server . AddDefaultHandlers ( base : : FilePath ( kDocRoot ) ) ;
 ASSERT_TRUE ( ssl_server . Start ( ) ) ;
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 const GURL favicon_url = embedded_test_server ( ) -> GetURL ( "example.test" , "/favicon/icon.png" ) ;
 const GURL favicon_page = ssl_server . GetURL ( "example.test" , "/favicon/page_with_favicon_by_url.html?url=" + favicon_url . spec ( ) ) ;
 content : : ConsoleObserverDelegate console_observer ( web_contents ( ) , "*icon.png*" ) ;
 web_contents ( ) -> SetDelegate ( & console_observer ) ;
 std : : unique_ptr < TestResourceDispatcherHostDelegate > delegate ( new TestResourceDispatcherHostDelegate ( favicon_url ) ) ;
 content : : ResourceDispatcherHost : : Get ( ) -> SetDelegate ( delegate . get ( ) ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , favicon_page ) ;
 console_observer . Wait ( ) ;
 waiter . Wait ( ) ;
 EXPECT_TRUE ( base : : MatchPattern ( console_observer . message ( ) , "*insecure favicon*" ) ) ;
 EXPECT_TRUE ( base : : MatchPattern ( console_observer . message ( ) , "*request has been blocked*" ) ) ;
 EXPECT_FALSE ( delegate -> was_requested ( ) ) ;
 }