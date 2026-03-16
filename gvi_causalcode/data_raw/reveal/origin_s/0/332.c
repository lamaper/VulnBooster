TEST_P ( SlimmingPaintWebFrameTest , DidScrollCallbackAfterScrollableAreaChanges ) {
 DCHECK ( RuntimeEnabledFeatures : : SlimmingPaintV2Enabled ( ) ) ;
 InitializeWithHTML ( * WebView ( ) -> MainFrameImpl ( ) -> GetFrame ( ) , "<style>" " #scrollable {
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
 WebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 Document * document = WebView ( ) -> MainFrameImpl ( ) -> GetFrame ( ) -> GetDocument ( ) ;
 Element * scrollable = document -> getElementById ( "scrollable" ) ;
 auto * scrollable_area = ToLayoutBox ( scrollable -> GetLayoutObject ( ) ) -> GetScrollableArea ( ) ;
 EXPECT_NE ( nullptr , scrollable_area ) ;
 EXPECT_EQ ( ContentLayerCount ( ) , 2u ) ;
 EXPECT_EQ ( ScrollHitTestLayerCount ( ) , 1u ) ;
 EXPECT_EQ ( ScrollOffset ( ) , scrollable_area -> GetScrollOffset ( ) ) ;
 ScrollHitTestLayerAt ( 0 ) -> SetScrollOffsetFromImplSide ( gfx : : ScrollOffset ( 0 , 1 ) ) ;
 WebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 EXPECT_EQ ( ScrollOffset ( 0 , 1 ) , scrollable_area -> GetScrollOffset ( ) ) ;
 scrollable -> setAttribute ( HTMLNames : : styleAttr , "overflow: visible" ) ;
 LocalMainFrame ( ) -> ExecuteScript ( WebScriptSource ( "var forceLayoutFromScript = scrollable.offsetTop;
" ) ) ;
 EXPECT_EQ ( document -> Lifecycle ( ) . GetState ( ) , DocumentLifecycle : : kLayoutClean ) ;
 EXPECT_EQ ( nullptr , ToLayoutBox ( scrollable -> GetLayoutObject ( ) ) -> GetScrollableArea ( ) ) ;
 EXPECT_EQ ( ScrollHitTestLayerCount ( ) , 1u ) ;
 ScrollHitTestLayerAt ( 0 ) -> SetScrollOffsetFromImplSide ( gfx : : ScrollOffset ( 0 , 3 ) ) ;
 WebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 EXPECT_EQ ( ContentLayerCount ( ) , 1u ) ;
 EXPECT_EQ ( ScrollHitTestLayerCount ( ) , 0u ) ;
 }