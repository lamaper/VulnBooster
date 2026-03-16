IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestDenyingUserMediaIncognito ) {
 content : : WebContents * tab_contents = LoadTestPageInIncognitoTab ( ) ;
 GetUserMediaAndDeny ( tab_contents ) ;
 }