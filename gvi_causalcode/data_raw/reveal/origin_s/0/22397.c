IN_PROC_BROWSER_TEST_F ( VirtualKeyboardBrowserTest , EndToEndTest ) {
 content : : RenderViewHost * keyboard_rvh = GetKeyboardRenderViewHost ( ) ;
 ASSERT_TRUE ( keyboard_rvh ) ;
 content : : RenderViewHost * browser_rvh = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetRenderViewHost ( ) ;
 ASSERT_TRUE ( browser_rvh ) ;
 GURL url = ui_test_utils : : GetTestUrl ( base : : FilePath ( ) , base : : FilePath ( FILE_PATH_LITERAL ( "chromeos/virtual_keyboard/end_to_end_test.html" ) ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 base : : FilePath path = ui_test_utils : : GetTestFilePath ( kVirtualKeyboardTestDir , base : : FilePath ( FILE_PATH_LITERAL ( "end_to_end_test.js" ) ) ) ;
 std : : string script ;
 ASSERT_TRUE ( base : : ReadFileToString ( path , & script ) ) ;
 EXPECT_TRUE ( content : : ExecuteScript ( keyboard_rvh , script ) ) ;
 bool success = false ;
 EXPECT_TRUE ( content : : ExecuteScriptAndExtractBool ( browser_rvh , "success ? verifyInput('a') : waitForInput('a');
" , & success ) ) ;
 ASSERT_TRUE ( success ) ;
 }