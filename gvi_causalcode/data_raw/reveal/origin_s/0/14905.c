TEST_F ( ProtocolHandlerRegistryTest , TestProtocolsWithNoDefaultAreHandled ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , "test1" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 registry ( ) -> ClearDefault ( "test" ) ;
 std : : vector < std : : string > handled_protocols ;
 registry ( ) -> GetRegisteredProtocols ( & handled_protocols ) ;
 ASSERT_EQ ( static_cast < size_t > ( 1 ) , handled_protocols . size ( ) ) ;
 ASSERT_EQ ( "test" , handled_protocols [ 0 ] ) ;
 }