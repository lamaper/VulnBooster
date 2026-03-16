TEST_F ( ProtocolHandlerRegistryTest , MAYBE_DeniedProtocolIsntHandledUntilAccepted ) {
 registry ( ) -> OnDenyRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 }