TEST_F ( ProtocolHandlerRegistryTest , ClearDefaultMakesProtocolNotHandled ) {
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 registry ( ) -> ClearDefault ( "test" ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 ASSERT_TRUE ( registry ( ) -> GetHandlerFor ( "test" ) . IsEmpty ( ) ) ;
 }