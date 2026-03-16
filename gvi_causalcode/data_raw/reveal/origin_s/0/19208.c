TEST_F ( ProtocolHandlerRegistryTest , TestDisablePreventsHandling ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 registry ( ) -> Disable ( ) ;
 ASSERT_FALSE ( registry ( ) -> IsHandledProtocol ( "test" ) ) ;
 }