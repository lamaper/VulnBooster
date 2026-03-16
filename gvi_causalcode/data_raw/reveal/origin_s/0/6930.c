TEST_F ( ProtocolHandlerRegistryTest , TestIsEquivalentRegistered ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> HasRegisteredEquivalent ( ph2 ) ) ;
 }