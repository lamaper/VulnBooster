IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , AssociateIconWithInitialPageDespite300ResponseAndMetaRefreshTag ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url_with_meta_refresh_tag = embedded_test_server ( ) -> GetURL ( "/favicon/page_with_meta_refresh_tag.html" ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/server-redirect?" + url_with_meta_refresh_tag . spec ( ) ) ;
 GURL landing_url = embedded_test_server ( ) -> GetURL ( "/favicon/page_with_favicon.html" ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 waiter . AlsoRequireUrl ( landing_url ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( landing_url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 }