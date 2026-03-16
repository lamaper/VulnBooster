IN_PROC_BROWSER_TEST_F ( FramebustBlockBrowserTest , SimpleFramebust_Blocked ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/iframe.html" ) ) ;
 GURL child_url = embedded_test_server ( ) -> GetURL ( "a.com" , "/title1.html" ) ;
 NavigateIframeToUrlWithoutGesture ( GetWebContents ( ) , "test" , child_url ) ;
 content : : RenderFrameHost * child = content : : ChildFrameAt ( GetWebContents ( ) -> GetMainFrame ( ) , 0 ) ;
 EXPECT_EQ ( child_url , child -> GetLastCommittedURL ( ) ) ;
 GURL redirect_url = embedded_test_server ( ) -> GetURL ( "b.com" , "/title1.html" ) ;
 base : : RunLoop block_waiter ;
 blocked_url_added_closure_ = block_waiter . QuitClosure ( ) ;
 child -> ExecuteJavaScriptForTests ( base : : ASCIIToUTF16 ( base : : StringPrintf ( "window.top.location = '%s';
" , redirect_url . spec ( ) . c_str ( ) ) ) ) ;
 block_waiter . Run ( ) ;
 EXPECT_TRUE ( base : : ContainsValue ( GetFramebustTabHelper ( ) -> blocked_urls ( ) , redirect_url ) ) ;
 }