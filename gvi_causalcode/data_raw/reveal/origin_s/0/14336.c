TEST_F ( ProtocolHandlerRegistryTest , TestIsRegistered ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 ASSERT_TRUE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 }