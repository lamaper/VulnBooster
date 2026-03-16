TEST_F ( WebFrameSimTest , TestScrollFocusedEditableElementIntoView ) {
 WebView ( ) . Resize ( WebSize ( 500 , 300 ) ) ;
 WebView ( ) . SetDefaultPageScaleLimits ( 1.f , 4 ) ;
 WebView ( ) . EnableFakePageScaleAnimationForTesting ( true ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetViewportEnabled ( false ) ;
 WebView ( ) . GetSettings ( ) -> SetAutoZoomFocusedNodeToLegibleScale ( true ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > : : - webkit - scrollbar {
 width : 0px ;
 height : 0px ;
 }
 body {
 margin : 0px ;
 }
 input {
 border : 0 ;
 padding : 0 ;
 position : absolute ;
 left : 200px ;
 top : 600px ;
 width : 100px ;
 height : 20px ;
 }

 background : silver ;
 width : 500px ;
 height : 600px ;
 }
 < / style > < div id = "content" > a < / div > < input type = "text" > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 WebView ( ) . AdvanceFocus ( false ) ;
 LocalFrame * frame = ToLocalFrame ( WebView ( ) . GetPage ( ) -> MainFrame ( ) ) ;
 LocalFrameView * frame_view = frame -> View ( ) ;
 VisualViewport & visual_viewport = frame -> GetPage ( ) -> GetVisualViewport ( ) ;
 FloatRect inputRect ( 200 , 600 , 100 , 20 ) ;
 frame_view -> GetScrollableArea ( ) -> SetScrollOffset ( ScrollOffset ( 0 , 0 ) , kProgrammaticScroll ) ;
 ASSERT_EQ ( FloatPoint ( ) , visual_viewport . VisibleRectInDocument ( ) . Location ( ) ) ;
 WebView ( ) . MainFrameImpl ( ) -> FrameWidget ( ) -> ScrollFocusedEditableElementIntoView ( ) ;
 EXPECT_EQ ( 1 , WebView ( ) . FakePageScaleAnimationPageScaleForTesting ( ) ) ;
 frame_view -> LayoutViewport ( ) -> SetScrollOffset ( ToFloatSize ( FloatPoint ( WebView ( ) . FakePageScaleAnimationTargetPositionForTesting ( ) ) ) , kProgrammaticScroll ) ;
 EXPECT_TRUE ( visual_viewport . VisibleRectInDocument ( ) . Contains ( inputRect ) ) ;
 WebView ( ) . EnableFakePageScaleAnimationForTesting ( true ) ;
 WebView ( ) . MainFrameImpl ( ) -> FrameWidget ( ) -> ScrollFocusedEditableElementIntoView ( ) ;
 EXPECT_EQ ( 0 , WebView ( ) . FakePageScaleAnimationPageScaleForTesting ( ) ) ;
 EXPECT_EQ ( IntPoint ( ) , WebView ( ) . FakePageScaleAnimationTargetPositionForTesting ( ) ) ;
 WebView ( ) . ResizeVisualViewport ( IntSize ( 200 , 100 ) ) ;
 ASSERT_FALSE ( visual_viewport . VisibleRectInDocument ( ) . Contains ( inputRect ) ) ;
 WebView ( ) . MainFrameImpl ( ) -> FrameWidget ( ) -> ScrollFocusedEditableElementIntoView ( ) ;
 frame_view -> GetScrollableArea ( ) -> SetScrollOffset ( ToFloatSize ( FloatPoint ( WebView ( ) . FakePageScaleAnimationTargetPositionForTesting ( ) ) ) , kProgrammaticScroll ) ;
 EXPECT_TRUE ( visual_viewport . VisibleRectInDocument ( ) . Contains ( inputRect ) ) ;
 EXPECT_EQ ( 1 , WebView ( ) . FakePageScaleAnimationPageScaleForTesting ( ) ) ;
 }