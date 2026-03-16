IN_PROC_BROWSER_TEST_F ( SitePerProcessInteractiveBrowserTest , DocumentHasFocus ) {
 GURL main_url ( embedded_test_server ( ) -> GetURL ( "a.com" , "/cross_site_iframe_factory.html?a(b(c),d)" ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , main_url ) ;
 content : : WebContents * web_contents = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 content : : RenderFrameHost * main_frame = web_contents -> GetMainFrame ( ) ;
 content : : RenderFrameHost * child1 = ChildFrameAt ( main_frame , 0 ) ;
 ASSERT_NE ( nullptr , child1 ) ;
 content : : RenderFrameHost * child2 = ChildFrameAt ( main_frame , 1 ) ;
 ASSERT_NE ( nullptr , child2 ) ;
 content : : RenderFrameHost * grandchild = ChildFrameAt ( child1 , 0 ) ;
 ASSERT_NE ( nullptr , grandchild ) ;
 EXPECT_NE ( main_frame -> GetSiteInstance ( ) , child1 -> GetSiteInstance ( ) ) ;
 EXPECT_NE ( main_frame -> GetSiteInstance ( ) , child2 -> GetSiteInstance ( ) ) ;
 EXPECT_NE ( child1 -> GetSiteInstance ( ) , grandchild -> GetSiteInstance ( ) ) ;
 auto document_has_focus = [ ] ( content : : RenderFrameHost * rfh ) -> bool {
 bool has_focus = false ;
 EXPECT_TRUE ( ExecuteScriptAndExtractBool ( rfh , "window.domAutomationController.send(document.hasFocus())" , & has_focus ) ) ;
 return has_focus ;
 }
 ;
 EXPECT_EQ ( main_frame , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_TRUE ( document_has_focus ( main_frame ) ) ;
 EXPECT_FALSE ( document_has_focus ( child1 ) ) ;
 EXPECT_FALSE ( document_has_focus ( grandchild ) ) ;
 EXPECT_FALSE ( document_has_focus ( child2 ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child1 , "window.focus();
" ) ) ;
 EXPECT_EQ ( child1 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_TRUE ( document_has_focus ( main_frame ) ) ;
 EXPECT_TRUE ( document_has_focus ( child1 ) ) ;
 EXPECT_FALSE ( document_has_focus ( grandchild ) ) ;
 EXPECT_FALSE ( document_has_focus ( child2 ) ) ;
 EXPECT_TRUE ( ExecuteScript ( grandchild , "window.focus();
" ) ) ;
 EXPECT_EQ ( grandchild , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_TRUE ( document_has_focus ( main_frame ) ) ;
 EXPECT_TRUE ( document_has_focus ( child1 ) ) ;
 EXPECT_TRUE ( document_has_focus ( grandchild ) ) ;
 EXPECT_FALSE ( document_has_focus ( child2 ) ) ;
 EXPECT_TRUE ( ExecuteScript ( child2 , "window.focus();
" ) ) ;
 EXPECT_EQ ( child2 , web_contents -> GetFocusedFrame ( ) ) ;
 EXPECT_TRUE ( document_has_focus ( main_frame ) ) ;
 EXPECT_FALSE ( document_has_focus ( child1 ) ) ;
 EXPECT_FALSE ( document_has_focus ( grandchild ) ) ;
 EXPECT_TRUE ( document_has_focus ( child2 ) ) ;
 }