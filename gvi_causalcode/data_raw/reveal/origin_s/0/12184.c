TEST_F ( FullscreenControllerStateUnitTest , DISABLED_ToggleTabWhenPendingBrowser ) {
 if ( FullscreenControllerStateTest : : IsWindowFullscreenStateChangedReentrant ( ) ) return ;
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 ASSERT_NO_FATAL_FAILURE ( TransitionToState ( STATE_TO_BROWSER_FULLSCREEN_NO_CHROME ) ) << GetAndClearDebugLog ( ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_TRUE ) ) << GetAndClearDebugLog ( ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_FALSE ) ) << GetAndClearDebugLog ( ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) << GetAndClearDebugLog ( ) ;
 }