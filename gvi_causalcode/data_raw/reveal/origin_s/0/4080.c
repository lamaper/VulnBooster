IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , MixedContentSecureFaviconAllowed ) {
 net : : EmbeddedTestServer ssl_server ( net : : EmbeddedTestServer : : TYPE_HTTPS ) ;
 ssl_server . AddDefaultHandlers ( base : : FilePath ( kDocRoot ) ) ;
 ASSERT_TRUE ( ssl_server . Start ( ) ) ;
 const GURL favicon_url = ssl_server . GetURL ( "example.test" , "/favicon/icon.png" ) ;
 const GURL favicon_page = ssl_server . GetURL ( "example.test" , "/favicon/page_with_favicon_by_url.html?url=" + favicon_url . spec ( ) ) ;
 std : : unique_ptr < TestResourceDispatcherHostDelegate > delegate ( new TestResourceDispatcherHostDelegate ( favicon_url ) ) ;
 content : : ResourceDispatcherHost : : Get ( ) -> SetDelegate ( delegate . get ( ) ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , favicon_page ) ;
 waiter . Wait ( ) ;
 EXPECT_TRUE ( delegate -> was_requested ( ) ) ;
 }