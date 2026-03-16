TEST_F ( WebUsbDetectorTest , UsbDeviceAddedAndRemoved ) {
 base : : string16 product_name = base : : UTF8ToUTF16 ( kProductName_1 ) ;
 GURL landing_page ( kLandingPage_1 ) ;
 scoped_refptr < device : : MockUsbDevice > device ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page ) ) ;
 std : : string guid = device -> guid ( ) ;
 Initialize ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device ) ;
 message_center : : Notification * notification = message_center_ -> FindVisibleNotificationById ( guid ) ;
 ASSERT_TRUE ( notification != nullptr ) ;
 base : : string16 expected_title = base : : ASCIIToUTF16 ( "Google Product A detected" ) ;
 EXPECT_EQ ( expected_title , notification -> title ( ) ) ;
 base : : string16 expected_message = base : : ASCIIToUTF16 ( "Go to www.google.com/A to connect." ) ;
 EXPECT_EQ ( expected_message , notification -> message ( ) ) ;
 EXPECT_TRUE ( notification -> delegate ( ) != nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid ) == nullptr ) ;
 }