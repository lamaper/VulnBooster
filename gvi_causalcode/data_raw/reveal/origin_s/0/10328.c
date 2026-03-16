IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , DenyingCameraDoesNotCauseStickyDenyForMics ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaWithSpecificConstraintsAndDeny ( tab_contents , kVideoOnlyCallConstraints ) ;
 EXPECT_TRUE ( GetUserMediaWithSpecificConstraintsAndAccept ( tab_contents , kAudioOnlyCallConstraints ) ) ;
 }