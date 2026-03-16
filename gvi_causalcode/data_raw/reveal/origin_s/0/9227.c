TEST_F ( WebFrameTest , FallbackForNonexistentProvisionalNavigation ) {
 RegisterMockedHttpURLLoad ( "fallback.html" ) ;
 TestFallbackWebFrameClient main_client ;
 TestFallbackWebFrameClient child_client ;
 main_client . SetChildWebFrameClient ( & child_client ) ;
 FrameTestHelpers : : WebViewHelper web_view_helper_ ;
 web_view_helper_ . Initialize ( & main_client ) ;
 WebLocalFrameImpl * main_frame = web_view_helper_ . LocalMainFrame ( ) ;
 WebURLRequest request ( ToKURL ( base_url_ + "fallback.html" ) ) ;
 main_frame -> StartNavigation ( request ) ;
 Platform : : Current ( ) -> GetURLLoaderMockFactory ( ) -> ServeAsynchronousRequests ( ) ;
 WebLocalFrame * child = main_frame -> FirstChild ( ) -> ToWebLocalFrame ( ) ;
 child -> StartNavigation ( WebURLRequest ( BlankURL ( ) ) ) ;
 EXPECT_EQ ( WebLocalFrame : : NoLoadInProgress , child -> MaybeRenderFallbackContent ( ResourceError : : Failure ( request . Url ( ) ) ) ) ;
 }