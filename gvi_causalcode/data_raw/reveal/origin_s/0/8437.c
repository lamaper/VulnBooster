TEST_F ( WebFrameTest , ClearClosedOpener ) {
 FrameTestHelpers : : WebViewHelper opener_helper ;
 opener_helper . Initialize ( ) ;
 FrameTestHelpers : : WebViewHelper helper ;
 helper . InitializeWithOpener ( opener_helper . GetWebView ( ) -> MainFrame ( ) ) ;
 opener_helper . Reset ( ) ;
 EXPECT_EQ ( nullptr , helper . LocalMainFrame ( ) -> Opener ( ) ) ;
 }