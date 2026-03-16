IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestTabExitsItselfFromFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( false ) ) ;
 }