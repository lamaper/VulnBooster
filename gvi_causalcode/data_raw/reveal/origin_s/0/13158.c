IN_PROC_BROWSER_TEST_F ( MessageCenterNotificationsTest , QueueWhenCenterVisible ) {


 TestDelegate * delegate ;
 TestDelegate * delegate2 ;
 manager ( ) -> Add ( CreateTestNotification ( "n" , & delegate ) , profile ( ) ) ;
 const std : : string id_n = manager ( ) -> GetMessageCenterNotificationIdForTest ( "n" , profile ( ) ) ;
 message_center ( ) -> SetVisibility ( message_center : : VISIBILITY_MESSAGE_CENTER ) ;
 manager ( ) -> Add ( CreateTestNotification ( "n2" , & delegate2 ) , profile ( ) ) ;
 const std : : string id_n2 = manager ( ) -> GetMessageCenterNotificationIdForTest ( "n2" , profile ( ) ) ;
 EXPECT_EQ ( base : : StringPrintf ( "add-%s_update-%s_update-%s" , id_n . c_str ( ) , id_n . c_str ( ) , id_n . c_str ( ) ) , observer . log ( id_n ) ) ;
 message_center ( ) -> SetVisibility ( message_center : : VISIBILITY_TRANSIENT ) ;
 EXPECT_EQ ( base : : StringPrintf ( "add-%s" , id_n2 . c_str ( ) ) , observer . log ( id_n2 ) ) ;
 delegate -> Release ( ) ;
 delegate2 -> Release ( ) ;
 }