IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestTabExitsFullscreenOnNavigation ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( "about:blank" ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( "chrome:/ewtab" ) ) ;
 ASSERT_FALSE ( browser ( ) -> window ( ) -> IsFullscreen ( ) ) ;
 }