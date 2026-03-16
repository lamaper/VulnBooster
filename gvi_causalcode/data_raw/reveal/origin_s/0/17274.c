TEST_F ( WebFrameSimTest , LayoutViewLocalVisualRect ) {
 UseAndroidSettings ( ) ;
 WebView ( ) . Resize ( WebSize ( 600 , 400 ) ) ;
 WebView ( ) . SetDefaultPageScaleLimits ( 0.5f , 2 ) ;
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( R "HTML( < meta name = 'viewport' content = 'width=device-width, minimum-scale=0.5' > < body style = 'margin: 0;
 width: 1800px;
 height: 1200px' > < / div > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 ASSERT_EQ ( LayoutRect ( 0 , 0 , 1200 , 800 ) , GetDocument ( ) . GetLayoutView ( ) -> LocalVisualRect ( ) ) ;
 }