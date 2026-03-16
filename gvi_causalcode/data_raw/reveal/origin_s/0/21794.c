IN_PROC_BROWSER_TEST_P ( DetachToBrowserTabDragControllerTest , DragInSameWindow ) {
 if ( input_source ( ) == INPUT_SOURCE_TOUCH ) {
 VLOG ( 1 ) << "Test is DISABLED for touch input." ;
 return ;
 }
 AddTabAndResetBrowser ( browser ( ) ) ;
 TabStrip * tab_strip = GetTabStripForBrowser ( browser ( ) ) ;
 TabStripModel * model = browser ( ) -> tab_strip_model ( ) ;
 gfx : : Point tab_1_center ( GetCenterInScreenCoordinates ( tab_strip -> tab_at ( 1 ) ) ) ;
 ASSERT_TRUE ( PressInput ( tab_1_center ) ) ;
 gfx : : Point tab_0_center ( GetCenterInScreenCoordinates ( tab_strip -> tab_at ( 0 ) ) ) ;
 ASSERT_TRUE ( DragInputTo ( tab_0_center ) ) ;
 ASSERT_TRUE ( ReleaseInput ( ) ) ;
 EXPECT_EQ ( "1 0" , IDString ( model ) ) ;
 EXPECT_FALSE ( TabDragController : : IsActive ( ) ) ;
 EXPECT_FALSE ( tab_strip -> IsDragSessionActive ( ) ) ;
 EXPECT_FALSE ( tab_strip -> GetWidget ( ) -> HasCapture ( ) ) ;
 }