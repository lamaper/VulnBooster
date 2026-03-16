TEST_F ( WebFrameSimTest , NormalIFrameHasLayoutObjects ) {
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 SimRequest frame_resource ( "https://example.com/frame.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( "<!DOCTYPE html>" "<iframe src=frame.html style='display: block'></iframe>" ) ;
 frame_resource . Complete ( "<!DOCTYPE html>" "<html><body>This is a visible iframe.</body></html>" ) ;
 Element * element = GetDocument ( ) . QuerySelector ( "iframe" ) ;
 HTMLFrameOwnerElement * frame_owner_element = ToHTMLFrameOwnerElement ( element ) ;
 Document * iframe_doc = frame_owner_element -> contentDocument ( ) ;
 EXPECT_TRUE ( iframe_doc -> documentElement ( ) -> GetLayoutObject ( ) ) ;
 element -> SetInlineStyleProperty ( CSSPropertyDisplay , CSSValueNone ) ;
 Compositor ( ) . BeginFrame ( ) ;
 EXPECT_FALSE ( iframe_doc -> documentElement ( ) -> GetLayoutObject ( ) ) ;
 }