IN_PROC_BROWSER_TEST_F ( ContentFaviconDriverTest , DoNotRemoveMappingIfStopped ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/favicon/slow_page_with_favicon.html" ) ;
 GURL icon_url = embedded_test_server ( ) -> GetURL ( "/favicon/icon.png" ) ;
 GURL default_icon_url = embedded_test_server ( ) -> GetURL ( "/favicon.ico" ) ;
 favicon_service ( ) -> SetFavicons ( {
 url }
 , icon_url , favicon_base : : IconType : : kFavicon , gfx : : test : : CreateImage ( 32 , 32 ) ) ;
 ASSERT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 PageLoadStopper stopper ( web_contents ( ) ) ;
 stopper . StopOnDidFinishNavigation ( ) ;
 PendingTaskWaiter waiter ( web_contents ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , url , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ;
 waiter . Wait ( ) ;
 ASSERT_THAT ( stopper . last_favicon_candidates ( ) , ElementsAre ( default_icon_url ) ) ;
 EXPECT_NE ( nullptr , GetFaviconForPageURL ( url , favicon_base : : IconType : : kFavicon ) . bitmap_data ) ;
 }