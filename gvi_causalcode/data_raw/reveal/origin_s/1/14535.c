TEST_F ( ProtocolHandlerRegistryTest , TestIsEquivalentRegistered ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) , "test1" ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) , "test2" ) ;
 registry ( ) -> OnAcceptRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> IsRegistered ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> HasRegisteredEquivalent ( ph2 ) ) ;
 }