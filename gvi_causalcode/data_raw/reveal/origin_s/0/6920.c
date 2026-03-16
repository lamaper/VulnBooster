TEST_F ( WebUsbDetectorTest , UsbDeviceWithoutLandingPageAddedAndRemoved ) {
 GURL landing_page ( "" ) ;
 scoped_refptr < device : : MockUsbDevice > device ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page ) ) ;
 std : : string guid = device -> guid ( ) ;
 Initialize ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 }