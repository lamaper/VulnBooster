TEST_F ( WebFrameSimTest , DoubleTapZoomWhileScrolled ) {
 UseAndroidSettings ( ) ;
 WebView ( ) . Resize ( WebSize ( 490 , 500 ) ) ;
 WebView ( ) . EnableFakePageScaleAnimationForTesting ( true ) ;
 WebView ( ) . GetSettings ( ) -> SetTextAutosizingEnabled ( false ) ;
 WebView ( ) . SetDefaultPageScaleLimits ( 0.5f , 4 ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > : : - webkit - scrollbar {
 width : 0px ;
 height : 0px ;
 }
 body {
 margin : 0px ;
 width : 10000px ;
 height : 10000px ;
 }

 position : absolute ;
 left : 2000px ;
 top : 3000px ;
 width : 100px ;
 height : 100px ;
 background - color : blue ;
 }
 < / style > < div id = "target" > < / div > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 LocalFrame * frame = ToLocalFrame ( WebView ( ) . GetPage ( ) -> MainFrame ( ) ) ;
 LocalFrameView * frame_view = frame -> View ( ) ;
 VisualViewport & visual_viewport = frame -> GetPage ( ) -> GetVisualViewport ( ) ;
 FloatRect target_rect_in_document ( 2000 , 3000 , 100 , 100 ) ;
 ASSERT_EQ ( 0.5f , visual_viewport . Scale ( ) ) ;
 frame_view -> GetScrollableArea ( ) -> SetScrollOffset ( ScrollOffset ( 2000 - 440 , 3000 - 450 ) , kProgrammaticScroll ) ;
 Element * target = GetDocument ( ) . QuerySelector ( "#target" ) ;
 DOMRect * rect = target -> getBoundingClientRect ( ) ;
 ASSERT_EQ ( 440 , rect -> left ( ) ) ;
 ASSERT_EQ ( 450 , rect -> top ( ) ) ;
 {
 WebView ( ) . AnimateDoubleTapZoom ( WebPoint ( 445 , 455 ) ) ;
 EXPECT_TRUE ( WebView ( ) . FakeDoubleTapAnimationPendingForTesting ( ) ) ;
 ScrollOffset new_offset = ToScrollOffset ( FloatPoint ( WebView ( ) . FakePageScaleAnimationTargetPositionForTesting ( ) ) ) ;
 float new_scale = WebView ( ) . FakePageScaleAnimationPageScaleForTesting ( ) ;
 visual_viewport . SetScale ( new_scale ) ;
 frame_view -> GetScrollableArea ( ) -> SetScrollOffset ( new_offset , kProgrammaticScroll ) ;
 EXPECT_FLOAT_EQ ( 1 , visual_viewport . Scale ( ) ) ;
 EXPECT_TRUE ( visual_viewport . VisibleRectInDocument ( ) . Contains ( target_rect_in_document ) ) ;
 }
 WebView ( ) . EnableFakePageScaleAnimationForTesting ( true ) ;
 {
 WebView ( ) . AnimateDoubleTapZoom ( WebPoint ( 445 , 455 ) ) ;
 EXPECT_TRUE ( WebView ( ) . FakeDoubleTapAnimationPendingForTesting ( ) ) ;
 FloatPoint target_offset ( WebView ( ) . FakePageScaleAnimationTargetPositionForTesting ( ) ) ;
 float new_scale = WebView ( ) . FakePageScaleAnimationPageScaleForTesting ( ) ;
 EXPECT_FLOAT_EQ ( 0.5f , new_scale ) ;
 EXPECT_TRUE ( target_rect_in_document . Contains ( target_offset ) ) ;
 }
 }