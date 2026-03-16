TEST_F ( WebFrameTest , AltTextOnAboutBlankPage ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . InitializeAndLoad ( "about:blank" ) ;
 web_view_helper . Resize ( WebSize ( 640 , 480 ) ) ;
 WebLocalFrameImpl * frame = web_view_helper . LocalMainFrame ( ) ;
 const char kSource [ ] = "<img id='foo' src='foo' alt='foo alt' width='200' height='200'>" ;
 FrameTestHelpers : : LoadHTMLString ( frame , kSource , ToKURL ( "about:blank" ) ) ;
 web_view_helper . GetWebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 RunPendingTasks ( ) ;
 LayoutObject * layout_object = frame -> GetFrame ( ) -> GetDocument ( ) -> getElementById ( "foo" ) -> GetLayoutObject ( ) -> SlowFirstChild ( ) ;
 String text = "" ;
 for ( LayoutObject * obj = layout_object ;
 obj ;
 obj = obj -> NextInPreOrder ( ) ) {
 if ( obj -> IsText ( ) ) {
 LayoutText * layout_text = ToLayoutText ( obj ) ;
 text = layout_text -> GetText ( ) ;
 break ;
 }
 }
 EXPECT_EQ ( "foo alt" , text . Utf8 ( ) ) ;
 }