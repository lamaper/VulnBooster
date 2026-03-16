IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestTabDoesntExitFullscreenOnSubFrameNavigation ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 GURL url ( ui_test_utils : : GetTestUrl ( base : : FilePath ( base : : FilePath : : kCurrentDirectory ) , base : : FilePath ( kSimpleFile ) ) ) ;
 GURL url_with_fragment ( url . spec ( ) + "#fragment" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url_with_fragment ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 }