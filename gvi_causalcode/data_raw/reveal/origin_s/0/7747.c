TEST_F ( FullscreenControllerStateUnitTest , OneCapturedTabFullscreenedBeforeBrowserFullscreen ) {
 content : : WebContentsDelegate * const wc_delegate = static_cast < content : : WebContentsDelegate * > ( browser ( ) ) ;
 ASSERT_TRUE ( wc_delegate -> EmbedsFullscreenWidget ( ) ) ;
 AddTab ( browser ( ) , GURL ( url : : kAboutBlankURL ) ) ;
 content : : WebContents * const tab = browser ( ) -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) ;
 browser ( ) -> tab_strip_model ( ) -> ActivateTabAt ( 0 , true ) ;
 const gfx : : Size kCaptureSize ( 1280 , 720 ) ;
 tab -> IncrementCapturerCount ( kCaptureSize ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_TRUE ) ) ;
 EXPECT_TRUE ( wc_delegate -> IsFullscreenForTabOrPending ( tab ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsWindowFullscreenForTabOrPending ( ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsFullscreenForBrowser ( ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TOGGLE_FULLSCREEN ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 EXPECT_TRUE ( wc_delegate -> IsFullscreenForTabOrPending ( tab ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsWindowFullscreenForTabOrPending ( ) ) ;
 EXPECT_TRUE ( GetFullscreenController ( ) -> IsFullscreenForBrowser ( ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TOGGLE_FULLSCREEN ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 EXPECT_TRUE ( wc_delegate -> IsFullscreenForTabOrPending ( tab ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsWindowFullscreenForTabOrPending ( ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsFullscreenForBrowser ( ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TOGGLE_FULLSCREEN ) ) ;
 ASSERT_TRUE ( InvokeEvent ( WINDOW_CHANGE ) ) ;
 ASSERT_TRUE ( InvokeEvent ( TAB_FULLSCREEN_FALSE ) ) ;
 EXPECT_FALSE ( wc_delegate -> IsFullscreenForTabOrPending ( tab ) ) ;
 EXPECT_FALSE ( GetFullscreenController ( ) -> IsWindowFullscreenForTabOrPending ( ) ) ;
 EXPECT_TRUE ( GetFullscreenController ( ) -> IsFullscreenForBrowser ( ) ) ;
 }