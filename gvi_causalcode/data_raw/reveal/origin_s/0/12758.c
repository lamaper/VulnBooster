TEST_F ( ProtocolHandlerRegistryTest , IgnoreProtocolHandler ) {
 registry ( ) -> OnIgnoreRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsIgnored ( test_protocol_handler ( ) ) ) ;
 registry ( ) -> RemoveIgnoredHandler ( test_protocol_handler ( ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsIgnored ( test_protocol_handler ( ) ) ) ;
 }