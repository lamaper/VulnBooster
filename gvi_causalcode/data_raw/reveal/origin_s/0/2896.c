IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestImageContentSettings ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/settings/image_page.html" ) ) ;
 bool result = false ;
 std : : string script = "for (i=0;
 i < document.images.length;
 i++) {
" " if ((document.images[i].naturalWidth != 0) &&" " (document.images[i].naturalHeight != 0)) {
" " window.domAutomationController.send(true);
" " }
" "}
" "window.domAutomationController.send(false);
" ;
 EXPECT_TRUE ( content : : ExecuteScriptAndExtractBool ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , script , & result ) ) ;
 EXPECT_TRUE ( result ) ;
 browser ( ) -> profile ( ) -> GetPrefs ( ) -> SetInteger ( content_settings : : WebsiteSettingsRegistry : : GetInstance ( ) -> Get ( CONTENT_SETTINGS_TYPE_IMAGES ) -> default_value_pref_name ( ) , CONTENT_SETTING_BLOCK ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/settings/image_page.html" ) ) ;
 result = false ;
 EXPECT_TRUE ( content : : ExecuteScriptAndExtractBool ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , script , & result ) ) ;
 EXPECT_FALSE ( result ) ;
 }