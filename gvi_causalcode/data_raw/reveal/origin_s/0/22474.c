IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_FullscreenFileURL ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , ui_test_utils : : GetTestUrl ( base : : FilePath ( base : : FilePath : : kCurrentDirectory ) , base : : FilePath ( kSimpleFile ) ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( false ) ) ;
 }