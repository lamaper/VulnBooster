IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_MouseLockAndFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 {
 FullscreenNotificationObserver fullscreen_observer ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_B , false , true , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 fullscreen_observer . Wait ( ) ;
 }
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_TRUE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 {
 FullscreenNotificationObserver fullscreen_observer ;
 DenyCurrentFullscreenOrMouseLockRequest ( ) ;
 fullscreen_observer . Wait ( ) ;
 }
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_FALSE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 {
 FullscreenNotificationObserver fullscreen_observer ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_B , false , true , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 fullscreen_observer . Wait ( ) ;
 }
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_TRUE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 }