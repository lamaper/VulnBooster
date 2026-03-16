IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestNewTabExitsFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 {
 FullscreenNotificationObserver fullscreen_observer ;
 AddTabAtIndex ( 1 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 fullscreen_observer . Wait ( ) ;
 ASSERT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }
 }