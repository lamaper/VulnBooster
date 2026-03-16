IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , AssociateIconWithInitialPageIconDespitePushState ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/pushstate_with_favicon.html" ) ;
 GURL pushstate_url = embedded_test_server ( ) -> GetURL ( "/favicon/pushstate_with_favicon_pushed.html" ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 waiter . AlsoRequireUrl ( pushstate_url ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( pushstate_url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 }