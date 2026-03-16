TEST_F ( ProtocolHandlerRegistryTest , RemovingHandlerMeansItCanBeAddedAgain ) {
 registry ( ) -> OnAcceptRegisterProtocolHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( registry ( ) -> CanSchemeBeOverridden ( "test" ) ) ;
 registry ( ) -> RemoveHandler ( test_protocol_handler ( ) ) ;
 ASSERT_TRUE ( registry ( ) -> CanSchemeBeOverridden ( "test" ) ) ;
 }