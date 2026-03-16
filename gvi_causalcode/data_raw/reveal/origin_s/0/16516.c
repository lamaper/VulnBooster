TEST_F ( FullscreenControllerStateUnitTest , ExitTabFullscreenViaDetachingTab ) {
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_TRUE ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 ASSERT_TRUE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 scoped_ptr < content : : WebContents > web_contents ( browser ( ) -> tab_strip_model ( ) -> DetachWebContentsAt ( 0 ) ) ;
 ChangeWindowFullscreenState ( ) ;
 EXPECT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }