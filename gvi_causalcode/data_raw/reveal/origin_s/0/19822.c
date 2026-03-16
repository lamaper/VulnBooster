IN_PROC_BROWSER_TEST_F ( MessageCenterNotificationsTest , UpdateNonProgressNotificationWhenCenterVisible ) {


 TestDelegate * delegate ;
 Notification notification = CreateTestNotification ( "n" , & delegate ) ;
 manager ( ) -> Add ( notification , profile ( ) ) ;
 const std : : string notification_id = manager ( ) -> GetMessageCenterNotificationIdForTest ( "n" , profile ( ) ) ;
 message_center ( ) -> ClickOnNotification ( notification_id ) ;
 message_center ( ) -> SetVisibility ( message_center : : VISIBILITY_MESSAGE_CENTER ) ;
 observer . reset_logs ( ) ;
 notification . set_title ( base : : ASCIIToUTF16 ( "title2" ) ) ;
 manager ( ) -> Update ( notification , profile ( ) ) ;
 EXPECT_EQ ( "" , observer . log ( notification_id ) ) ;
 message_center ( ) -> SetVisibility ( message_center : : VISIBILITY_TRANSIENT ) ;
 EXPECT_EQ ( base : : StringPrintf ( "update-%s" , notification_id . c_str ( ) ) , observer . log ( notification_id ) ) ;
 delegate -> Release ( ) ;
 }