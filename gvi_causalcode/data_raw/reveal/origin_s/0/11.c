TEST_F ( WebFrameSimTest , DisplayNoneIFramePrints ) {
 SimRequest main_resource ( "https://example.com/test.html" , "text/html" ) ;
 SimRequest frame_resource ( "https://example.com/frame.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 main_resource . Complete ( "<!DOCTYPE html>" "<iframe src=frame.html style='display: none'></iframe>" ) ;
 frame_resource . Complete ( "<!DOCTYPE html>" "<html><body>This is a visible iframe.</body></html>" ) ;
 Element * element = GetDocument ( ) . QuerySelector ( "iframe" ) ;
 HTMLFrameOwnerElement * frame_owner_element = ToHTMLFrameOwnerElement ( element ) ;
 Document * iframe_doc = frame_owner_element -> contentDocument ( ) ;
 EXPECT_FALSE ( iframe_doc -> documentElement ( ) -> GetLayoutObject ( ) ) ;
 FloatSize page_size ( 400 , 400 ) ;
 float maximum_shrink_ratio = 1.0 ;
 iframe_doc -> GetFrame ( ) -> StartPrinting ( page_size , page_size , maximum_shrink_ratio ) ;
 EXPECT_TRUE ( iframe_doc -> documentElement ( ) -> GetLayoutObject ( ) ) ;
 iframe_doc -> GetFrame ( ) -> EndPrinting ( ) ;
 EXPECT_FALSE ( iframe_doc -> documentElement ( ) -> GetLayoutObject ( ) ) ;
 }