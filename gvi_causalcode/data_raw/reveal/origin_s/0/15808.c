TEST_F ( ProtocolHandlerRegistryTest , TestClearDefault ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> ClearDefault ( "test" ) ;
 ASSERT_FALSE ( registry ( ) -> IsDefault ( ph1 ) ) ;
 ASSERT_FALSE ( registry ( ) -> IsDefault ( ph2 ) ) ;
 }