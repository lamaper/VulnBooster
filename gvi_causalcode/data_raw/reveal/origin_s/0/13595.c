IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , LoadIconFromWebManifest ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/page_with_manifest.html" ) ;
 GURL icon_url = embedded_test_server ( ) -> GetURL ( "/favicon/icon.png" ) ;
 std : : unique_ptr < TestResourceDispatcherHostDelegate > delegate ( new TestResourceDispatcherHostDelegate ( icon_url ) ) ;
 content : : ResourceDispatcherHost : : Get ( ) -> SetDelegate ( delegate . get ( ) ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;

 EXPECT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kWebManifestIcon ) . bitmap_data ) ;

