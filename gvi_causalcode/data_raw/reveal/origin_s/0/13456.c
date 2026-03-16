IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestDismissingRequest ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaAndDismiss ( tab_contents ) ;
 }