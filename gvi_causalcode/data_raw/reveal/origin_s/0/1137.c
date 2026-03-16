TEST_F ( ProtocolHandlerRegistryTest , TestGetRegisteredProtocols ) {
 std : : vector < std : : string > protocols ;
 registry ( ) -> GetRegisteredProtocols ( & protocols ) ;
 ASSERT_EQ ( static_cast < size_t > ( 0 ) , protocols . size ( ) ) ;
 registry ( ) -> GetHandlersFor ( "test" ) ;
 protocols . clear ( ) ;
 registry ( ) -> GetRegisteredProtocols ( & protocols ) ;
 ASSERT_EQ ( static_cast < size_t > ( 0 ) , protocols . size ( ) ) ;
 }