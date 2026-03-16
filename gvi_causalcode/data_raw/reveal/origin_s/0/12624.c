TEST_F ( WebFrameTest , ExecuteCommandProducesUserGesture ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . InitializeAndLoad ( "about:blank" ) ;
 WebLocalFrameImpl * frame = web_view_helper . LocalMainFrame ( ) ;
 EXPECT_FALSE ( frame -> GetFrame ( ) -> HasBeenActivated ( ) ) ;
 frame -> ExecuteScript ( WebScriptSource ( WebString ( "document.execCommand('copy');
" ) ) ) ;
 EXPECT_FALSE ( frame -> GetFrame ( ) -> HasBeenActivated ( ) ) ;
 frame -> ExecuteCommand ( WebString : : FromUTF8 ( "Paste" ) ) ;
 EXPECT_TRUE ( frame -> GetFrame ( ) -> HasBeenActivated ( ) ) ;
 }