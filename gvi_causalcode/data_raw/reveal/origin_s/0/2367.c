TEST_F ( ProtocolHandlerRegistryTest , DisableDeregistersProtocolHandlers ) {
 ASSERT_FALSE ( delegate ( ) -> IsExternalHandlerRegistered ( "test" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( delegate ( ) -> IsExternalHandlerRegistered ( "test" ) ) ;
 registry ( ) -> Disable ( ) ;
 ASSERT_FALSE ( delegate ( ) -> IsExternalHandlerRegistered ( "test" ) ) ;
 registry ( ) -> Enable ( ) ;
 ASSERT_TRUE ( delegate ( ) -> IsExternalHandlerRegistered ( "test" ) ) ;
 }