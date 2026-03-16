TEST_F ( WebUsbDetectorTest , ThreeUsbDevicesWereThereBeforeAndThenRemovedBeforeWebUsbDetectorWasCreated ) {
 base : : string16 product_name_1 = base : : UTF8ToUTF16 ( kProductName_1 ) ;
 GURL landing_page_1 ( kLandingPage_1 ) ;
 scoped_refptr < device : : MockUsbDevice > device_1 ( new device : : MockUsbDevice ( 0 , 1 , "Google" , kProductName_1 , "002" , landing_page_1 ) ) ;
 std : : string guid_1 = device_1 -> guid ( ) ;
 base : : string16 product_name_2 = base : : UTF8ToUTF16 ( kProductName_2 ) ;
 GURL landing_page_2 ( kLandingPage_2 ) ;
 scoped_refptr < device : : MockUsbDevice > device_2 ( new device : : MockUsbDevice ( 3 , 4 , "Google" , kProductName_2 , "005" , landing_page_2 ) ) ;
 std : : string guid_2 = device_2 -> guid ( ) ;
 base : : string16 product_name_3 = base : : UTF8ToUTF16 ( kProductName_3 ) ;
 GURL landing_page_3 ( kLandingPage_3 ) ;
 scoped_refptr < device : : MockUsbDevice > device_3 ( new device : : MockUsbDevice ( 6 , 7 , "Google" , kProductName_3 , "008" , landing_page_3 ) ) ;
 std : : string guid_3 = device_3 -> guid ( ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device_1 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_1 ) == nullptr ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device_2 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_2 ) == nullptr ) ;
 device_client_ . usb_service ( ) -> AddDevice ( device_3 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_3 ) == nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device_1 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_1 ) == nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device_2 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_2 ) == nullptr ) ;
 device_client_ . usb_service ( ) -> RemoveDevice ( device_3 ) ;
 EXPECT_TRUE ( message_center_ -> FindVisibleNotificationById ( guid_3 ) == nullptr ) ;
 WebUsbDetector web_usb_detector ;
 web_usb_detector . Initialize ( ) ;
 }