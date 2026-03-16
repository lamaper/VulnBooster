TEST_F ( ProtocolHandlerRegistryTest , IgnoreEquivalentProtocolHandler ) {
 ProtocolHandler ph1 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) ) ;
 ProtocolHandler ph2 = CreateProtocolHandler ( "test" , GURL ( "http://test/%s" ) ) ;
 registry ( ) -> OnIgnoreRegisterProtocolHandler ( ph1 ) ;
 ASSERT_TRUE ( registry ( ) -> IsIgnored ( ph1 ) ) ;
 ASSERT_TRUE ( registry ( ) -> HasIgnoredEquivalent ( ph2 ) ) ;
 registry ( ) -> RemoveIgnoredHandler ( ph1 ) ;
 ASSERT_FALSE ( registry ( ) -> IsIgnored ( ph1 ) ) ;
 ASSERT_FALSE ( registry ( ) -> HasIgnoredEquivalent ( ph2 ) ) ;
 }