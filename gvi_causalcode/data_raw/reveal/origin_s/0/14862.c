TEST_F ( ProtocolHandlerRegistryTest , SaveAndLoad ) {
 ProtocolHandler stuff_protocol_handler ( CreateProtocolHandler ( "stuff" , "stuff" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 registry ( ) -> OnIgnoreRegisterProtocolHandler ( stuff_protocol_handler ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsIgnored ( stuff_protocol_handler ) ) ;
 delegate ( ) -> Reset ( ) ;
 RecreateRegistry ( true ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 ASSERT_TRUE ( registry ( ) -> IsIgnored ( stuff_protocol_handler ) ) ;
 }