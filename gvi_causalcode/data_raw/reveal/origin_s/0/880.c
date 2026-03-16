TEST_F ( WebUsbDetectorTest , UsbDeviceAddedBeforeActiveTabUrlIsLandingPage ) {
 GURL landing_page_1 ( kLandingPage_1 ) ;
 scoped_refptr < device : : MockUsbDevice > device_1 ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page_1 ) ) ;
 std : : string guid_1 = device_1 -> guid ( ) ;
 base : : HistogramTester histogram_tester ;
 Initialize ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device_1 ) ;
 ASSERT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_1 ) != nullptr ) ;
 AddTab ( browser ( ) , landing_page_1 ) ;
 ASSERT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_1 ) == nullptr ) ;
 histogram_tester . ExpectUniqueSample ( "WebUsb.NotificationClosed" , 3 , 1 ) ;
 }