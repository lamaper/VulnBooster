TEST_F ( ProtocolHandlerRegistryTest , TestGetHandlerFor ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 ASSERT_EQ ( ph2 , registry ( ) -> GetHandlerFor ( "test" ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 }