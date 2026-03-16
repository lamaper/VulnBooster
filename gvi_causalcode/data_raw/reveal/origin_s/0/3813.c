IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , ReplaceFaviconWithTouchIconViaJavascript ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/page_change_favicon_type_to_touch_icon_via_js.html" ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 waiter . AlsoRequireTitle ( base : : ASCIIToUTF16 ( "OK" ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 EXPECT_EQ ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 }