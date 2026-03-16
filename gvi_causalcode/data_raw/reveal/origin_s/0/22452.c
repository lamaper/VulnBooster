TEST_F ( ProtocolHandlerRegistryTest , TestRemoveHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> RemoveHandler ( ph1 ) ;
 ASSERT_FALSE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 }