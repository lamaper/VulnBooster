TEST_F ( WebFrameSimTest , ScrollFocusedEditableIntoViewNoLayoutObject ) {
 WebView ( ) . Resize ( WebSize ( 500 , 600 ) ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 SimRequest r ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 r . Complete ( R "HTML( < ! DOCTYPE html > < style > input {
 position : absolute ;
 top : 1000px ;
 left : 800px ;
 }
 @ media ( max - height : 500px ) {
 input {
 display : none ;
 }
 }
 < / style > < input id = "target" type = "text" > < / input > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 Element * input = GetDocument ( ) . getElementById ( "target" ) ;
 input -> focus ( ) ;
 ScrollableArea * area = GetDocument ( ) . View ( ) -> LayoutViewport ( ) ;
 area -> SetScrollOffset ( ScrollOffset ( 0 , 0 ) , kProgrammaticScroll ) ;
 ASSERT_TRUE ( input -> GetLayoutObject ( ) ) ;
 ASSERT_EQ ( input , WebView ( ) . FocusedElement ( ) ) ;
 ASSERT_EQ ( ScrollOffset ( 0 , 0 ) , area -> GetScrollOffset ( ) ) ;
 WebView ( ) . Resize ( WebSize ( 500 , 300 ) ) ;
 ASSERT_FALSE ( input -> GetLayoutObject ( ) ) ;
 ASSERT_EQ ( input , WebView ( ) . FocusedElement ( ) ) ;
 WebFrameWidget * widget = WebView ( ) . MainFrameImpl ( ) -> FrameWidgetImpl ( ) ;
 widget -> ScrollFocusedEditableElementIntoView ( ) ;
 Compositor ( ) . BeginFrame ( ) ;
 EXPECT_EQ ( ScrollOffset ( 0 , 0 ) , area -> GetScrollOffset ( ) ) ;
 }