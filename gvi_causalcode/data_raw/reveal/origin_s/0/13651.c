IN_PROC_BROWSER_TEST_F ( VirtualKeyboardBrowserTest , IsKeyboardLoaded ) {
 content : : RenderViewHost * keyboard_rvh = GetKeyboardRenderViewHost ( ) ;
 ASSERT_TRUE ( keyboard_rvh ) ;
 bool loaded = false ;
 std : : string script = "!!chrome.virtualKeyboardPrivate" ;
 EXPECT_TRUE ( content : : ExecuteScriptAndExtractBool ( keyboard_rvh , "window.domAutomationController.send(" + script + ");
" , & loaded ) ) ;
 ASSERT_TRUE ( loaded ) ;
 }