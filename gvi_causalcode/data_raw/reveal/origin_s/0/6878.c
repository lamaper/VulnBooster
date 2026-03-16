IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , AssociateIconWithInitialPageIconDespiteReplaceState ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/replacestate_with_favicon.html" ) ;
 GURL replacestate_url = embedded_test_server ( ) -> GetURL ( "/favicon/replacestate_with_favicon_replaced.html" ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 waiter . AlsoRequireUrl ( replacestate_url ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( replacestate_url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 }