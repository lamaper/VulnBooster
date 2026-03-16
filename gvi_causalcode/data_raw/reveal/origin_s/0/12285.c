IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_BrowserFullscreenExit ) {
 ASSERT_NO_FATAL_FAILURE ( ToggleBrowserFullscreen ( true ) ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleBrowserFullscreen ( false ) ) ;
 ASSERT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }