IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , ReloadBypassingCache ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/page_with_favicon.html" ) ;
 GURL icon_url = embedded_test_server ( ) -> GetURL ( "/favicon/icon.png" ) ;
 std : : unique_ptr < TestResourceDispatcherHostDelegate > delegate ( new TestResourceDispatcherHostDelegate ( icon_url ) ) ;
 content : : ResourceDispatcherHost : : Get ( ) -> SetDelegate ( delegate . get ( ) ) ;
 {
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 }
 ASSERT_TRUE ( delegate -> was_requested ( ) ) ;
 EXPECT_FALSE ( delegate -> bypassed_cache ( ) ) ;
 delegate -> Reset ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 {
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 }
 EXPECT_FALSE ( delegate -> bypassed_cache ( ) ) ;
 delegate -> Reset ( ) ;
 {
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 chrome : : ExecuteCommand ( browser ( ) , IDC_RELOAD_BYPASSING_CACHE ) ;
 waiter . Wait ( ) ;
 }
 ASSERT_TRUE ( delegate -> was_requested ( ) ) ;
 EXPECT_TRUE ( delegate -> bypassed_cache ( ) ) ;
 }