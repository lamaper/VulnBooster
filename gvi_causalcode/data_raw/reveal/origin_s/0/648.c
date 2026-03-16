TEST_F ( WebFrameTest , DidScrollCallbackAfterScrollableAreaChanges ) {
 FrameTestHelpers : : WebViewHelper web_view_helper ;
 web_view_helper . Initialize ( ) ;
 web_view_helper . Resize ( WebSize ( 200 , 200 ) ) ;
 WebViewImpl * web_view = web_view_helper . GetWebView ( ) ;
 InitializeWithHTML ( * web_view -> MainFrameImpl ( ) -> GetFrame ( ) , "<style>" " #scrollable {
" " height: 100px;
" " width: 100px;
" " overflow: scroll;
" " will-change: transform;
" " }
" " #forceScroll {
 height: 120px;
 width: 50px;
 }
" "</style>" "<div id='scrollable'>" " <div id='forceScroll'></div>" "</div>" ) ;
 web_view -> UpdateAllLifecyclePhases ( ) ;
 Document * document = web_view -> MainFrameImpl ( ) -> GetFrame ( ) -> GetDocument ( ) ;
 Element * scrollable = document -> getElementById ( "scrollable" ) ;
 auto * scrollable_area = ToLayoutBox ( scrollable -> GetLayoutObject ( ) ) -> GetScrollableArea ( ) ;
 EXPECT_NE ( nullptr , scrollable_area ) ;
 cc : : Layer * cc_scroll_layer = scrollable_area -> LayerForScrolling ( ) -> CcLayer ( ) ;
 EXPECT_NE ( nullptr , cc_scroll_layer ) ;
 EXPECT_EQ ( ScrollOffset ( ) , scrollable_area -> GetScrollOffset ( ) ) ;
 cc_scroll_layer -> SetScrollOffsetFromImplSide ( gfx : : ScrollOffset ( 0 , 1 ) ) ;
 web_view -> UpdateAllLifecyclePhases ( ) ;
 EXPECT_EQ ( ScrollOffset ( 0 , 1 ) , scrollable_area -> GetScrollOffset ( ) ) ;
 scrollable -> setAttribute ( HTMLNames : : styleAttr , "overflow: visible" ) ;
 WebLocalFrame * frame = web_view_helper . LocalMainFrame ( ) ;
 frame -> ExecuteScript ( WebScriptSource ( "var forceLayoutFromScript = scrollable.offsetTop;
" ) ) ;
 EXPECT_EQ ( document -> Lifecycle ( ) . GetState ( ) , DocumentLifecycle : : kLayoutClean ) ;
 EXPECT_EQ ( nullptr , ToLayoutBox ( scrollable -> GetLayoutObject ( ) ) -> GetScrollableArea ( ) ) ;
 cc_scroll_layer -> SetScrollOffsetFromImplSide ( gfx : : ScrollOffset ( 0 , 3 ) ) ;
 }