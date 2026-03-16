TEST_F ( WebFrameSimTest , TickmarksDocumentRelative ) {
 WebView ( ) . Resize ( WebSize ( 500 , 300 ) ) ;
 WebView ( ) . GetPage ( ) -> GetSettings ( ) . SetTextAutosizingEnabled ( false ) ;
 SimRequest request ( "https://example.com/test.html" , "text/html" ) ;
 LoadURL ( "https://example.com/test.html" ) ;
 request . Complete ( R "HTML( < ! DOCTYPE html > < style > body , html {
 width : 4000px ;
 height : 4000px ;
 margin : 0 ;
 }
 div {
 position : absolute ;
 left : 800px ;
 top : 2000px ;
 }
 < / style > < div > test < / div > ) HTML ");
 Compositor ( ) . BeginFrame ( ) ;
 WebLocalFrameImpl * frame = ToWebLocalFrameImpl ( WebView ( ) . MainFrame ( ) ) ;
 LocalFrameView * frame_view = ToLocalFrame ( WebView ( ) . GetPage ( ) -> MainFrame ( ) ) -> View ( ) ;
 frame_view -> GetScrollableArea ( ) -> SetScrollOffset ( ScrollOffset ( 3000 , 1000 ) , kProgrammaticScroll ) ;
 WebFindOptions options ;
 WebString search_text = WebString : : FromUTF8 ( "test" ) ;
 const int kFindIdentifier = 12345 ;
 EXPECT_TRUE ( frame -> Find ( kFindIdentifier , search_text , options , false ) ) ;
 frame -> EnsureTextFinder ( ) . ResetMatchCount ( ) ;
 frame -> EnsureTextFinder ( ) . StartScopingStringMatches ( kFindIdentifier , search_text , options ) ;
 RunPendingTasks ( ) ;
 Vector < IntRect > original_tickmarks ;
 frame_view -> LayoutViewport ( ) -> GetTickmarks ( original_tickmarks ) ;
 EXPECT_EQ ( 1u , original_tickmarks . size ( ) ) ;
 EXPECT_EQ ( IntPoint ( 800 , 2000 ) , original_tickmarks [ 0 ] . Location ( ) ) ;
 }