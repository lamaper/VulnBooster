IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , EscapingMouseLock ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 {
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 }
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 SendEscapeToFullscreenController ( ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 {
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 }
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_FALSE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 SendEscapeToFullscreenController ( ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_FALSE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 }