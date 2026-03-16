TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestRemoveHandlerRemovesDefault ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , "test2" ) ;
 ProtocolHandler ph3 = CreateProtocolHandler ( "test" , "test3" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph2 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph3 ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> RemoveHandler ( ph1 ) ;
 ASSERT_FALSE ( registry ( ) -> IsDefault ( ph1 ) ) ;
 }