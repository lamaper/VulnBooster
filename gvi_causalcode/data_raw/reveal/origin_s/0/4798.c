IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_ReloadExitsMouseLockAndFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 {
 MouseLockNotificationObserver mouselock_observer ;
 Reload ( ) ;
 mouselock_observer . Wait ( ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 }
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 {
 MouseLockNotificationObserver mouselock_observer ;
 Reload ( ) ;
 mouselock_observer . Wait ( ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 }
 {
 FullscreenNotificationObserver fullscreen_observer ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_B , false , true , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 fullscreen_observer . Wait ( ) ;
 }
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 {
 FullscreenNotificationObserver fullscreen_observer ;
 Reload ( ) ;
 fullscreen_observer . Wait ( ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_FALSE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 }
 }