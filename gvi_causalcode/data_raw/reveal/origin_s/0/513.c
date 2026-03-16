TEST_F ( FullscreenControllerStateUnitTest , ExitTabFullscreenViaSwitchingTab ) {
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_TRUE ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 ASSERT_TRUE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 browser ( ) -> tab_strip_model ( ) -> SelectNextTab ( ) ;
 ChangeWindowFullscreenState ( ) ;
 EXPECT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }