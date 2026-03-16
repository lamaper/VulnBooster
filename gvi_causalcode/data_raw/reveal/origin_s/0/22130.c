IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestDenyingUserMedia ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaAndDeny ( tab_contents ) ;
 }