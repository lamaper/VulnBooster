IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , DenyingMicDoesNotCauseStickyDenyForCameras ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaWithSpecificConstraintsAndDeny ( tab_contents , kAudioOnlyCallConstraints ) ;
 EXPECT_TRUE ( GetUserMediaWithSpecificConstraintsAndAccept ( tab_contents , kVideoOnlyCallConstraints ) ) ;
 }