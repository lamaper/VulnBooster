TEST_F ( ProtocolHandlerRegistryTest , TestReentrantNotifications ) {
 QueryProtocolHandlerOnChange queryer ( profile ( ) , registry ( ) ) ;
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( queryer . called_ ) ;
 }