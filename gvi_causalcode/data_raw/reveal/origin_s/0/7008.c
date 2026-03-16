TEST_F ( FullscreenControllerStateUnitTest , ExitFullscreenViaBrowserWindow ) {
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TOGGLE_FULLSCREEN ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 ASSERT_TRUE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 browser ( ) -> window ( ) -> ExitFullscreen ( ) ;
 ChangeWindowFullscreenState ( ) ;
 EXPECT_EQ ( EXCLUSIVE_ACCESS_BUBBLE_TYPE_NONE , browser ( ) -> fullscreen_controller ( ) -> GetExclusiveAccessBubbleType ( ) ) ;
 }