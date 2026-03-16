TEST_F ( FullscreenControllerStateUnitTest , ExitTabFullscreenViaReplacingTab ) {
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_TRUE ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 ASSERT_TRUE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 content : : WebContents * new_web_contents = content : : WebContents : : Create ( content : : WebContents : : CreateParams ( profile ( ) ) ) ;
 scoped_ptr < content : : WebContents > old_web_contents ( browser ( ) -> tab_strip_model ( ) -> ReplaceWebContentsAt ( 0 , new_web_contents ) ) ;
 ChangeWindowFullscreenState ( ) ;
 EXPECT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }