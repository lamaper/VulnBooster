TEST_F ( WebUsbDetectorTest , UsbDeviceWasThereBeforeAndThenRemoved ) {
 GURL landing_page ( kLandingPage_1 ) ;
 scoped_refptr < device : : MockUsbDevice > device ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page ) ) ;
 std : : string guid = device -> guid ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 Initialize ( ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 }