TEST_F ( WebFrameSimTest , ScrollFocusedIntoViewClipped ) {
 UseAndroidSettings ( ) ;
 WebView ( ) . Resize ( WebSize ( 400 , 600 ) ) ;
 WebView ( ) . EnableFakePageScaleAnimationForTesting ( true ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > : : - webkit - scrollbar {
 width : 0px ;
 height : 0px ;
 }
 body , html {
 margin : 0px ;
 width : 100 % ;
 height : 100 % ;
 }
 input {
 padding : 0 ;
 position : relative ;
 top : 1400px ;
 width : 100px ;
 height : 20px ;
 }

 width : 100 % ;
 height : 100 % ;
 overflow : hidden ;
 }

 width : 980px ;
 height : 1470px ;
 }