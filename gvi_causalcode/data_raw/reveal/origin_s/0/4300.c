TEST_F ( WebFrameSimTest , FindInPageSelectNextMatch ) {
 WebView ( ) . Resize ( WebSize ( 500 , 300 ) ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > body , html {
 width : 4000px ;
 height : 4000px ;
 margin : 0 ;
 }

 position : absolute ;
 left : 800px ;
 top : 2000px ;
 }

 position : absolute ;
 left : 1000px ;
 top : 3000px ;
 }