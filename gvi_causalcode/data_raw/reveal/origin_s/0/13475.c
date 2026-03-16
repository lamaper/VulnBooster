IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_BrowserFullscreenMouseLockContentSettings ) {
 ASSERT_NO_FATAL_FAILURE ( ToggleBrowserFullscreen ( true ) ) ;
 TestFullscreenMouseLockContentSettings ( ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleBrowserFullscreen ( false ) ) ;
 }