IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_ToggleFullscreenModeForTab ) {
 GURL url = test_server ( ) -> GetURL ( "simple.html" ) ;
 AddTabAtIndex ( 0 , url , PAGE_TRANSITION_TYPED ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreenNoRetries ( true ) ) ;
 ASSERT_TRUE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreenNoRetries ( false ) ) ;
 }