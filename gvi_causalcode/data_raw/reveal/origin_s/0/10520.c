IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestDismissIsNotSticky ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaAndDismiss ( tab_contents ) ;
 GetUserMediaAndDismiss ( tab_contents ) ;
 }