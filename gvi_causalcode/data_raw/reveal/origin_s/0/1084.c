IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , DISABLED_MouseLockThenFullscreen ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_D , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_FALSE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayingButtons ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ToggleTabFullscreen ( true ) ) ;
 ASSERT_TRUE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_TRUE ( IsFullscreenPermissionRequested ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ASSERT_TRUE ( IsWindowFullscreenForTabOrPending ( ) ) ;
 ASSERT_FALSE ( IsFullscreenBubbleDisplayingButtons ( ) ) ;
 }