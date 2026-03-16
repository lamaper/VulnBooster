TEST_F ( ProtocolHandlerRegistryTest , DisallowRegisteringExternallyHandledProtocols ) {
 delegate ( ) -> RegisterExternalHandler ( "test" ) ;
 ASSERT_FALSE ( registry ( ) -> CanSchemeBeOverridden ( "test" ) ) ;
 }