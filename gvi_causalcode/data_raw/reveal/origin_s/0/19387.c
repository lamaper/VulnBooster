IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestSecureOriginAcceptIsSticky ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 EXPECT_TRUE ( content : : IsOriginSecure ( tab_contents -> GetLastCommittedURL ( ) ) ) ;
 EXPECT_TRUE ( GetUserMediaAndAccept ( tab_contents ) ) ;
 GetUserMediaAndExpectAutoAcceptWithoutPrompt ( tab_contents ) ;
 }