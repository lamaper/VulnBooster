IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestFullscreenFromTabWhenAlreadyInBrowserFullscreenWorks ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( "about:blank" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( "chrome:/ewtab" ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleBrowserFullscreen ( true ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 GoBack ( ) ;
 ASSERT_TRUE ( IsFullscreenForBrowser ( ) ) ;
 ASSERT_FALSE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 }