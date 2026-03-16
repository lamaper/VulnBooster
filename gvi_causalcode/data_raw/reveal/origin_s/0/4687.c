IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestAllowingUserMedia ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 EXPECT_TRUE ( GetUserMediaAndAccept ( tab_contents ) ) ;
 }