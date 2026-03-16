IN_PROC_BROWSER_TEST_F ( MessageCenterNotificationsTest , BasicAddCancel ) {


 manager ( ) -> Add ( CreateTestNotification ( "hey" ) , profile ( ) ) ;
 EXPECT_EQ ( 1u , message_center ( ) -> NotificationCount ( ) ) ;
 manager ( ) -> CancelById ( "hey" , NotificationUIManager : : GetProfileID ( profile ( ) ) ) ;
 EXPECT_EQ ( 0u , message_center ( ) -> NotificationCount ( ) ) ;
 }