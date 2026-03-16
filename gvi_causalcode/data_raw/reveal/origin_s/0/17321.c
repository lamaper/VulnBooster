IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestSecureOriginDenyIsSticky ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 EXPECT_TRUE ( content : : IsOriginSecure ( tab_contents -> GetLastCommittedURL ( ) ) ) ;
 GetUserMediaAndDeny ( tab_contents ) ;
 GetUserMediaAndExpectAutoDenyWithoutPrompt ( tab_contents ) ;
 }