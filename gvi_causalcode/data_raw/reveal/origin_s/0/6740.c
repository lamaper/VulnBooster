TEST_F ( WebFrameSimTest , DisambiguationPopupPixelTest ) {
 WebView ( ) . Resize ( WebSize ( 400 , 600 ) ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 UseAndroidSettings ( ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > body , html {
 width : 4000px ;
 height : 4000px ;
 margin : 0 ;
 }

 position : absolute ;
 left : 200px ;
 top : 300px ;
 width : 100px ;
 height : 100px ;
 background - color : red ;
 }
 < / style > < div id = "box" > < / div > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 ASSERT_EQ ( 0.25f , WebView ( ) . PageScaleFactor ( ) ) ;
 float scale = 4.f ;
 WebRect zoom_rect ( 200 , 300 , 100 , 100 ) ;
 gfx : : Size canvas_size ( zoom_rect . width * scale , zoom_rect . height * scale ) ;
 SkImageInfo info = SkImageInfo : : MakeN32Premul ( canvas_size . width ( ) , canvas_size . height ( ) ) ;
 size_t size = info . computeMinByteSize ( ) ;
 auto buffer = std : : make_unique < uint8_t [ ] > ( size ) ;
 SkBitmap bitmap ;
 bitmap . installPixels ( info , buffer . get ( ) , info . minRowBytes ( ) ) ;
 cc : : SkiaPaintCanvas canvas ( bitmap ) ;
 canvas . scale ( scale , scale ) ;
 canvas . translate ( - zoom_rect . x , - zoom_rect . y ) ;
 WebView ( ) . UpdateAllLifecyclePhases ( ) ;
 WebView ( ) . PaintContentIgnoringCompositing ( & canvas , zoom_rect ) ;
 for ( int x = 0 ;
 x < canvas_size . width ( ) ;
 ++ x ) {
 for ( int y = 0 ;
 y < canvas_size . height ( ) ;
 ++ y ) {
 ASSERT_EQ ( bitmap . getColor ( x , y ) , SK_ColorRED ) << "Mismatching pixel at (" << x << ", " << y << ")" ;
 }
 }
 }