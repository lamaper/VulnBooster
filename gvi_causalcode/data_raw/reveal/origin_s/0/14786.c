TEST_F ( WebFrameTest , GetCanonicalUrlForSharingNone ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . InitializeAndLoad ( "about:blank" ) ;
 WebLocalFrameImpl * frame = web_view_helper . LocalMainFrame ( ) ;
 EXPECT_TRUE ( frame -> GetDocument ( ) . CanonicalUrlForSharing ( ) . IsNull ( ) ) ;
 }