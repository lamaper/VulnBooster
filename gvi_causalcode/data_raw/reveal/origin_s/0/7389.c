TEST_F ( ProtocolHandlerRegistryTest , TestIsHandledProtocol ) {
 registry ( ) -> GetHandlersFor ( "test" ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 }