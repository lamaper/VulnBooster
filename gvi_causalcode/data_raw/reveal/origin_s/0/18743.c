IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_PrivilegedMouseLockAndFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 SetPrivilegedFullscreen ( true ) ;
 FullscreenNotificationObserver fullscreen_observer ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_B , false , true , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 fullscreen_observer . Wait ( ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 }