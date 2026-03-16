TEST_F ( WebFrameTest , LocalFrameWithRemoteParentIsTransparent ) {
 FrameTestHelpers : : WebViewHelper helper ;
 helper . InitializeRemote ( ) ;
 WebLocalFrameImpl * local_frame = FrameTestHelpers : : CreateLocalChild ( * helper . RemoteMainFrame ( ) ) ;
 FrameTestHelpers : : LoadFrame ( local_frame , "data:text/html,some page" ) ;
 Color color = local_frame -> GetFrameView ( ) -> BaseBackgroundColor ( ) ;
 EXPECT_EQ ( Color : : kTransparent , color ) ;
 }