TEST_F ( ProtocolHandlerRegistryTest , MAYBE_TestInstallDefaultHandler ) {
 RecreateRegistry ( false ) ;
 registry ( ) -> AddPredefinedHandler ( CreateProtocolHandler ( "test" , GURL ( "http://test.com/%s" ) ) ) ;
 registry ( ) -> InitProtocolSettings ( ) ;
 std : : vector < std : : string > protocols ;
 registry ( ) -> GetRegisteredProtocols ( & protocols ) ;
 ASSERT_EQ ( static_cast < size_t > ( 1 ) , protocols . size ( ) ) ;
 }