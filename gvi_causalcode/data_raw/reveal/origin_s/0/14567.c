TEST_F ( WebUsbDetectorTest , NotificationClickedWhileInactiveTabUrlIsLandingPage ) {
 GURL landing_page_1 ( kLandingPage_1 ) ;
 GURL landing_page_2 ( kLandingPage_2 ) ;
 scoped_refptr < device : : MockUsbDevice > device_1 ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page_1 ) ) ;
 std : : string guid_1 = device_1 -> guid ( ) ;
 TabStripModel * tab_strip_model = browser ( ) -> tab_strip_model ( ) ;
 base : : HistogramTester histogram_tester ;
 Initialize ( ) ;
 AddTab ( browser ( ) , landing_page_1 ) ;
 AddTab ( browser ( ) , landing_page_2 ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device_1 ) ;
 message_center : : Notification * notification_1 = message_center_ -> FindVisibleNotificationById ( guid_1 ) ;
 ASSERT_TRUE ( notification_1 != nullptr ) ;
 EXPECT_EQ ( 2 , tab_strip_model -> count ( ) ) ;
 notification_1 -> Click ( ) ;
 EXPECT_EQ ( 2 , tab_strip_model -> count ( ) ) ;
 content : : WebContents * web_contents = tab_strip_model -> GetWebContentsAt ( tab_strip_model -> active_index ( ) ) ;
 EXPECT_EQ ( landing_page_1 , web_contents -> GetURL ( ) ) ;
 ASSERT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_1 ) == nullptr ) ;
 histogram_tester . ExpectUniqueSample ( "WebUsb.NotificationClosed" , 2 , 1 ) ;
 }