TEST_F ( WebFrameSimTest , LayoutViewportExceedsLayoutOverflow ) {
 UseAndroidSettings ( ) ;
 WebView ( ) . ResizeWithBrowserControls ( WebSize ( 400 , 540 ) , 60 , 0 , true ) ;
 WebView ( ) . SetDefaultPageScaleLimits ( 0.25f , 2 ) ;
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( R "HTML( < meta name = 'viewport' content = 'width=device-width, minimum-scale=1' > < body style = 'margin: 0;
 height: 95vh' > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 ScrollableArea * area = GetDocument ( ) . View ( ) -> LayoutViewport ( ) ;
 ASSERT_EQ ( 540 , area -> VisibleHeight ( ) ) ;
 ASSERT_EQ ( IntSize ( 400 , 570 ) , area -> ContentsSize ( ) ) ;
 WebView ( ) . ResizeWithBrowserControls ( WebSize ( 400 , 600 ) , 60 , 0 , false ) ;
 Compositor ( ) . BeginFrame ( ) ;
 ASSERT_EQ ( 600 , area -> VisibleHeight ( ) ) ;
 ASSERT_EQ ( IntSize ( 400 , 600 ) , area -> ContentsSize ( ) ) ;
 }