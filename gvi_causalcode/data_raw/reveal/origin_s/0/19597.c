IN_PROC_BROWSER_TEST_F ( PrefsFunctionalTest , TestImagesNotBlockedInIncognito ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/settings/image_page.html" ) ;
 Browser * incognito_browser = CreateIncognitoBrowser ( ) ;
 ui_test_utils : : NavigateToURL ( incognito_browser , url ) ;
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
 EXPECT_TRUE ( content : : ExecuteScriptAndExtractBool ( incognito_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) , script , & result ) ) ;
 EXPECT_TRUE ( result ) ;
 }