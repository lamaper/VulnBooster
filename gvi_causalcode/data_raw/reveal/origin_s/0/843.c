TEST_F ( NotificationConversionHelperTest , NotificationToNotificationOptions ) {
 scoped_ptr < Notification > notification1 = CreateNotification ( message_center : : NOTIFICATION_TYPE_IMAGE ) ;
 scoped_ptr < extensions : : api : : notifications : : NotificationOptions > options1 ( new extensions : : api : : notifications : : NotificationOptions ( ) ) ;
 NotificationConversionHelper : : NotificationToNotificationOptions ( * ( notification1 ) , options1 . get ( ) ) ;
 EXPECT_EQ ( options1 -> type , extensions : : api : : notifications : : TEMPLATE_TYPE_IMAGE ) ;
 EXPECT_EQ ( * ( options1 -> title ) , "Title" ) ;
 EXPECT_EQ ( * ( options1 -> message ) , "This is a message." ) ;
 EXPECT_EQ ( * ( options1 -> priority ) , 1 ) ;
 EXPECT_EQ ( * ( options1 -> context_message ) , "I am a context message." ) ;
 EXPECT_FALSE ( * ( options1 -> is_clickable ) ) ;
 EXPECT_EQ ( * ( options1 -> event_time ) , 12345678.9 ) ;
 EXPECT_EQ ( options1 -> buttons -> at ( 0 ) -> title , "Button 1" ) ;
 EXPECT_EQ ( options1 -> buttons -> at ( 1 ) -> title , "Button 2" ) ;
 EXPECT_EQ ( options1 -> icon_bitmap -> width , 1 ) ;
 EXPECT_EQ ( options1 -> icon_bitmap -> height , 1 ) ;
 scoped_ptr < Notification > notification2 = CreateNotification ( message_center : : NOTIFICATION_TYPE_PROGRESS ) ;
 scoped_ptr < extensions : : api : : notifications : : NotificationOptions > options2 ( new extensions : : api : : notifications : : NotificationOptions ( ) ) ;
 NotificationConversionHelper : : NotificationToNotificationOptions ( * ( notification2 ) , options2 . get ( ) ) ;
 EXPECT_EQ ( options2 -> type , extensions : : api : : notifications : : TEMPLATE_TYPE_PROGRESS ) ;
 EXPECT_EQ ( * ( options2 -> progress ) , 50 ) ;
 scoped_ptr < Notification > notification3 = CreateNotification ( message_center : : NOTIFICATION_TYPE_MULTIPLE ) ;
 scoped_ptr < extensions : : api : : notifications : : NotificationOptions > options3 ( new extensions : : api : : notifications : : NotificationOptions ( ) ) ;
 NotificationConversionHelper : : NotificationToNotificationOptions ( * ( notification3 ) , options3 . get ( ) ) ;
 EXPECT_EQ ( options3 -> type , extensions : : api : : notifications : : TEMPLATE_TYPE_LIST ) ;
 EXPECT_EQ ( options3 -> items -> at ( 0 ) -> title , "Item 1 Title" ) ;
 EXPECT_EQ ( options3 -> items -> at ( 0 ) -> message , "Item 1 Message" ) ;
 EXPECT_EQ ( options3 -> items -> at ( 1 ) -> title , "Item 2 Title" ) ;
 EXPECT_EQ ( options3 -> items -> at ( 1 ) -> message , "Item 2 Message" ) ;
 }