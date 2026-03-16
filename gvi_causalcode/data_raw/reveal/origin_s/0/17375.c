TEST_F ( WebUsbDetectorTest , UsbDeviceWithoutProductNameAddedAndRemoved ) {
 std : : string product_name = "" ;
 GURL landing_page ( kLandingPage_1 ) ;
 scoped_refptr < device : : MockUsbDevice > device ( new device : : MockUsbDevice ( 0 , 1 , "Google" , product_name , "002" , landing_page ) ) ;
 std : : string guid = device -> guid ( ) ;
 Initialize ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 }