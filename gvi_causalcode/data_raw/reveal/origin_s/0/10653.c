IN_PROC_BROWSER_TEST_F ( SitePerProcessInteractiveBrowserTest , SubframeKeyboardEventRouting ) {
 GURL main_url ( embedded_test_server ( ) -> GetURL ( "a.com" , "/frame_tree/page_with_one_frame.html" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , main_url ) ;
 content : : WebContents * web_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 GURL frame_url ( embedded_test_server ( ) -> GetURL ( "b.com" , "/page_with_input_field.html" ) ) ;
 EXPECT_TRUE ( NavigateIframeToURL ( web_contents , "child0" , frame_url ) ) ;
 content : : RenderFrameHost * child = ChildFrameAt ( web_contents -> GetMainFrame ( ) , 0 ) ;
 std : : string result ;
 std : : string script = "function onInput(e) {
" " domAutomationController.setAutomationId(0);
" " domAutomationController.send(getInputFieldText());
" "}
" "inputField = document.getElementById('text-field');
" "inputField.addEventListener('input', onInput, false);
" ;
 EXPECT_TRUE ( ExecuteScript ( child , script ) ) ;
 EXPECT_TRUE ( ExecuteScriptAndExtractString ( child , "window.focus();
 focusInputField();
" , & result ) ) ;
 EXPECT_EQ ( "input-focus" , result ) ;
 EXPECT_EQ ( child , web_contents -> GetFocusedFrame ( ) ) ;
 content : : DOMMessageQueue msg_queue ;
 std : : string reply ;
 SimulateKeyPress ( web_contents , ui : : DomKey : : FromCharacter ( 'f' ) , ui : : DomCode : : US_F , ui : : VKEY_F , false , false , false , false ) ;
 EXPECT_TRUE ( msg_queue . WaitForMessage ( & reply ) ) ;
 EXPECT_EQ ( "\"F\"" , reply ) ;
 SimulateKeyPress ( web_contents , ui : : DomKey : : FromCharacter ( 'O' ) , ui : : DomCode : : US_O , ui : : VKEY_O , false , false , false , false ) ;
 EXPECT_TRUE ( msg_queue . WaitForMessage ( & reply ) ) ;
 EXPECT_EQ ( "\"FO\"" , reply ) ;
 SimulateKeyPress ( web_contents , ui : : DomKey : : FromCharacter ( 'O' ) , ui : : DomCode : : US_O , ui : : VKEY_O , false , false , false , false ) ;
 EXPECT_TRUE ( msg_queue . WaitForMessage ( & reply ) ) ;
 EXPECT_EQ ( "\"FOO\"" , reply ) ;
 }