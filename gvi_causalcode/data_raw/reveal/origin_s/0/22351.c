IN_PROC_BROWSER_TEST_F ( WebRtcApprtcBrowserTest , MANUAL_WorksOnApprtc ) {
 DetectErrorsInJavaScript ( ) ;
 ASSERT_TRUE ( LaunchApprtcInstanceOnLocalhost ( "9999" ) ) ;
 ASSERT_TRUE ( LaunchColliderOnLocalHost ( "http://localhost:9999" , "8089" ) ) ;
 while ( ! LocalApprtcInstanceIsUp ( ) ) DVLOG ( 1 ) << "Waiting for AppRTC to come up..." ;
 GURL room_url = GURL ( "http://localhost:9999/r/some_room" "?wshpp=localhost:8089&wstls=false" ) ;
 chrome : : AddTabAt ( browser ( ) , GURL ( ) , - 1 , true ) ;
 content : : WebContents * left_tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 PermissionRequestManager : : FromWebContents ( left_tab ) -> set_auto_response_for_test ( PermissionRequestManager : : ACCEPT_ALL ) ;
 InfoBarResponder left_infobar_responder ( InfoBarService : : FromWebContents ( left_tab ) , InfoBarResponder : : ACCEPT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , room_url ) ;
 chrome : : AddTabAt ( browser ( ) , GURL ( ) , - 1 , true ) ;
 content : : WebContents * right_tab = browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) ;
 PermissionRequestManager : : FromWebContents ( right_tab ) -> set_auto_response_for_test ( PermissionRequestManager : : ACCEPT_ALL ) ;
 InfoBarResponder right_infobar_responder ( InfoBarService : : FromWebContents ( right_tab ) , InfoBarResponder : : ACCEPT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , room_url ) ;
 ASSERT_TRUE ( WaitForCallToComeUp ( left_tab ) ) ;
 ASSERT_TRUE ( WaitForCallToComeUp ( right_tab ) ) ;
 ASSERT_TRUE ( DetectRemoteVideoPlaying ( left_tab ) ) ;
 ASSERT_TRUE ( DetectRemoteVideoPlaying ( right_tab ) ) ;
 chrome : : CloseWebContents ( browser ( ) , left_tab , false ) ;
 chrome : : CloseWebContents ( browser ( ) , right_tab , false ) ;
 }