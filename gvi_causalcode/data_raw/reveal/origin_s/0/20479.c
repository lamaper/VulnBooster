IN_PROC_BROWSER_TEST_P ( WebRtcWebcamBrowserTest , TestAcquiringAndReacquiringWebcam ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> InitializeAndWaitUntilReady ( ) ) ;
 GURL url ( embedded_test_server ( ) -> GetURL ( kMainWebrtcTestHtmlPage ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 content : : WebContents * tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 if ( ! HasWebcamAvailableOnSystem ( tab ) ) {
 LOG ( INFO ) << "No webcam found on bot: skipping..." ;
 return ;
 }
 if ( ! IsOnQtKit ( ) ) {
 EXPECT_EQ ( "320x240" , GetUserMediaAndGetStreamSize ( tab , kVideoCallConstraintsQVGA ) ) ;
 }
 EXPECT_EQ ( "640x480" , GetUserMediaAndGetStreamSize ( tab , kVideoCallConstraintsVGA ) ) ;
 EXPECT_EQ ( "640x360" , GetUserMediaAndGetStreamSize ( tab , kVideoCallConstraints360p ) ) ;
 if ( IsOnQtKit ( ) ) return ;
 EXPECT_EQ ( "1280x720" , GetUserMediaAndGetStreamSize ( tab , kVideoCallConstraints720p ) ) ;
 EXPECT_EQ ( "1920x1080" , GetUserMediaAndGetStreamSize ( tab , kVideoCallConstraints1080p ) ) ;
 }