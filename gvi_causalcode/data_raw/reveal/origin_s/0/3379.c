IN_PROC_BROWSER_TEST_F ( SitePerProcessInteractiveBrowserTest , SequentialFocusNavigation ) {
 GURL main_url ( embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?a(b,c)" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , main_url ) ;
 content : : WebContents * web_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : RenderFrameHost * main_frame = web_contents -> GetMainFrame ( ) ;
 content : : RenderFrameHost * child1 = ChildFrameAt ( main_frame , 0 ) ;
 ASSERT_NE ( nullptr , child1 ) ;
 content : : RenderFrameHost * child2 = ChildFrameAt ( main_frame , 1 ) ;
 ASSERT_NE ( nullptr , child2 ) ;
 EXPECT_TRUE ( ExecuteScript ( main_frame , "window.name = 'root';
" ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child1 , "window.name = 'child1';
" ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child2 , "window.name = 'child2';
" ) ) ;
 std : : string script = "function onFocus(e) {
" " domAutomationController.setAutomationId(0);
" " domAutomationController.send(window.name + '-focused-' + e.target.id);
" "}
" "var input1 = document.createElement('input');
" "input1.id = 'input1';
" "var input2 = document.createElement('input');
" "input2.id = 'input2';
" "document.body.insertBefore(input1, document.body.firstChild);
" "document.body.appendChild(input2);
" "input1.addEventListener('focus', onFocus, false);
" "input2.addEventListener('focus', onFocus, false);
" ;
 EXPECT_TRUE ( ExecuteScript ( main_frame , script ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child1 , script ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child2 , script ) ) ;
 auto press_tab_and_wait_for_message = [ web_contents ] ( bool reverse ) {
 content : : DOMMessageQueue msg_queue ;
 std : : string reply ;
 SimulateKeyPress ( web_contents , ui : : DomKey : : TAB , ui : : DomCode : : TAB , ui : : VKEY_TAB , false , reverse , false , false ) ;
 EXPECT_TRUE ( msg_queue . WaitForMessage ( & reply ) ) ;
 return reply ;
 }
 ;
 EXPECT_EQ ( "\"root-focused-input1\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( main_frame , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child1-focused-input1\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( child1 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child1-focused-input2\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( "\"child2-focused-input1\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( child2 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child2-focused-input2\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( "\"root-focused-input2\"" , press_tab_and_wait_for_message ( false ) ) ;
 EXPECT_EQ ( main_frame , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child2-focused-input2\"" , press_tab_and_wait_for_message ( true ) ) ;
 EXPECT_EQ ( child2 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child2-focused-input1\"" , press_tab_and_wait_for_message ( true ) ) ;
 EXPECT_EQ ( "\"child1-focused-input2\"" , press_tab_and_wait_for_message ( true ) ) ;
 EXPECT_EQ ( child1 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_EQ ( "\"child1-focused-input1\"" , press_tab_and_wait_for_message ( true ) ) ;
 EXPECT_EQ ( "\"root-focused-input1\"" , press_tab_and_wait_for_message ( true ) ) ;
 EXPECT_EQ ( main_frame , web_contents -> GetFocusedFrame ( ) ) ;
 }