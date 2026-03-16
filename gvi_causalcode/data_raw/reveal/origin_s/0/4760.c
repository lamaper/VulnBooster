IN_PROC_BROWSER_TEST_F ( MediaStreamPermissionTest , TestDenyingThenClearingStickyException ) {
 content : : WebContents * tab_contents = LoadTestPageInTab ( ) ;
 GetUserMediaAndDeny ( tab_contents ) ;
 GetUserMediaAndExpectAutoDenyWithoutPrompt ( tab_contents ) ;
 HostContentSettingsMap * settings_map = HostContentSettingsMapFactory : : GetForProfile ( browser ( ) -> profile ( ) ) ;
 settings_map -> ClearSettingsForOneType ( CONTENT_SETTINGS_TYPE_MEDIASTREAM_MIC ) ;
 settings_map -> ClearSettingsForOneType ( CONTENT_SETTINGS_TYPE_MEDIASTREAM_CAMERA ) ;
 GetUserMediaAndDeny ( tab_contents ) ;
 }