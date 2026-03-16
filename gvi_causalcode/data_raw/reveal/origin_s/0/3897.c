IN_PROC_BROWSER_TEST_F ( FullscreenControllerInteractiveTest , MAYBE_TestTabDoesntExitMouseLockOnSubFrameNavigation ) {
 ASSERT_TRUE ( test_server ( ) -> Start ( ) ) ;
 GURL url ( test_server ( ) -> GetURL ( kFullscreenMouseLockHTML ) ) ;
 GURL url_with_fragment ( url . spec ( ) + "#fragment" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 ASSERT_TRUE ( ui_test_utils : : SendKeyPressAndWait ( browser ( ) , ui : : VKEY_1 , false , false , false , false , chrome : : NOTIFICATION_MOUSE_LOCK_CHANGED , content : : NotificationService : : AllSources ( ) ) ) ;
 ASSERT_TRUE ( IsFullscreenBubbleDisplayed ( ) ) ;
 ASSERT_TRUE ( IsMouseLockPermissionRequested ( ) ) ;
 ASSERT_FALSE ( IsMouseLocked ( ) ) ;
 AcceptCurrentFullscreenOrMouseLockRequest ( ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url_with_fragment ) ;
 ASSERT_TRUE ( IsMouseLocked ( ) ) ;
 }