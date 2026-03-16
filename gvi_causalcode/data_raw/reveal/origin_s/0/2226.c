IN_PROC_BROWSER_TEST_F ( WebRtcApprtcBrowserTest , MAYBE_MANUAL_FirefoxApprtcInteropTest ) {
 DetectErrorsInJavaScript ( ) ;
 ASSERT_TRUE ( LaunchApprtcInstanceOnLocalhost ( "9999" ) ) ;
 ASSERT_TRUE ( LaunchColliderOnLocalHost ( "http://localhost:9999" , "8089" ) ) ;
 while ( ! LocalApprtcInstanceIsUp ( ) ) DVLOG ( 1 ) << "Waiting for AppRTC to come up..." ;
 GURL room_url = GURL ( "http://localhost:9999/r/some_room" "?wshpp=localhost:8089&wstls=false" "&firefox_fake_device=1" ) ;
 chrome : : AddTabAt ( browser ( ) , GURL ( ) , - 1 , true ) ;
 content : : WebContents * chrome_tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 PermissionRequestManager : : FromWebContents ( chrome_tab ) -> set_auto_response_for_test ( PermissionRequestManager : : ACCEPT_ALL ) ;
 InfoBarResponder infobar_responder ( InfoBarService : : FromWebContents ( chrome_tab ) , InfoBarResponder : : ACCEPT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , room_url ) ;
 ASSERT_TRUE ( LaunchFirefoxWithUrl ( room_url ) ) ;
 ASSERT_TRUE ( WaitForCallToComeUp ( chrome_tab ) ) ;
 ASSERT_TRUE ( DetectRemoteVideoPlaying ( chrome_tab ) ) ;
 }