IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , MAYBE_TestSessionRestore ) {
 EXPECT_EQ ( 2 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( GURL ( chrome : : kChromeUIVersionURL ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> GetURL ( ) ) ;
 EXPECT_EQ ( GURL ( "about:blank" ) , browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetURL ( ) ) ;
 }