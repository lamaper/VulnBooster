TEST_F ( ProtocolHandlerRegistryTest , TestNotifications ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 NotificationCounter counter ( profile ( ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( counter . notified ( ) ) ;
 counter . Clear ( ) ;
 registry ( ) -> Disable ( ) ;
 ASSERT_TRUE ( counter . notified ( ) ) ;
 counter . Clear ( ) ;
 registry ( ) -> Enable ( ) ;
 ASSERT_TRUE ( counter . notified ( ) ) ;
 counter . Clear ( ) ;
 registry ( ) -> RemoveHandler ( ph1 ) ;
 ASSERT_TRUE ( counter . notified ( ) ) ;
 counter . Clear ( ) ;
 }