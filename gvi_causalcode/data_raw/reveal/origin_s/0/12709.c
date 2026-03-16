IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_TestFullscreenBubbleMouseLockState ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 AddTabAtIndex ( 0 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 AddTabAtIndex ( 1 , GURL ( url : : kAboutBlankURL ) , PAGE_TRANSITION_TYPED ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 RequestToLockMouse ( true , false ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayingButtons ( ) ) ;
 }