TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestStartsAsDefault ) {
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsDefault ( test_protocol_handler ( ) ) ) ;
 }