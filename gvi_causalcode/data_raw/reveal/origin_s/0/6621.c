TEST_P ( SlimmingPaintWebFrameTest , FrameViewScroll ) {
 DCHECK ( RuntimeEnabledFeatures : : SlimmingPaintV2Enabled ( ) ) ;
 InitializeWithHTML ( * WebView ( ) -> MainFrameImpl ( ) -> GetFrame ( ) , "<style>" " #forceScroll {
" " height: 2000px;
" " width: 100px;
" " }
" "</style>" "<div id='forceScroll'></div>" ) ;
 WebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 auto * scrollable_area = GetLocalFrameView ( ) -> LayoutViewport ( ) ;
 EXPECT_NE ( nullptr , scrollable_area ) ;
 EXPECT_EQ ( ScrollHitTestLayerCount ( ) , 1u ) ;
 EXPECT_EQ ( ScrollOffset ( ) , scrollable_area -> GetScrollOffset ( ) ) ;
 ScrollHitTestLayerAt ( 0 ) -> SetScrollOffsetFromImplSide ( gfx : : ScrollOffset ( 0 , 1 ) ) ;
 WebView ( ) -> UpdateAllLifecyclePhases ( ) ;
 EXPECT_EQ ( ScrollOffset ( 0 , 1 ) , scrollable_area -> GetScrollOffset ( ) ) ;
 }