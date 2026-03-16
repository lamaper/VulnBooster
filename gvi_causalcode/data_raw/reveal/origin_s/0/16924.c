IN_PROC_BROWSER_TEST_F ( TabDragCaptureLostTest , ReleaseCaptureOnDrag ) {
 AddTabAndResetBrowser ( browser ( ) ) ;
 TabStrip * tab_strip = GetTabStripForBrowser ( browser ( ) ) ;
 gfx : : Point tab_1_center ( GetCenterInScreenCoordinates ( tab_strip -> tab_at ( 1 ) ) ) ;
 ASSERT_TRUE ( ui_test_utils : : SendMouseMoveSync ( tab_1_center ) && ui_test_utils : : SendMouseEventsSync ( ui_controls : : LEFT , ui_controls : : DOWN ) ) ;
 gfx : : Point tab_0_center ( GetCenterInScreenCoordinates ( tab_strip -> tab_at ( 0 ) ) ) ;
 TestDesktopBrowserFrameAura * frame = static_cast < TestDesktopBrowserFrameAura * > ( BrowserView : : GetBrowserViewForBrowser ( browser ( ) ) -> GetWidget ( ) -> native_widget_private ( ) ) ;
 frame -> ReleaseCaptureOnNextClear ( ) ;
 ASSERT_TRUE ( ui_test_utils : : SendMouseMoveSync ( tab_0_center ) ) ;
 EXPECT_FALSE ( tab_strip -> IsDragSessionActive ( ) ) ;
 }