TEST_F ( WebFrameSimTest , ChangeBackgroundColor ) {
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( "<!DOCTYPE html><body></body>" ) ;
 Element * body = GetDocument ( ) . QuerySelector ( "body" ) ;
 EXPECT_TRUE ( ! ! body ) ;
 Compositor ( ) . BeginFrame ( ) ;
 EXPECT_EQ ( SK_ColorWHITE , Compositor ( ) . background_color ( ) ) ;
 body -> SetInlineStyleProperty ( CSSPropertyBackgroundColor , "red" ) ;
 Compositor ( ) . BeginFrame ( ) ;
 EXPECT_EQ ( SK_ColorRED , Compositor ( ) . background_color ( ) ) ;
 }