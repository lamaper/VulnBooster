TEST_F ( WebFrameTest , PrintDetachedIframe ) {
 RegisterMockedHttpURLLoad ( "print-detached-iframe.html" ) ;
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . InitializeAndLoad ( base_url_ + "print-detached-iframe.html" ) ;
 TestFramePrinting ( ToWebLocalFrameImpl ( web_view_helper . LocalMainFrame ( ) -> FirstChild ( ) ) ) ;
 }