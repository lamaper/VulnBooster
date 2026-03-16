TEST_F ( WebFrameSimTest , RtlInitialScrollOffsetWithViewport ) {
 UseAndroidSettings ( ) ;
 WebView ( ) . Resize ( WebSize ( 400 , 400 ) ) ;
 WebView ( ) . SetDefaultPageScaleLimits ( 0.25f , 2 ) ;
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( R "HTML( < meta name = 'viewport' content = 'width=device-width, minimum-scale=1' > < body dir = 'rtl' > < div style = 'width: 3000px;
 height: 20px' > < / div > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 ScrollableArea * area = GetDocument ( ) . View ( ) -> LayoutViewport ( ) ;
 ASSERT_EQ ( ScrollOffset ( 0 , 0 ) , area -> GetScrollOffset ( ) ) ;
 }