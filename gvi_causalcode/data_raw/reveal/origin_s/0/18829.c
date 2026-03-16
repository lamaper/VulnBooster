IN_PROC_BROWSER_TEST_F ( TabDragControllerTest , GestureEndShouldEndDragTest ) {
 AddTabAndResetBrowser ( browser ( ) ) ;
 TabStrip * tab_strip = GetTabStripForBrowser ( browser ( ) ) ;
 Tab * tab1 = tab_strip -> tab_at ( 1 ) ;
 gfx : : Point tab_1_center ( tab1 -> width ( ) / 2 , tab1 -> height ( ) / 2 ) ;
 ui : : GestureEvent gesture_tap_down ( tab_1_center . x ( ) , tab_1_center . x ( ) , 0 , base : : TimeDelta ( ) , ui : : GestureEventDetails ( ui : : ET_GESTURE_TAP_DOWN ) ) ;
 tab_strip -> MaybeStartDrag ( tab1 , gesture_tap_down , tab_strip -> GetSelectionModel ( ) ) ;
 EXPECT_TRUE ( TabDragController : : IsActive ( ) ) ;
 ui : : GestureEvent gesture_end ( tab_1_center . x ( ) , tab_1_center . x ( ) , 0 , base : : TimeDelta ( ) , ui : : GestureEventDetails ( ui : : ET_GESTURE_END ) ) ;
 tab_strip -> OnGestureEvent ( & gesture_end ) ;
 EXPECT_FALSE ( TabDragController : : IsActive ( ) ) ;
 EXPECT_FALSE ( tab_strip -> IsDragSessionActive ( ) ) ;
 }